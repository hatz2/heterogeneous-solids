//
// Created by Alberto Elorza Rubio on 07/02/2024.
//

#include "UpdateDescriptionCommand.h"

namespace hs {
    UpdateDescriptionCommand::UpdateDescriptionCommand(std::string newDescription, DescriptionProp& descriptionProp) :
        before(descriptionProp.getDescription()), after(std::move(newDescription)), descriptionProp(descriptionProp)
    {

    }

    void UpdateDescriptionCommand::execute() {
        descriptionProp.setDescription(after);
    }

    void UpdateDescriptionCommand::undo() {
        descriptionProp.setDescription(before);
    }

    const std::string& UpdateDescriptionCommand::getDescription() {
        return description;
    }

    bool UpdateDescriptionCommand::doDiscard() {
        return before == after;
    }

    bool UpdateDescriptionCommand::merge(UpdateDescriptionCommand& other) {
        if (&descriptionProp == &other.descriptionProp) {
            after = other.after;
            return true;
        }
        return false;
    }

    const std::string UpdateDescriptionCommand::description = "Updated description";
} // hs