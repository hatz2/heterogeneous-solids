//
// Created by Alberto Elorza Rubio on 22/02/2024.
//

#include "ApplyRotationCommand.h"

#include <glm/gtc/epsilon.hpp>
#include <glm/ext/scalar_constants.hpp>

namespace hs {
    ApplyRotationCommand::ApplyRotationCommand(Transform& transform, glm::vec3 rotation, bool absolute) :
        transform(transform), rotation(transform.getRotation()),
        newRotation(absolute ? rotation : transform.getRotation() + rotation)
    {

    }

    void ApplyRotationCommand::execute() {
        transform.setRotation(newRotation);
    }

    void ApplyRotationCommand::undo() {
        transform.setRotation(rotation);
    }

    const std::string& ApplyRotationCommand::getDescription() {
        return description;
    }

    bool ApplyRotationCommand::doDiscard() {
        return glm::all(glm::epsilonEqual(rotation, newRotation, glm::epsilon<float>()));
    }

    bool ApplyRotationCommand::merge(ApplyRotationCommand& other) {
        if (&other.transform == &transform) {
            newRotation = other.newRotation;
            return true;
        }
        return false;
    }

    const std::string ApplyRotationCommand::description = "Transform Rotation";
} // hs