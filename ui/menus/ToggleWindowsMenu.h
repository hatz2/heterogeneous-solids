//
// Created by Alberto Elorza Rubio on 01/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_TOGGLEWINDOWSMENU_H
#define HETEROGENEOUS_SOLIDS_TOGGLEWINDOWSMENU_H

#include "../core/MenuNode.h"
#include "../core/WindowManager.h"

namespace hs {

    class ToggleWindowsMenu: public MenuNode {
    public:
        explicit ToggleWindowsMenu(WindowManager& windowManager);
    protected:
        void renderMenuNode() override;
    private:
        WindowManager& windowManager;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_TOGGLEWINDOWSMENU_H
