//
// Created by Alberto Elorza Rubio on 07/02/2024.
//

#include "UpdateVisibilityCommand.h"

namespace hs {
    UpdateVisibilityCommand::UpdateVisibilityCommand(bool visible, VisibilityProp& visibilityProp) :
        before(visibilityProp.isVisible()), after(visible), visibilityProp(visibilityProp)
    {

    }

    void UpdateVisibilityCommand::execute() {
        visibilityProp.setVisible(after);
    }

    void UpdateVisibilityCommand::undo() {
        visibilityProp.setVisible(before);
    }

    const std::string& UpdateVisibilityCommand::getDescription() {
        return description;
    }

    bool UpdateVisibilityCommand::doDiscard() {
        return before == after;
    }

    bool UpdateVisibilityCommand::merge(UpdateVisibilityCommand& other) {
        if (&visibilityProp == &other.visibilityProp) {
            after = other.after;
            return true;
        }
        return false;
    }

    const std::string UpdateVisibilityCommand::description = "Updated visibility";
} // hs
