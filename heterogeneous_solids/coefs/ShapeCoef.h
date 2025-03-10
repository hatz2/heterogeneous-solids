//
// Created by Alberto Elorza Rubio on 01/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SHAPECOEF_H
#define HETEROGENEOUS_SOLIDS_SHAPECOEF_H

#include <glm/glm.hpp>
#include <memory>
#include <set>
#include "../../scene/drawables/Vertex.h"
#include "../../utils/Decorator.h"
#include "../../utils/Observer.h"

namespace hs {

    class CellCoef;

    enum class ShapeCoefType {
        Vertex = 0,
        Edge = 1,
        Surface = 2,
        Corner = 3
    };

    class ShapeCoef;

    struct ShapeCoefSubjectData {
        ShapeCoef* origin;
        glm::vec3 absolutePosition;
        glm::vec3 relativePosition;
    };

    class ShapeCoef:
            public Subject<ShapeCoefSubjectData>,
            private Observer<Transform&>,
            private Observer<ShapeCoefSubjectData>
    {
    public:
        ShapeCoef(glm::vec3 position, unsigned int gridIndex);
        ~ShapeCoef() override;

        [[nodiscard]] Transform& getTransform();

        [[nodiscard]] const glm::vec3& getPosition() const;
        void setPosition(glm::vec3 position);

        [[nodiscard]] ShapeCoefType getType() const;
        [[nodiscard]] unsigned int getGridIndex() const;

        [[nodiscard]] bool isAlreadyRendered() const;
        void setAlreadyRendered(bool alreadyRendered);

        [[nodiscard]] ShapeCoef* getCornerCoef() const;
        void setCornerCoef(ShapeCoef* cornerCoef);
        void removeCornerCoef();

        [[nodiscard]] const std::set<CellCoef*>& getSharedCoefs() const;
        void attachSharedCoef(CellCoef* sharedCoef);
        void detachSharedCoef(CellCoef* sharedCoef);

        static unsigned int cornerIndexFromGridIndex(unsigned int position);
        static ShapeCoefType typeFromGridIndex(unsigned int position);
        static const char* getNameFromType(ShapeCoefType type);
    private:
        ShapeCoef* cornerCoef; // the corner coef, if there is no corner coef associated should reference itself
        ShapeCoefType type;
        unsigned int gridIndex;
        Transform transform;

        glm::vec3 position;

        bool alreadyRendered;
        std::set<CellCoef*> sharedCoefs; // all the cell coef that share the same position

        void internalSetPosition(glm::vec3 position);
        void updateObserver(Transform& transform) override;
        void updateObserver(ShapeCoefSubjectData payload) override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SHAPECOEF_H
