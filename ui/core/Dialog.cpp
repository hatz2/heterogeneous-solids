//
// Created by Alberto Elorza Rubio on 12/12/2023.
//

#include "Dialog.h"

#include <imgui.h>

namespace hs {
    Dialog::Dialog(std::string title) : title(std::move(title)), requestShow(false) {

    }

    void Dialog::render() {
        if (requestShow) {
            ImGui::OpenPopup(title.c_str());
            requestShow = false;
        }
        bool open = true;
        if (ImGui::BeginPopupModal(title.c_str(), &open, ImGuiWindowFlags_AlwaysAutoResize)) {
            if (!open || renderBody()) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }

    void Dialog::show() {
        requestShow = true;
    }

    void Dialog::reset() {

    }
} // hs