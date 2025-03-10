//
// Created by Alberto Elorza Rubio on 01/02/2024.
//

#include "ToggleWindowsMenu.h"

namespace hs {
    ToggleWindowsMenu::ToggleWindowsMenu(WindowManager& windowManager) : windowManager(windowManager) {

    }

    void ToggleWindowsMenu::renderMenuNode() {
        if (ImGui::BeginMenu("Toggle")) {
            for (const auto& window: windowManager.getStaticWindows()) {
                if (ImGui::MenuItem(window->getTitle().c_str(), nullptr, window->isOpen()))
                    window->toggleOpen();
            }
            ImGui::EndMenu();
        }
    }
} // hs