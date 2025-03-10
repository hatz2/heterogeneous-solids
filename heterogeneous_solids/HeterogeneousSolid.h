//
// Created by Alberto Elorza Rubio on 28/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_HETEROGENEOUSSOLID_H
#define HETEROGENEOUS_SOLIDS_HETEROGENEOUSSOLID_H

#include <vector>
#include <optional>
#include "coefs/ShapeCoef.h"
#include "Cell.h"
#include "HSSharedData.h"
#include "HeterogeneousMaterial.h"

namespace hs {

    class HeterogeneousSolid: public SceneNode {
    public:
        HeterogeneousSolid();
        explicit HeterogeneousSolid(std::string name);

        void needRecalculation(bool U, bool R);

        void addCell(Cell* cell);
        void removeCell(Cell* cell);

        std::set<Cell*>& getCells();
        std::shared_ptr<HSSharedData> getSharedData();

        SceneNodeState& getState() override;
        [[nodiscard]] const char* getIcon() const override;

        [[nodiscard]] std::shared_ptr<HeterogeneousMaterial> getMaterial() const;
        void setMaterial(std::shared_ptr<HeterogeneousMaterial> material);

        void visitNode(NodeVisitor& visitor) override;

        Decorator<void, RenderContext&>& getRenderer() override;

        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getParent() const override;
        [[nodiscard]] size_t getIndexInParent() const override;
        [[nodiscard]] bool acceptsParent(SceneNode &parent) const override;
        bool bindParent(SceneNode& parent, size_t index) override;
        bool unbindParent() override;

        [[nodiscard]] size_t childCount() const override;
        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getChild(size_t index) const override;
        std::optional<size_t> addChild(std::unique_ptr<SceneNode>& child) override;
        std::optional<size_t> moveChild(hs::SceneNode &child) override;
        std::optional<std::unique_ptr<SceneNode>> removeChild(size_t index) override;

        std::optional<std::reference_wrapper<Transform>> getImmediateTransform() override;
        std::optional<std::reference_wrapper<Transform>> getOwnedTransform() override;
    private:
        Transform transform;
        std::shared_ptr<HSSharedData> sharedData;
        MutableSceneNodeState state;
        std::shared_ptr<HeterogeneousMaterial> material;

        std::vector<std::unique_ptr<ShapeCoef>> shapeCoefs;
        std::set<Cell*> cells;
        std::vector<std::unique_ptr<SceneNode>> children;
        std::optional<std::reference_wrapper<SceneNode>> parentObject;
        size_t indexInParent;

        DecoratorStack<void, RenderContext&> renderDecorator;

        void renderHeterogeneousSolid(RenderContext& renderContext);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_HETEROGENEOUSSOLID_H
