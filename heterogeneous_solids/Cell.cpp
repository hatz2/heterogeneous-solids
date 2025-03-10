//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#include "Cell.h"

#include <utility>
#include "utils.h"
#include "../utils/vector.h"

namespace hs {
    Cell::Cell(std::array<glm::vec3, 64> shapePositions) :
        state("Main Cell"),

        sharedData(std::make_shared<HSSharedData>()),

        coefPositions(shapePositions),
        perlinPeriod(21),

        parentSolid(std::nullopt),
        indexInParent(0),

        renderDecorator([this](RenderContext& renderContext) { renderCell(renderContext); })
    {
        std::fill(p.begin(), p.end(), glm::vec3(5));
        std::fill(a0.begin(), a0.begin() + 32, 0.f);
        std::fill(a0.begin() + 32, a0.end(), 1.f);


        auto coefGroup = std::make_unique<CellCoefGroup>(*this, children.size(), coefPositions, p, a0);
        cellCoefGroup = coefGroup.get();
        children.push_back(std::move(coefGroup));

        auto trimmedCell = std::make_unique<TrimmedCell>(getDefaultCoefs(), *this, children.size());
        trimmedCells.insert(trimmedCell.get());
        children.push_back(std::move(trimmedCell));
    }

    Cell::Cell() : Cell(getDefaultCoefs()) {

    }

    Cell::~Cell() {
        if (parentSolid) parentSolid.value().get().removeCell(this);
        parentSolid = std::nullopt;
        indexInParent = 0;
    }

    glm::vec3 Cell::evaluate(glm::vec3 coordinates) {
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
                    position += Bi * Bj * Bk * coefPositions[ii + jj + k];
                }
            }
        }

        return position;
    }

    std::vector<glm::vec3> Cell::evaluate(const std::vector<glm::vec3>& points) {
        std::vector<glm::vec3> evaluatedPoints;
        for (glm::vec3 point : points) evaluatedPoints.push_back(evaluate(point));
        return evaluatedPoints;
    }

    PointAndTangentsUVW Cell::evaluatePointAndTangents(glm::vec3 coordinates) {
        glm::vec3 position(0);
        glm::vec3 tgU(0), tgV(0), tgW(0);
        float Bi, BDi, Bj, BDj, Bk, BDk;

        for (int i = 0; i <= 3; ++i) {
            Bi = B(i, coordinates.x);
            BDi = BD(i, coordinates.x);
            int ii = i * 16;
            for (int j = 0; j <= 3; ++j) {
                Bj = B(j, coordinates.y);
                BDj = BD(j, coordinates.y);
                int jj = j * 4;
                for (int k = 0; k <= 3; ++k) {
                    Bk = B(k, coordinates.z);
                    BDk = BD(k, coordinates.z);

                    auto& coefPosition = coefPositions[ii + jj + k];

                    position += Bi * Bj * Bk * coefPosition;
                    tgU += BDi * Bj * Bk * coefPosition;
                    tgV += Bi * BDj * Bk * coefPosition;
                    tgW += Bi * Bj * BDk * coefPosition;
                }
            }
        }

        return { position, tgU, tgV, tgW };
    }

    std::vector<PointAndTangentsUVW> Cell::evaluatePointAndTangents(const std::vector<glm::vec3>& points) {
        std::vector<PointAndTangentsUVW> evaluatedPointAndTangents;
        for (glm::vec3 point : points) evaluatedPointAndTangents.push_back(evaluatePointAndTangents(point));
        return evaluatedPointAndTangents;
    }

    void Cell::needRecalculation(bool U, bool R) {
        for (auto& trimmedCell : trimmedCells) trimmedCell->needRecalculation(U, R);
    }

    std::set<TrimmedCell*>& Cell::getTrimmedCells() {
        return trimmedCells;
    }

    CellCoefGroup*& Cell::getCellCoefGroup() {
        return cellCoefGroup;
    }

    std::optional<std::reference_wrapper<HeterogeneousSolid>> Cell::getHeterogeneousSolidParent() const {
        return parentSolid;
    }

    glm::vec3 Cell::getPerlinPeriod() const {
        return perlinPeriod;
    }

    void Cell::setPerlinPeriod(glm::vec3 perlinPeriod) {
        Cell::perlinPeriod = perlinPeriod;
    }

    HSSharedData& Cell::getSharedData() const {
        return *sharedData;
    }

    SceneNodeState& Cell::getState() {
        return state;
    }

    const char* Cell::getIcon() const {
        return ICON_MD_SELECT_ALL;
    }

    void Cell::visitNode(NodeVisitor& visitor) {
        visitor.doCell(*this);
    }

    Decorator<void, RenderContext&>& Cell::getRenderer() {
        return renderDecorator;
    }

    void Cell::renderCell(RenderContext& renderContext) {
        if (!state.isVisible()) return;

        if (renderContext.getRenderMode() == RenderMode::Surfaces) {
            renderContext.getUniform("cellData.a0").set(&a0.front(), a0.size());
            renderContext.getUniform("cellData.p").set(&p.front(), p.size());
            renderContext.getUniform("cellData.perlinPeriod").set(perlinPeriod);
        }

        cellCoefGroup->getRenderer()(renderContext);

        for (auto& trimmedCell : trimmedCells)
            trimmedCell->getRenderer()(renderContext);
    }

    std::optional<std::reference_wrapper<SceneNode>> Cell::getParent() const {
        return parentSolid;
    }

    size_t Cell::getIndexInParent() const {
        return indexInParent;
    }

    bool Cell::acceptsParent(SceneNode& parent) const {
        return dynamic_cast<HeterogeneousSolid*>(&parent);
    }

    bool Cell::bindParent(SceneNode& parent, size_t index) {
        auto updateState = [this](size_t index) {
            state.setDefaultDescription("Main Cell " + std::to_string(index));
        };

        if (parentSolid && &parent == &parentSolid.value().get()) {
            indexInParent = index;
            updateState(index);
            return true;
        }

        if (auto* hsParent = dynamic_cast<HeterogeneousSolid*>(&parent)) {
            if (parentSolid) parentSolid.value().get().removeCell(this);
            parentSolid = *hsParent;
            indexInParent = index;
            sharedData = hsParent->getSharedData();
            updateState(index);
            parentSolid.value().get().addCell(this);
            return true;
        }
        return false;
    }

    bool Cell::unbindParent() {
        if (parentSolid) parentSolid.value().get().removeCell(this);
        for (auto& coef : cellCoefGroup->getCoefs())
            coef->detachShapeCoef();
        parentSolid = std::nullopt;
        indexInParent = 0;
        return true;
    }

    size_t Cell::childCount() const {
        return children.size();
    }

    std::optional<std::reference_wrapper<SceneNode>> Cell::getChild(size_t index) const {
        return ext::tryGet(children, index);
    }
} // hs