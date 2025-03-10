//
// Created by Alberto Elorza Rubio on 04/02/2024.
//

#include "SwapTrimmingNodeContentCommand.h"

namespace hs {
    SwapTrimmingNodeContentCommand::SwapTrimmingNodeContentCommand(
        std::shared_ptr<TrimmingNode> trimmingNode,
        std::shared_ptr<TrimmingNode> newContent
    ) : trimmingNode(std::move(trimmingNode)), newContent(std::move(newContent)) {

    }

    void SwapTrimmingNodeContentCommand::execute() {
        trimmingNode->swapContentWith(*newContent);
    }

    void SwapTrimmingNodeContentCommand::undo() {
        trimmingNode->swapContentWith(*newContent);
    }

    const std::string& SwapTrimmingNodeContentCommand::getDescription() {
        return description;
    }

    const std::string SwapTrimmingNodeContentCommand::description = "Swapped two nodes content";
} // hs