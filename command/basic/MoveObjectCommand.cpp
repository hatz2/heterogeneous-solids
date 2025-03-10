//
// Created by Alberto Elorza Rubio on 08/02/2024.
//

#include "MoveObjectCommand.h"

namespace hs {
    MoveObjectCommand::MoveObjectCommand(SceneNode& targetChild, SceneNode& targetParent) :
        targetChild(targetChild),
        targetParent(targetParent),
        originalParent(targetChild.getParent()),
        valid(false)
    {

    }

    void MoveObjectCommand::execute() {
        // Only will work if there is already a parent and is not the target one
        if (!originalParent || &originalParent.value().get() == &targetParent.get()) return;

        std::optional<std::reference_wrapper<SceneNode>> parent = targetParent.get();
        while (parent) {
            // Circular parent (child is the parent of the parent)
            if (&parent.value().get() == &targetChild.get()) return;
            parent = parent->get().getParent();
        }

        valid = targetParent.get().moveChild(targetChild).has_value();
    }

    void MoveObjectCommand::undo() {
        // Only will work if there is already a parent and is not the target one
        if (!originalParent || &originalParent.value().get() == &targetParent.get()) return;
        originalParent.value().get().moveChild(targetChild);
    }

    const std::string& MoveObjectCommand::getDescription() {
        return description;
    }

    bool MoveObjectCommand::doDiscard() {
        return !valid;
    }

    const std::string MoveObjectCommand::description = "Move object";
} // hs