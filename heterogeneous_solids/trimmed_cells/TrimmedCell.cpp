//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#include "TrimmedCell.h"
#include "../utils.h"
#include "../BezierData.h"

#include <utility>

namespace hs {
    TrimmedCell::TrimmedCell(
        const std::array<glm::vec3, 64>& coefs,
        Cell &mainCell,
        size_t index,
        std::optional<std::reference_wrapper<TrimmedCell>> parentTrimmedCell,
        std::shared_ptr<TrimmingNode> machiningNode
    ) : trimmedCoefs(coefs),
        mainCell(mainCell),
        parentTrimmedCell(parentTrimmedCell),
        indexInParent(index),
        subTrimmedCells(),
        subTrimmedCellsCount(0),
        canonicalNode(machiningNode == nullptr ? std::make_unique<TrimmingNode>() : std::move(machiningNode)),
        activeNode(canonicalNode),
        needRecalcSubCells(true),

        renderDecorator([this](RenderContext& renderContext) { renderTrimmedCell(renderContext); })
    {
        TrimmedCell::canonicalNode->attachObserver(this);

        for (const auto& curveCoefs : isoCurveCoefs)
            isoCurves.push_back(std::make_unique<IsoCurve>(curveCoefs, *this));

        for (const auto& surfaceCoefs : isoSurfaceCoefs)
            isoSurfaces.push_back(std::make_unique<IsoSurface>(surfaceCoefs, *this));
    }

    TrimmedCell::~TrimmedCell() {
        getActiveNode()->detachObserver(this);
    }

    Cell& TrimmedCell::getMainCell() const {
        return mainCell;
    }

    std::optional<std::reference_wrapper<TrimmedCell>> TrimmedCell::getParentTrimmedCell() const {
        return parentTrimmedCell;
    }

    std::shared_ptr<TrimmingNode> TrimmedCell::getCanonicalNode() const {
        return canonicalNode;
    }

    std::shared_ptr<TrimmingNode> TrimmedCell::getActiveNode() const {
        return activeNode;
    }

    bool TrimmedCell::usingCanonicalNode() const {
        return activeNode == canonicalNode;
    }

    void TrimmedCell::resetActiveNode() {
        setActiveNode(canonicalNode);
    }

    void TrimmedCell::setActiveNode(std::shared_ptr<TrimmingNode> node) {
        activeNode->detachObserver(this);
        activeNode = std::move(node);
        activeNode->attachObserver(this);
        activeNode->notifyRefresh();
    }

    void TrimmedCell::setCanonicalNode(std::shared_ptr<TrimmingNode> node) {
        canonicalNode = std::move(node);
    }

    glm::vec3 TrimmedCell::evaluate(glm::vec3 coordinates) {
        glm::vec3 position(0);
        float Bi, Bj, Bk;

        for (int i = 0; i <= 3; ++i) {
            Bi = B(i, coordinates.x);
            int ii = i * 16;
            for (int j = 0; j <= 3; ++j) {
                Bj = B(j, coordinates.y);
                int jj = j * 4;
                for (int k = 0; k <= 3; ++k) {
                    Bk = B(k, coordinates.z);
                    position += Bi * Bj * Bk * trimmedCoefs[ii + jj + k];
                }
            }
        }

        return position;
    }

    std::vector<glm::vec3> TrimmedCell::evaluate(const std::vector<glm::vec3>& points) {
        std::vector<glm::vec3> evaluatedPoints;
        for (glm::vec3 point : points) evaluatedPoints.push_back(evaluate(point));
        if (parentTrimmedCell) return parentTrimmedCell->get().evaluate(evaluatedPoints);
        return evaluatedPoints;
    }

    PointAndTangentsST TrimmedCell::evaluatePointsAndTangents(PointAndTangentsST ptAndTgs) {
        glm::vec3 position(0);
        glm::vec3 tgU(0), tgV(0), tgW(0);
        float Bi, BDi, Bj, BDj, Bk, BDk;

        for (int i = 0; i <= 3; ++i) {
            Bi = B(i, ptAndTgs.point.x);
            BDi = BD(i, ptAndTgs.point.x);
            int ii = i * 16;
            for (int j = 0; j <= 3; ++j) {
                Bj = B(j, ptAndTgs.point.y);
                BDj = BD(j, ptAndTgs.point.y);
                int jj = j * 4;
                for (int k = 0; k <= 3; ++k) {
                    Bk = B(k, ptAndTgs.point.z);
                    BDk = BD(k, ptAndTgs.point.z);

                    auto& coef = trimmedCoefs[ii + jj + k];

                    position += Bi * Bj * Bk * coef;
                    tgU += BDi * Bj * Bk * coef;
                    tgV += Bi * BDj * Bk * coef;
                    tgW += Bi * Bj * BDk * coef;
                }
            }
        }

        glm::vec3 tgSInParent = (tgU * ptAndTgs.tgS.x) + (tgV * ptAndTgs.tgS.y) + (tgW * ptAndTgs.tgS.z);
        glm::vec3 tgTInParent = (tgU * ptAndTgs.tgT.x) + (tgV * ptAndTgs.tgT.y) + (tgW * ptAndTgs.tgT.z);

        return { position, tgSInParent, tgTInParent };
    }

    std::vector<PointAndTangentsST> TrimmedCell::evaluatePointsAndTangents(
        const std::vector<PointAndTangentsST>& ptAndTgsVec
    ) {
        std::vector<PointAndTangentsST> evaluatedPtAndTgs;
        for (PointAndTangentsST ptAndTgs : ptAndTgsVec)
            evaluatedPtAndTgs.push_back(evaluatePointsAndTangents(ptAndTgs));
        if (parentTrimmedCell) return parentTrimmedCell->get().evaluatePointsAndTangents(evaluatedPtAndTgs);
        return evaluatedPtAndTgs;
    }

    void TrimmedCell::needRecalculation(bool U, bool R) {
        for (auto& curve : isoCurves) curve->needRecalculation(U, R);
        for (auto& surface : isoSurfaces) surface->needRecalculation(U, R);
        for (auto& cell : subTrimmedCells) cell->needRecalculation(U, R);
    }

    const std::array<glm::vec3, 64>& TrimmedCell::getTrimmedCoefs() const {
        return trimmedCoefs;
    }

    void TrimmedCell::setTrimmedCoefs(const std::array<glm::vec3, 64>& trimmedCoefs) {
        TrimmedCell::trimmedCoefs = trimmedCoefs;
        needRecalculation(true, true);
        needRecalcSubCells = true;
    }

    std::vector<std::unique_ptr<TrimmedCell>>& TrimmedCell::getSubTrimmedCells() {
        return subTrimmedCells;
    }

    SceneNodeState& TrimmedCell::getState() {
        return getActiveNode()->getState();
    }

    [[nodiscard]] const char* TrimmedCell::getIcon() const {
        return usingCanonicalNode() ? ICON_MD_CHECK_BOX_OUTLINE_BLANK : ICON_MD_BUILD_CIRCLE;
    }

    void TrimmedCell::visitNode(NodeVisitor& visitor) {
        visitor.doTrimmedCell(*this);
    }

    void TrimmedCell::reserve(size_t cellsCount) {
        if (subTrimmedCells.size() >= cellsCount) return;
        for (size_t i = subTrimmedCells.size(); i < cellsCount; i++)
            subTrimmedCells.push_back(std::make_unique<TrimmedCell>(
                std::array<glm::vec3, 64>(),
                mainCell,
                i,
                *this,
                activeNode->getOrCreate(i)
            ));
    }

    void TrimmedCell::updateObserver() {
        auto subTrimmedCoefs = activeNode->operation->subTrimmedCell();
        subTrimmedCellsCount = subTrimmedCoefs.size();
        for (int i = 0; i < subTrimmedCellsCount; i++) {
            if (subTrimmedCells.size() <= i) {
                subTrimmedCells.push_back(std::make_unique<TrimmedCell>(
                    subTrimmedCoefs[i],
                    mainCell,
                    i,
                    *this,
                    activeNode->getOrCreate(i)
                ));
            } else {
                subTrimmedCells[i]->setTrimmedCoefs(subTrimmedCoefs[i]);
                bool usingCanonical = subTrimmedCells[i]->usingCanonicalNode();
                subTrimmedCells[i]->setCanonicalNode(activeNode->getOrCreate(i));
                if (usingCanonical) subTrimmedCells[i]->resetActiveNode();
            }
        }
    }

    Decorator<void, RenderContext&>& TrimmedCell::getRenderer() {
        return renderDecorator;
    }

    std::optional<std::reference_wrapper<SceneNode>> TrimmedCell::getParent() const {
        return parentTrimmedCell.has_value() ? *parentTrimmedCell : (SceneNode&)mainCell;
    }

    size_t TrimmedCell::getIndexInParent() const {
        return indexInParent;
    }

    size_t TrimmedCell::childCount() const {
        return subTrimmedCellsCount;
    }

    std::optional<std::reference_wrapper<SceneNode>> TrimmedCell::getChild(size_t index) const {
        if (index >= subTrimmedCellsCount || index >= subTrimmedCells.size()) return std::nullopt;
        return *subTrimmedCells[index];
    }

    void TrimmedCell::renderTrimmedCell(RenderContext& renderContext) {
        if (!getState().isVisible()) return;

        if (needRecalcSubCells) {
            updateObserver();
            needRecalcSubCells = false;
        }

        switch (renderContext.getRenderMode()) {
            case RenderMode::Lines:
                if (renderContext.IsDetailedRendering() && subTrimmedCellsCount) {
                    for (int i = 0; i < subTrimmedCellsCount; i++) subTrimmedCells[i]->getRenderer()(renderContext);
                } else {
                    for (auto& curve : isoCurves) curve->render(renderContext);
                }
                break;
            case RenderMode::SurfaceSelectColor:
                renderContext.getSelectionController().subscribeNextObject(*this);
            case RenderMode::Normals:
            case RenderMode::Surfaces:
                if (renderContext.IsDetailedRendering() && subTrimmedCellsCount) {
                    for (int i = 0; i < subTrimmedCellsCount; i++) subTrimmedCells[i]->getRenderer()(renderContext);
                } else {
                    for (auto& surface : isoSurfaces) surface->render(renderContext);
                }
                break;
            case RenderMode::Vertices:
                break;
        }
    }
} // hs