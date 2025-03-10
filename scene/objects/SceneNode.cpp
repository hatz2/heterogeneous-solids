//
// Created by Alberto Elorza Rubio on 09/02/2024.
//

#include "SceneNode.h"

namespace hs {
    std::optional<std::reference_wrapper<SceneNode>> SceneNode::getNextSibling() const {
        if (auto parent = getParent()) {
            auto& node = parent->get();
            return node.getChild((getIndexInParent() + 1) % node.childCount());
        }
        return std::nullopt;
    }

    std::optional<std::reference_wrapper<SceneNode>> SceneNode::getPreviousSibling() const {
        if (auto parent = getParent()) {
            auto& node = parent->get();
            auto indexInParent = (long long)getIndexInParent();
            auto childCount = (long long)node.childCount();
            return node.getChild((((indexInParent - 1) % childCount) + childCount) % childCount);
        }
        return std::nullopt;
    }

    std::optional<std::reference_wrapper<SceneNode>> SceneNode::getObject() const {
        if (auto parent = getParent())
            return parent->get().getChild(getIndexInParent());
        return std::nullopt;
    }

    std::optional<std::unique_ptr<SceneNode>> SceneNode::getObjectOwnership() {
        auto parent = getParent();
        if (!parent) return std::nullopt;

        if (auto child = parent->get().getChild(getIndexInParent())) {
            if (&child.value().get() == this) {
                // Under no circumstance getChild and removeChild may differ the resulting object
                // otherwise the behaviour is truly unexpected
                return parent->get().removeChild(getIndexInParent());
            } else spdlog::warn("A child got by index does not match the object");
        }
        return std::nullopt;
    }

    std::optional<std::reference_wrapper<Transform>> SceneNode::getImmediateTransform() {
        if (auto transform = getOwnedTransform()) {
            return transform;
        }
        if (auto parent = getParent()) {
            return parent.value().get().getImmediateTransform();
        }
        return std::nullopt;
    }
} // hs