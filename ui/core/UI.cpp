//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#include <imgui_internal.h>
#include "UI.h"

namespace hs {
    UI::UI() :
        windowManager(std::make_unique<WindowManager>()),
        dialogManager(std::make_unique<DialogManager>()),
        mainMenu(std::make_unique<Menu>())
    {

    }

    WindowManager& UI::getWindowManager() {
        return *windowManager;
    }

    DialogManager& UI::getDialogManager() {
        return *dialogManager;
    }

    Menu& UI::getMainMenu() {
        return *mainMenu;
    }

    void UI::render() {
        if (!mainMenu->empty()) mainMenu->renderMainMenu();
        windowManager->render();
        dialogManager->render();
    }

    void UI::recoverFromError() {
        ImGui::ErrorCheckEndFrameRecover(nullptr);
    }
} // hs