//
// Created by Alberto Elorza Rubio on 29/12/2023.
//

#include "MessageDialog.h"

#include <utility>
#include <imgui.h>

#include "../components.h"

namespace hs {
    MessageDialog::MessageDialog(std::string title) : Dialog(std::move(title)) {

    }

    Dialog::DoClose MessageDialog::renderBody() {
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        ImGui::Text("%s", message.c_str());
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        const char* label = "Confirm";
        alignForWidth(ImGui::CalcTextSize(label).x + ImGui::GetStyle().FramePadding.x * 2.0f);
        return ImGui::Button(label);
    }

    const std::string& MessageDialog::getMessage() const {
        return message;
    }

    void MessageDialog::setMessage(const std::string& message) {
        MessageDialog::message = message;
    }
} // hs