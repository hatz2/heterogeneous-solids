//
// Created by Alberto Elorza Rubio on 10/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_CELLCOEFGROUP_H
#define HETEROGENEOUS_SOLIDS_CELLCOEFGROUP_H

#include "../../scene/objects/SceneNode.h"
#include "CellCoef.h"
#include "MaterialCoef.h"

namespace hs {

    class Cell;

    class CellCoefGroup: public SceneNode {
    public:
        CellCoefGroup(
            Cell& parentCell, size_t index,
            std::array<glm::vec3, 64>& coefPositions, std::array<glm::vec3, 64>& p, std::array<float, 64>& a0
        );

        [[nodiscard]] Cell& getCell() const;
        [[nodiscard]] std::array<std::unique_ptr<CellCoef>, 64>& getCoefs();

        void visitNode(NodeVisitor& visitor) override;

        [[nodiscard]] SceneNodeState& getState() override;
        [[nodiscard]] const char* getIcon() const override;

        Decorator<void, RenderContext&>& getRenderer() override;

        [[nodiscard]] bool nodeDefaultOpen() const override;

        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getParent() const override;
        [[nodiscard]] size_t getIndexInParent() const override;

        [[nodiscard]] size_t childCount() const override;
        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getChild(size_t index) const override;
    private:
        Cell& cell;
        size_t indexInParent;
        MutableSceneNodeState state;

        std::array<std::unique_ptr<CellCoef>, 64> coefs;

        DecoratorStack<void, RenderContext&> renderDecorator;

        void renderCellCoefGroup(RenderContext& renderContext);
    };

} // hs

#include "../Cell.h"

#endif //HETEROGENEOUS_SOLIDS_CELLCOEFGROUP_H
