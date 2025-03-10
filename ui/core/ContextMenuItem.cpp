//
// Created by Alberto Elorza Rubio on 01/02/2024.
//

#include "ContextMenuItem.h"

namespace hs {
    ContextMenuItem::ContextMenuItem(
        std::string title,
        std::shared_ptr<ContextManager> contextManager,
        std::function<void(const Context&)> action
    ) : ContextMenuNode(std::move(contextManager)), title(std::move(title)), action(action) {

    }

    void ContextMenuItem::renderMenuNode(const Context& context) {
        action(context);
    }
} // hs