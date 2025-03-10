//
// Created by Alberto Elorza Rubio on 04/04/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_POSITIONCOEF_H
#define HETEROGENEOUS_SOLIDS_POSITIONCOEF_H

#include "ShapeCoef.h"

namespace hs {

    class Cell;

    class PositionCoef: private Observer<ShapeCoefSubjectData>
    {
    public:
        PositionCoef(Cell& cell, glm::vec3& shapePosition, unsigned int gridIndex);
        PositionCoef(const PositionCoef& other) = delete;

        [[nodiscard]] glm::vec3& getShapePosition() const;
        void setShapePosition(glm::vec3 shapePosition);

        [[nodiscard]] unsigned int getGridIndex() const;
        [[nodiscard]] ShapeCoefType getShapeCoefType() const;

        [[nodiscard]] const std::optional<ShapeCoef*>& getAttachedShapeCoef() const;
        [[nodiscard]] ShapeCoef* getCornerCoef() const;
    private:
        Cell& cell;
        std::optional<ShapeCoef*> attachedShapeCoef;
        glm::vec3& shapePosition;

        unsigned int gridIndex;
        ShapeCoefType shapeCoefType;

        void setAttachedShapeCoef(ShapeCoef* shapeCoef, CellCoef* cellCoef);
        void detachShapeCoef(CellCoef* cellCoef);

        void updateObserver(ShapeCoefSubjectData payload) override;

        friend class CellCoef;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_POSITIONCOEF_H
