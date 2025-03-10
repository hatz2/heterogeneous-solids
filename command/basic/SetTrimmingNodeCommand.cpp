//
// Created by Alberto Elorza Rubio on 09/01/2024.
//

#include "SetTrimmingNodeCommand.h"

namespace hs {
    SetTrimmingNodeCommand::SetTrimmingNodeCommand(
        TrimmedCell& trimmedCell, const std::shared_ptr<TrimmingNode>& trimmingNode
    ) :
        description(std::string("Set Node: ") + trimmingNode->getState().getDescriptionOrDefault()),
        trimmedCell(trimmedCell),
        previousNode(trimmedCell.getActiveNode()),
        newNode(trimmingNode)
    {

    }

    void SetTrimmingNodeCommand::execute() {
        trimmedCell.setActiveNode(newNode);
    }

    void SetTrimmingNodeCommand::undo() {
        trimmedCell.setActiveNode(previousNode);
    }

    const std::string& SetTrimmingNodeCommand::getDescription() {
        return description;
    }

    bool SetTrimmingNodeCommand::doDiscard() {
        return previousNode == newNode;
    }

    bool SetTrimmingNodeCommand::merge(SetTrimmingNodeCommand& other) {
        if (&other.trimmedCell == &trimmedCell) {
            newNode = other.newNode;
            return true;
        }
        return false;
    }
} // hs