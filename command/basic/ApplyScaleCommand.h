//
// Created by Alberto Elorza Rubio on 22/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_APPLYSCALECOMMAND_H
#define HETEROGENEOUS_SOLIDS_APPLYSCALECOMMAND_H

#include "../Command.h"
#include "../../scene/objects/Transform.h"

namespace hs {

    class ApplyScaleCommand: public Command, public MergeCommand<ApplyScaleCommand> {
    public:
        ApplyScaleCommand(Transform& transform, glm::vec3 scale, bool absolute = false);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;

        bool doDiscard() override;

        bool merge(ApplyScaleCommand& other) override;
    private:
        static const std::string description;
        Transform& transform;
        glm::vec3 scale;
        glm::vec3 newScale;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_APPLYSCALECOMMAND_H
