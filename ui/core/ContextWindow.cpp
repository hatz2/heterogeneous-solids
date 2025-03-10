//
// Created by Alberto Elorza Rubio on 18/11/2023.
//

#include "ContextWindow.h"

#include <imgui.h>

namespace hs {
    ContextWindow::ContextWindow(std::string title, std::shared_ptr<ContextManager> contextManager) :
        Window(std::move(title)), contextManager(std::move(contextManager))
    {

    }

    void ContextWindow::renderBody() {
        auto context = contextManager->borrowContext();
        if (context == nullptr) {
            ImGui::BeginDisabled();
            renderBody(*contextManager->getDefaultContext());
            ImGui::EndDisabled();
        } else {
            renderBody(*context);
        }
    }
} // hs