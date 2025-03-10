//
// Created by Alberto Elorza Rubio on 27/12/2023.
//

#include <spdlog/spdlog.h>
#include "AddObjectCommand.h"


namespace hs {
    AddObjectCommand::AddObjectCommand(std::unique_ptr<SceneNode> object, SceneNode& parent) :
        object(std::move(object)), index(0), parent(parent),
        description("Add Object")
    {

    }

    void AddObjectCommand::execute() {
        if (object == nullptr) {
            spdlog::warn("Unable to execute AddObjectCommand : No object");
            return;
        }

        if (auto idx = parent.addChild(object))
            index = idx.value();
        else
            spdlog::warn("Abnormal AddObjectCommand execution : Insertion returned no index");
    }

    void AddObjectCommand::undo() {
        if (auto obj = parent.removeChild(index)) {
            if (!obj.value()->unbindParent())
                spdlog::warn("AddObjectCommand undo : Unable to unbind parent from object");

            object = std::move(obj.value());
        } else
            spdlog::warn("Unable to undo AddObjectCommand : Index found no child");
    }

    const std::string& AddObjectCommand::getDescription() {
        return description;
    }
} // hs