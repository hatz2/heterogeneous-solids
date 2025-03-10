//
// Created by Alberto Elorza Rubio on 27/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_REMOVEOBJECTCOMMAND_H
#define HETEROGENEOUS_SOLIDS_REMOVEOBJECTCOMMAND_H

#include "../Command.h"
#include "../../scene/objects/SceneNode.h"

#include <memory>
#include <string>

namespace hs {

    class RemoveObjectCommand: public Command {
    public:
        RemoveObjectCommand(size_t index, SceneNode& parent);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;
    private:
        std::unique_ptr<SceneNode> object;
        size_t index;
        SceneNode& parent;
        std::string description;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_REMOVEOBJECTCOMMAND_H
