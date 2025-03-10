//
// Created by Alberto Elorza Rubio on 27/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_ADDOBJECTCOMMAND_H
#define HETEROGENEOUS_SOLIDS_ADDOBJECTCOMMAND_H

#include "../Command.h"
#include "../../scene/objects/SceneNode.h"

#include <memory>
#include <string>

namespace hs {

    class AddObjectCommand: public Command {
    public:
        AddObjectCommand(std::unique_ptr<SceneNode> object, SceneNode& parent);

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

#endif //HETEROGENEOUS_SOLIDS_ADDOBJECTCOMMAND_H
