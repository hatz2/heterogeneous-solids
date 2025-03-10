//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MENUITEM_H
#define HETEROGENEOUS_SOLIDS_MENUITEM_H

#include <string>
#include <functional>
#include "MenuNode.h"

namespace hs {

    class MenuItem: public MenuNode {
    public:
        MenuItem(std::string title, std::function<void()> action);

        void renderMenuNode() override;
    private:
        std::string title;
        std::function<void()> action;
    };

    class ConditionalMenuItem: public MenuItem {
    public:
        ConditionalMenuItem(std::string title, std::function<void()> action, std::function<bool()> active);

        void renderMenuNode() override;
    private:
        std::function<bool()> active;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MENUITEM_H
