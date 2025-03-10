//
// Created by Alberto Elorza Rubio on 10/02/2024.
//

#include "CellCoef.h"

namespace hs {
    CellCoef::CellCoef(
        Cell& cell, SceneNode& parent, size_t index, std::unique_ptr<PositionCoef> positionCoef,
        glm::vec3& p, std::unique_ptr<MaterialCoef> materialCoef
    ) : cell(cell), parent(parent), indexInParent(index),
        state("Cell Coefficient " + std::to_string(index + 1)),
        positionCoef(std::move(positionCoef)), p(p), materialCoef(std::move(materialCoef)),
        renderDecorator([this](RenderContext& renderContext) { renderCellCoef(renderContext); }) {

    }

    CellCoef::~CellCoef() {
        detachShapeCoef();
    }

    Cell& CellCoef::getCell() const {
        return cell;
    }

    void CellCoef::visitNode(NodeVisitor& visitor) {
        visitor.doCellCoef(*this);
    }

    SceneNodeState& CellCoef::getState() {
        return state;
    }

    const char* CellCoef::getIcon() const {
        return ICON_MD_NUMBERS;
    }

    Decorator<void, RenderContext&>& CellCoef::getRenderer() {
        return renderDecorator;
    }

    std::optional<std::reference_wrapper<SceneNode>> CellCoef::getParent() const {
        return parent;
    }

    size_t CellCoef::getIndexInParent() const {
        return indexInParent;
    }

    std::optional<std::reference_wrapper<Transform>> CellCoef::getOwnedTransform() {
        auto attachedShapeCoef = getAttachedShapeCoef();
        if (!attachedShapeCoef) return std::nullopt;
        return attachedShapeCoef.value()->getTransform();
    }

    PositionCoef& CellCoef::getPositionCoef() const {
        return *positionCoef;
    }

    MaterialCoef& CellCoef::getMaterialCoef() const {
        return *materialCoef;
    }

    const std::optional<ShapeCoef*>& CellCoef::getAttachedShapeCoef() const {
        return positionCoef->getAttachedShapeCoef();
    }

    void CellCoef::setAttachedShapeCoef(ShapeCoef* shapeCoef) {
        positionCoef->setAttachedShapeCoef(shapeCoef, this);
    }

    void CellCoef::detachShapeCoef() {
        positionCoef->detachShapeCoef(this);
    }

    void CellCoef::renderCellCoef(RenderContext& renderContext) {
        auto cornerNeighborhoodFilter = [this](SceneNode* selection) {
            if (positionCoef->shapeCoefType == ShapeCoefType::Corner) return true;
            CellCoef* selectedCoef;
            if (!(selectedCoef = dynamic_cast<CellCoef*>(selection))) return false;

            return selectedCoef->positionCoef->getCornerCoef() == positionCoef->getCornerCoef();
        };
        auto attachedShapeCoef = getAttachedShapeCoef();
        if (!state.isVisible() || !attachedShapeCoef || attachedShapeCoef.value()->isAlreadyRendered() ||
            !cornerNeighborhoodFilter(renderContext.getSelection()) ||
            (
                renderContext.getRenderMode() != RenderMode::Vertices &&
                renderContext.getRenderMode() != RenderMode::VertexSelectColor
            )
        ) return;

        if (renderContext.getRenderMode() == RenderMode::VertexSelectColor)
            renderContext.getSelectionController().subscribeNextObject(*this);

        if (attachedShapeCoef) renderContext.setModelMatrix(attachedShapeCoef.value()->getTransform());
        else renderContext.setModelMatrix(glm::translate(glm::mat4(1), positionCoef->getShapePosition()));

        Vertex::getVertexInstance().render(renderContext);
        attachedShapeCoef.value()->setAlreadyRendered(true);
    }
} // hs