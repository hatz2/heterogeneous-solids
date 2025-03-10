//
// Created by Alberto Elorza Rubio on 22/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_APPLYROTATIONCOMMAND_H
#define HETEROGENEOUS_SOLIDS_APPLYROTATIONCOMMAND_H

#include "../Command.h"
#include "../../scene/objects/Transform.h"

namespace hs {

    class ApplyRotationCommand: public Command, public MergeCommand<ApplyRotationCommand> {
    public:
        ApplyRotationCommand(Transform& transform, glm::vec3 rotation, bool absolute = false);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;

        bool doDiscard() override;

        bool merge(ApplyRotationCommand& other) override;
    private:
        static const std::string description;
        Transform& transform;
        glm::vec3 rotation;
        glm::vec3 newRotation;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_APPLYROTATIONCOMMAND_H
