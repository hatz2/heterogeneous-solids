//
// Created by Alberto Elorza Rubio on 22/02/2024.
//

#include "ApplyScaleCommand.h"

#include <glm/gtc/epsilon.hpp>
#include <glm/ext/scalar_constants.hpp>

namespace hs {
    ApplyScaleCommand::ApplyScaleCommand(Transform& transform, glm::vec3 scale, bool absolute) :
        transform(transform), scale(transform.getScale()),
        newScale(absolute ? scale : transform.getScale() * scale)
    {

    }

    void ApplyScaleCommand::execute() {
        transform.setScale(newScale);
    }

    void ApplyScaleCommand::undo() {
        transform.setScale(scale);
    }

    const std::string& ApplyScaleCommand::getDescription() {
        return description;
    }

    bool ApplyScaleCommand::doDiscard() {
        return glm::all(glm::epsilonEqual(scale, newScale, glm::epsilon<float>()));
    }

    bool ApplyScaleCommand::merge(ApplyScaleCommand& other) {
        if (&other.transform == &transform) {
            newScale = other.newScale;
            return true;
        }
        return false;
    }

    const std::string ApplyScaleCommand::description = "Transform Scale";
} // hs