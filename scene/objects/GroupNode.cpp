//
// Created by Alberto Elorza Rubio on 21/11/2023.
//

#include "GroupNode.h"
#include "../../utils/vector.h"

namespace hs {
    GroupNode::GroupNode() :
        parent(std::nullopt),
        indexInParent(0),

        state(),
        renderDecorator([this](RenderContext& renderContext){ renderGroup3D(renderContext); })
    {
        updateDefaultDescription();
    }

    GroupNode::Iterator GroupNode::begin() {
        return children.begin();
    }

    GroupNode::Iterator GroupNode::end() {
        return children.end();
    }

    const std::vector<GroupNode::ItemType>& GroupNode::getChildren() const {
        return children;
    }

    SceneNodeState& GroupNode::getState() {
        return state;
    }

    const char* GroupNode::getIcon() const {
        return ICON_MD_CATEGORY;
    }

    void GroupNode::visitNode(NodeVisitor& visitor) {
        visitor.doGroupNode(*this);
    }

    Decorator<void, RenderContext&>& GroupNode::getRenderer() {
        return renderDecorator;
    }

    void GroupNode::renderGroup3D(RenderContext& renderContext) {
        if (!state.isVisible()) return;

        for (const auto& obj : children) {
            renderContext.setModelMatrix(transform);
            obj->getRenderer()(renderContext);
        }
    }

    std::optional<std::reference_wrapper<SceneNode>> GroupNode::getParent() const {
        return parent;
    }

    size_t GroupNode::getIndexInParent() const {
        return indexInParent;
    }

    bool GroupNode::acceptsParent(SceneNode& parent) const {
        return true;
    }

    bool GroupNode::bindParent(SceneNode& parent, size_t index) {
        GroupNode::indexInParent = index;

        if (!GroupNode::parent || &GroupNode::parent->get() != &parent) {
            GroupNode::parent = parent;

            if (auto transformParent = parent.getImmediateTransform()) transform.setParent(transformParent->get());
            else transform.removeParent();
        }

        return true;
    }

    bool GroupNode::unbindParent() {
        parent = std::nullopt;
        indexInParent = 0;
        transform.removeParent();
        return true;
    }

    size_t GroupNode::childCount() const {
        return children.size();
    }

    std::optional<std::reference_wrapper<SceneNode>> GroupNode::getChild(size_t index) const {
        return ext::tryGet(children, index);
    }

    std::optional<size_t> GroupNode::addChild(std::unique_ptr<SceneNode>& child) {
        size_t idx = children.size();
        if (!child->bindParent(*this, idx)) // Prevent invalid relationship
            return std::nullopt;
        children.push_back(std::move(child));
        updateDefaultDescription();
        return idx;
    }

    std::optional<size_t> GroupNode::moveChild(SceneNode& child) {
        if (!child.acceptsParent(*this)) return std::nullopt;

        if (auto object = child.getObjectOwnership()) {
            size_t idx = children.size();
            if (!child.bindParent(*this, idx)) {
                spdlog::warn("Object set parent did not work as expected");
                return std::nullopt;
            }

            children.push_back(std::move(object.value()));
            updateDefaultDescription();
            return idx;
        } else spdlog::warn("Got no object ownership");
        return std::nullopt;
    }

    std::optional<std::unique_ptr<SceneNode>> GroupNode::removeChild(size_t index) {
        auto removed = ext::tryRemove(children, index);
        if (removed) {
            updateDefaultDescription();
            int idx = 0;
            for (auto& child : children)
                child->bindParent(*this, idx++);
        }
        return removed;
    }

    std::optional<std::reference_wrapper<Transform>> GroupNode::getOwnedTransform() {
        return transform;
    }

    void GroupNode::updateDefaultDescription() {
        size_t size = children.size();
        std::string description = "Group with " + std::to_string(size) + " object";
        if (size != 1) description += "s";
        state.setDefaultDescription(description);
    }
} // hs