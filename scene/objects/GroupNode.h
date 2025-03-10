//
// Created by Alberto Elorza Rubio on 21/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_GROUPNODE_H
#define HETEROGENEOUS_SOLIDS_GROUPNODE_H

#include "SceneNode.h"
#include "Transform.h"
#include <vector>
#include <memory>

namespace hs {

    class GroupNode: public SceneNode {
    public:
        using ItemType = std::unique_ptr<SceneNode>;
        using Iterator = std::vector<ItemType>::iterator;

        GroupNode();

        [[nodiscard]] Iterator begin();
        [[nodiscard]] Iterator end();
        [[nodiscard]] const std::vector<ItemType>& getChildren() const;

        SceneNodeState& getState() override;
        [[nodiscard]] const char* getIcon() const override;

        void visitNode(NodeVisitor& visitor) override;

        Decorator<void, RenderContext&>& getRenderer() override;

        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getParent() const override;
        [[nodiscard]] size_t getIndexInParent() const override;
        [[nodiscard]] bool acceptsParent(SceneNode& parent) const override;
        bool bindParent(SceneNode& parent, size_t index) override;
        bool unbindParent() override;

        [[nodiscard]] size_t childCount() const override;
        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getChild(size_t index) const override;
        std::optional<size_t> addChild(std::unique_ptr<SceneNode>& child) override;
        std::optional<size_t> moveChild(SceneNode &child) override;
        std::optional<std::unique_ptr<SceneNode>> removeChild(size_t index) override;

        [[nodiscard]] std::optional<std::reference_wrapper<Transform>> getOwnedTransform() override;
    private:
        Transform transform;
        std::optional<std::reference_wrapper<SceneNode>> parent;
        size_t indexInParent;

        std::vector<ItemType> children;
        MutableSceneNodeState state;
        DecoratorStack<void, RenderContext&> renderDecorator;

        void renderGroup3D(RenderContext& renderContext);
        void updateDefaultDescription();
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_GROUPNODE_H
