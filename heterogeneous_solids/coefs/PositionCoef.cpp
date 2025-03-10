//
// Created by Alberto Elorza Rubio on 04/04/2024.
//

#include "PositionCoef.h"

#include "../Cell.h"
#include <utility>

namespace hs {
    PositionCoef::PositionCoef(Cell& cell, glm::vec3& shapePosition, unsigned int gridIndex) :
        cell(cell), shapePosition(shapePosition), gridIndex(gridIndex),
        shapeCoefType(ShapeCoef::typeFromGridIndex(gridIndex))
    {

    }

    glm::vec3& PositionCoef::getShapePosition() const {
        return shapePosition;
    }

    void PositionCoef::setShapePosition(glm::vec3 shapePosition) {
        if (attachedShapeCoef) attachedShapeCoef.value()->setPosition(shapePosition);
        else {
            cell.needRecalculation(false, true);
            PositionCoef::shapePosition = shapePosition;
        }
    }

    unsigned int PositionCoef::getGridIndex() const {
        return gridIndex;
    }

    ShapeCoefType PositionCoef::getShapeCoefType() const {
        return shapeCoefType;
    }

    const std::optional<ShapeCoef*>& PositionCoef::getAttachedShapeCoef() const {
        return attachedShapeCoef;
    }

    ShapeCoef* PositionCoef::getCornerCoef() const {
        if (attachedShapeCoef) return attachedShapeCoef.value()->getCornerCoef();
        return nullptr;
    }

    void PositionCoef::setAttachedShapeCoef(ShapeCoef* shapeCoef, CellCoef* cellCoef) {
        if (attachedShapeCoef) attachedShapeCoef.value()->detachObserver(this);
        shapeCoef->attachObserver(this);
        shapeCoef->attachSharedCoef(cellCoef);
        attachedShapeCoef = shapeCoef;
    }

    void PositionCoef::detachShapeCoef(CellCoef* cellCoef) {
        if (attachedShapeCoef) {
            attachedShapeCoef.value()->detachObserver(this);
            attachedShapeCoef.value()->detachSharedCoef(cellCoef);
            attachedShapeCoef = std::nullopt;
        }
    }

    void PositionCoef::updateObserver(ShapeCoefSubjectData payload) {
        cell.needRecalculation(false, true);
        shapePosition = payload.absolutePosition;
    }
} // hs