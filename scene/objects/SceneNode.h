//
// Created by Alberto Elorza Rubio on 21/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SCENENODE_H
#define HETEROGENEOUS_SOLIDS_SCENENODE_H

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include "../RenderContext.h"
#include "../../utils/NodeVisitor.h"
#include "SceneNodeState.h"
#include "../../utils/Decorator.h"
#include "Transform.h"

namespace hs {

    class SceneNode {
    public:
        SceneNode& operator=(SceneNode&) = delete;
        virtual ~SceneNode() = default;

        virtual void visitNode(NodeVisitor& visitor) {
            visitor.doSceneNode(*this);
        }

        virtual SceneNodeState& getState() = 0;
        [[nodiscard]] virtual const char* getIcon() const = 0;

        virtual Decorator<void, RenderContext&>& getRenderer() {
            static NullDecorator<void, RenderContext&> noDecorator;
            return noDecorator;
        }

        [[nodiscard]] virtual bool nodeDefaultOpen() const {
            return true;
        }

        [[nodiscard]] virtual std::optional<std::reference_wrapper<SceneNode>> getParent() const {
            return std::nullopt;
        }
        [[nodiscard]] virtual size_t getIndexInParent() const {
            return 0;
        }
        [[nodiscard]] virtual bool acceptsParent(SceneNode& parent) const {
            return false;
        }
        virtual bool bindParent(SceneNode& parent, size_t index) {
            return false;
        }
        virtual bool unbindParent() {
            return false;
        }

        [[nodiscard]] virtual size_t childCount() const {
            return 0;
        }
        [[nodiscard]] virtual std::optional<std::reference_wrapper<SceneNode>> getChild(size_t index) const {
            return std::nullopt;
        }
        virtual std::optional<size_t> addChild(std::unique_ptr<SceneNode>& child) {
            return std::nullopt;
        }
        virtual std::optional<size_t> moveChild(SceneNode& child) {
            return std::nullopt;
        }
        /// @brief removes a child object an returns its ownership
        /// @post under no circumstance the pointer might get out of scope
        ///         ensure once implemented to update every child index
        /// @return an optional that might hold the unique object pointer
        [[nodiscard]] virtual std::optional<std::unique_ptr<SceneNode>> removeChild(size_t index) {
            return std::nullopt;
        }

        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getNextSibling() const;
        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getPreviousSibling() const;
        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getObject() const;

        /// @brief tries to retrieve the unique pointer holding the object ownership
        /// @pre the object must have a parent object in the node tree
        /// @post the pointer must not get out of scope under no circumstance
        /// @return an optional that might hold the unique object pointer
        [[nodiscard]] std::optional<std::unique_ptr<SceneNode>> getObjectOwnership();

        /// @brief the node closest transform,
        /// if the object has a transform it produces the same output as getOwnedTransform
        [[nodiscard]] virtual std::optional<std::reference_wrapper<Transform>> getImmediateTransform();

        /// @brief the node owned transform if it has one
        [[nodiscard]] virtual std::optional<std::reference_wrapper<Transform>> getOwnedTransform() {
            return std::nullopt;
        }
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SCENENODE_H
