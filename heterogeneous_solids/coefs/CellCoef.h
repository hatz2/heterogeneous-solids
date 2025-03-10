//
// Created by Alberto Elorza Rubio on 10/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_CELLCOEF_H
#define HETEROGENEOUS_SOLIDS_CELLCOEF_H

#include "../../scene/objects/SceneNode.h"
#include "ShapeCoef.h"
#include "PositionCoef.h"
#include "MaterialCoef.h"

namespace hs {

    class Cell;

    class CellCoef: public SceneNode {
    public:
        CellCoef(
            Cell& cell, SceneNode& parent, size_t index, std::unique_ptr<PositionCoef> positionCoef,
            glm::vec3& p, std::unique_ptr<MaterialCoef> materialCoef
        );
        ~CellCoef() override;

        [[nodiscard]] Cell& getCell() const;

        void visitNode(NodeVisitor& visitor) override;

        [[nodiscard]] SceneNodeState& getState() override;
        [[nodiscard]] const char* getIcon() const override;

        Decorator<void, RenderContext&>& getRenderer() override;

        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getParent() const override;
        [[nodiscard]] size_t getIndexInParent() const override;

        std::optional<std::reference_wrapper<Transform>> getOwnedTransform() override;

        [[nodiscard]] PositionCoef& getPositionCoef() const;
        [[nodiscard]] MaterialCoef& getMaterialCoef() const;

        [[nodiscard]] const std::optional<ShapeCoef*>& getAttachedShapeCoef() const;
        void setAttachedShapeCoef(ShapeCoef* shapeCoef);
        void detachShapeCoef();
    private:
        Cell& cell;
        SceneNode& parent;
        size_t indexInParent;

        MutableSceneNodeState state;
        std::unique_ptr<PositionCoef> positionCoef;
        glm::vec3& p;
        std::unique_ptr<MaterialCoef> materialCoef;

        DecoratorStack<void, RenderContext&> renderDecorator;

        void renderCellCoef(RenderContext& renderContext);
    };

} // hs

#include "../Cell.h"

#endif //HETEROGENEOUS_SOLIDS_CELLCOEF_H
