//
// Created by Alberto Elorza Rubio on 10/02/2024.
//

#include "CellCoefGroup.h"

namespace hs {
    CellCoefGroup::CellCoefGroup(
        Cell& cell, size_t index,
        std::array<glm::vec3, 64>& coefPositions, std::array<glm::vec3, 64>& p, std::array<float, 64>& a0
    ) :
        cell(cell), indexInParent(index), coefs(), state("Coefficients Group"),
        renderDecorator([this](RenderContext& renderContext) { renderCellCoefGroup(renderContext); })
    {
        for (int i = 0; i < coefs.size(); i++) {
            auto positionCoef = std::make_unique<PositionCoef>(cell, coefPositions[i], i);
            auto materialCoef = std::make_unique<MaterialCoef>(a0[i]);
            coefs[i] = std::make_unique<CellCoef>(
                cell, *this, i, std::move(positionCoef), p[i], std::move(materialCoef)
            );
        }
        for (int i = 0; i < coefs.size(); i++) {
            CellCoef* corner = coefs[ShapeCoef::cornerIndexFromGridIndex(i)].get();
            coefs[i]->getMaterialCoef().setMaterialCoefSync(corner->getMaterialCoef().getMaterialCoefSync());
        }
    }

    Cell& CellCoefGroup::getCell() const {
        return cell;
    }

    std::array<std::unique_ptr<CellCoef>, 64>& CellCoefGroup::getCoefs() {
        return coefs;
    }

    void CellCoefGroup::visitNode(NodeVisitor& visitor) {
        visitor.doCellCoefGroup(*this);
    }

    SceneNodeState& CellCoefGroup::getState() {
        return state;
    }

    const char* CellCoefGroup::getIcon() const {
        return ICON_MD_GROUP_WORK;
    }

    Decorator<void, RenderContext&>& CellCoefGroup::getRenderer() {
        return renderDecorator;
    }

    bool CellCoefGroup::nodeDefaultOpen() const {
        return false;
    }

    std::optional<std::reference_wrapper<SceneNode>> CellCoefGroup::getParent() const {
        return cell;
    }

    size_t CellCoefGroup::getIndexInParent() const {
        return indexInParent;
    }

    size_t CellCoefGroup::childCount() const {
        return coefs.size();
    }

    std::optional<std::reference_wrapper<SceneNode>> CellCoefGroup::getChild(size_t index) const {
        return *coefs[index];
    }

    void CellCoefGroup::renderCellCoefGroup(RenderContext& renderContext) {
        if (!state.isVisible() ||
            (
                renderContext.getRenderMode() != RenderMode::Vertices &&
                renderContext.getRenderMode() != RenderMode::VertexSelectColor
            )
        ) return;

        for (auto& coef : coefs)
            coef->getRenderer()(renderContext);
    }
} // hs