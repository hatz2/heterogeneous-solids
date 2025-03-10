//
// Created by Alberto Elorza Rubio on 08/01/2024.
//

#include "ChangeMachiningProcessCommand.h"

namespace hs {
    ChangeMachiningProcessCommand::ChangeMachiningProcessCommand(
        const std::shared_ptr<TrimmingNode>& trimmedNode,
        MachiningProcess& process
    ) :
        trimmedNode(trimmedNode),
        previousProcess(trimmedNode->getOperation().getMachiningProcess()),
        newProcess(process),
        description(std::string("Set Machining Process: ") + process.name())
    {

    }

    void ChangeMachiningProcessCommand::execute() {
        trimmedNode->getOperation().setMachiningProcess(newProcess);
        trimmedNode->notifyRefresh();
    }

    void ChangeMachiningProcessCommand::undo() {
        trimmedNode->getOperation().setMachiningProcess(previousProcess);
        trimmedNode->notifyRefresh();
    }

    const std::string& ChangeMachiningProcessCommand::getDescription() {
        return description;
    }

    bool ChangeMachiningProcessCommand::doDiscard() {
        return &previousProcess.get() == &newProcess.get();
    }

    bool ChangeMachiningProcessCommand::merge(ChangeMachiningProcessCommand& other) {
        if (trimmedNode == other.trimmedNode) {
            newProcess = other.newProcess;
            description = other.description;
            return true;
        }
        return false;
    }
} // hs