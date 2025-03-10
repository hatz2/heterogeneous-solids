//
// Created by Alberto Elorza Rubio on 08/01/2024.
//

#include "ChangeMachiningParamCommand.h"

namespace hs {
    ChangeMachiningParamCommand::ChangeMachiningParamCommand(
        const std::shared_ptr<TrimmingNode>& trimmedNode, const std::string& paramName, float value
    ) :
        trimmedNode(trimmedNode),
        paramName(paramName),
        previousValue(trimmedNode->getOperation().getMachiningParams().at(paramName)),
        newValue(value),
        description(std::string("Set value of: ") + paramName)
    {

    }

    void ChangeMachiningParamCommand::execute() {
        trimmedNode->getOperation().getMachiningParams().at(paramName).set(newValue);
        trimmedNode->notifyRefresh();
    }

    void ChangeMachiningParamCommand::undo() {
        trimmedNode->getOperation().getMachiningParams().at(paramName).set(previousValue);
        trimmedNode->notifyRefresh();
    }

    const std::string& ChangeMachiningParamCommand::getDescription() {
        return description;
    }

    bool ChangeMachiningParamCommand::doDiscard() {
        return abs(previousValue - newValue) <= FLT_EPSILON;
    }

    bool ChangeMachiningParamCommand::merge(ChangeMachiningParamCommand& other) {
        if (trimmedNode == other.trimmedNode && paramName == other.paramName) {
            newValue = other.newValue;
            return true;
        }
        return false;
    }
} // hs