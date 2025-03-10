//
// Created by Alberto Elorza Rubio on 09/12/2023.
//

#include <imgui.h>

#include <utility>
#include "ContextMenuNode.h"

namespace hs {
    ContextMenuNode::ContextMenuNode(std::shared_ptr<ContextManager> contextManager) :
        contextManager(std::move(contextManager))
    {

    }

    void ContextMenuNode::renderMenuNode() {
        auto context = contextManager->borrowContext();
        if (context == nullptr) {
            ImGui::BeginDisabled();
            renderMenuNode(*contextManager->getDefaultContext());
            ImGui::EndDisabled();
        } else {
            renderMenuNode(*context);
        }
    }
} // hs