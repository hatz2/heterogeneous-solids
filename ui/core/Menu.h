//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MENU_H
#define HETEROGENEOUS_SOLIDS_MENU_H

#include <vector>
#include <memory>
#include "MenuItem.h"

namespace hs {

    class MenuSeparator: public MenuNode {
    public:
        MenuSeparator() = default;
    protected:
        void renderMenuNode() override;
    };

    class Menu: public MenuNode {
    public:
        explicit Menu(std::string title = DEFAULT_TITLE);

        void renderMenuNode() override;

        void addItem(std::shared_ptr<MenuNode> node);
        void addSeparator();

        void renderMainMenu();
        void renderWindowMenu();
        void renderContextMenu();

        [[nodiscard]] bool empty() const;
    private:
        static const char* DEFAULT_TITLE;
        std::string title;
        std::vector<std::shared_ptr<MenuNode>> nodes;
        void renderNodes();
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MENU_H
