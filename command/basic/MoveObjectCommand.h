//
// Created by Alberto Elorza Rubio on 08/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_MOVEOBJECTCOMMAND_H
#define HETEROGENEOUS_SOLIDS_MOVEOBJECTCOMMAND_H

#include "../Command.h"
#include "../../scene/objects/SceneNode.h"

namespace hs {

    class MoveObjectCommand: public Command {
    public:
        MoveObjectCommand(SceneNode& targetChild, SceneNode& targetParent);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;

        bool doDiscard() override;
    private:
        std::reference_wrapper<SceneNode> targetChild;
        std::reference_wrapper<SceneNode> targetParent;
        std::optional<std::reference_wrapper<SceneNode>> originalParent;
        bool valid;

        static const std::string description;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MOVEOBJECTCOMMAND_H
