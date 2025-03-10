//
// Created by Alberto Elorza Rubio on 22/02/2024.
//

#include "ApplyTranslationCommand.h"

#include <glm/gtc/epsilon.hpp>
#include <glm/ext/scalar_constants.hpp>

namespace hs {
    ApplyTranslationCommand::ApplyTranslationCommand(Transform& transform, glm::vec3 translation, bool absolute) :
        transform(transform), translation(transform.getTranslation()),
        newTranslation(absolute ? translation : transform.getTranslation() + translation)
    {

    }

    void ApplyTranslationCommand::execute() {
        transform.setTranslation(newTranslation);
    }

    void ApplyTranslationCommand::undo() {
        transform.setTranslation(translation);
    }

    const std::string& ApplyTranslationCommand::getDescription() {
        return description;
    }

    bool ApplyTranslationCommand::doDiscard() {
        return glm::all(glm::epsilonEqual(translation, newTranslation, glm::epsilon<float>()));
    }

    bool ApplyTranslationCommand::merge(ApplyTranslationCommand& other) {
        if (&other.transform == &transform) {
            newTranslation = other.newTranslation;
            return true;
        }
        return false;
    }

    const std::string ApplyTranslationCommand::description = "Transform Translation";
} // hs