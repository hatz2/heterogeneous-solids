//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_UI_H
#define HETEROGENEOUS_SOLIDS_UI_H

#include <memory>
#include "WindowManager.h"
#include "Menu.h"
#include "DialogManager.h"

namespace hs {

    class UI {
    public:
        UI();

        WindowManager& getWindowManager();
        DialogManager& getDialogManager();
        Menu& getMainMenu();
        void render();
        void recoverFromError();
    private:
        std::unique_ptr<WindowManager> windowManager;
        std::unique_ptr<DialogManager> dialogManager;
        std::unique_ptr<Menu> mainMenu;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_UI_H
