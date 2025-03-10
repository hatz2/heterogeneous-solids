//
// Created by Alberto Elorza Rubio on 22/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_APPLYTRANSLATIONCOMMAND_H
#define HETEROGENEOUS_SOLIDS_APPLYTRANSLATIONCOMMAND_H

#include "../Command.h"
#include "../../scene/objects/Transform.h"

namespace hs {

    class ApplyTranslationCommand: public Command, public MergeCommand<ApplyTranslationCommand> {
    public:
        ApplyTranslationCommand(Transform& transform, glm::vec3 translation, bool absolute = false);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;

        bool doDiscard() override;

        bool merge(ApplyTranslationCommand &other) override;
    private:
        static const std::string description;
        Transform& transform;
        glm::vec3 translation;
        glm::vec3 newTranslation;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_APPLYTRANSLATIONCOMMAND_H
