//
// Created by Alberto Elorza Rubio on 15/12/2023.
//

#include "TrimmingNode.h"

namespace hs {
    TrimmingNode::TrimmingNode() :
        state(std::make_unique<MutableSceneNodeState>("")),
        operation(std::make_unique<MachiningOperation>()), children()
    {
        state->setDefaultDescription(std::string(DescriptionPrefix) + operation->getMachiningProcess().name());
    }

    TrimmingNode::TrimmingNode(const TrimmingNode& other) :
        state(std::make_unique<MutableSceneNodeState>(*other.state)),
        operation(std::make_unique<MachiningOperation>(*other.operation)), children()
    {
        for (auto& child : other.children)
            children.push_back(std::make_shared<TrimmingNode>(*child));
    }

    std::shared_ptr<TrimmingNode> TrimmingNode::getOrCreate(size_t index) {
        while (index >= children.size()) children.push_back(std::make_unique<TrimmingNode>());
        return children.at(index);
    }

    void TrimmingNode::clear() {
        children.clear();
    }

    MachiningOperation& TrimmingNode::getOperation() {
        return *operation;
    }

    MutableSceneNodeState& TrimmingNode::getState() {
        return *state;
    }

    void TrimmingNode::swapContentWith(TrimmingNode& other) {
        auto extractedState = std::move(state);
        auto extractedChildren = std::move(children);
        auto extractedOperation = std::move(operation);

        state = std::move(other.state);
        children = std::move(other.children);
        operation = std::move(other.operation);

        other.state = std::move(extractedState);
        other.children = std::move(extractedChildren);
        other.operation = std::move(extractedOperation);

        notifyRefresh();
        other.notifyRefresh();
    }

    void TrimmingNode::notifyRefresh() {
        state->setDefaultDescription(std::string(DescriptionPrefix) + operation->getMachiningProcess().name());
        updateSubject();
    }

    const char* TrimmingNode::DescriptionPrefix = "Trimmed Cell: ";
} // hs