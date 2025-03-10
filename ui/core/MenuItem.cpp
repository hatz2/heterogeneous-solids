//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#include "MenuItem.h"

#include <imgui.h>
#include <utility>

namespace hs {
    MenuItem::MenuItem(std::string title, std::function<void()> action) :
            title(std::move(title)), action(std::move(action)) {

    }

    void MenuItem::renderMenuNode() {
        if (ImGui::MenuItem(title.c_str())) action();
    }

    ConditionalMenuItem::ConditionalMenuItem(
        std::string title, std::function<void()> action, std::function<bool()> active
    ) : MenuItem(std::move(title), std::move(action)), active(std::move(active)) {

    }

    void ConditionalMenuItem::renderMenuNode() {
        ImGui::BeginDisabled(!active());
        MenuItem::renderMenuNode();
        ImGui::EndDisabled();
    }
} // hs