//
// Created by Alberto Elorza Rubio on 13/12/2023.
//

#include "ContextDialog.h"

#include <imgui.h>

namespace hs {
    ContextDialog::ContextDialog(std::string title, std::shared_ptr<ContextManager> contextManager) :
        Dialog(std::move(title)), contextManager(std::move(contextManager))
    {

    }

    Dialog::DoClose ContextDialog::renderBody() {
        auto context = contextManager->borrowContext();
        if (context == nullptr) {
            ImGui::BeginDisabled();
            auto ret = renderBody(*contextManager->getDefaultContext());
            ImGui::EndDisabled();
            return ret;
        } else {
            return renderBody(*context);
        }
    }
} // hs