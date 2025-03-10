//
// Created by Alberto Elorza Rubio on 27/12/2023.
//

#include <spdlog/spdlog.h>
#include "RemoveObjectCommand.h"

namespace hs {
    RemoveObjectCommand::RemoveObjectCommand(size_t index, SceneNode& parent) :
        object(nullptr), index(index), parent(parent),
        description("Remove Object")
    {

    }

    void RemoveObjectCommand::execute() {
        if (auto obj = parent.removeChild(index)) {
            if (!obj.value()->unbindParent())
                spdlog::warn("RemoveObjectCommand : Unable to unbind parent from object");

            object = std::move(obj.value());
        } else
            spdlog::warn("Unable to execute RemoveObjectCommand : Index found no child");
    }

    void RemoveObjectCommand::undo() {
        if (object == nullptr) {
            spdlog::warn("Unable to undo RemoveObjectCommand : No object");
            return;
        }

        if (auto idx = parent.addChild(object))
            index = idx.value();
        else
            spdlog::warn("Abnormal AddObjectCommand undo : Insertion returned no index");
    }

    const std::string& RemoveObjectCommand::getDescription() {
        return description;
    }
} // hs