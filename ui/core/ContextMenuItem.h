//
// Created by Alberto Elorza Rubio on 01/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_CONTEXTMENUITEM_H
#define HETEROGENEOUS_SOLIDS_CONTEXTMENUITEM_H

#include "ContextMenuNode.h"

namespace hs {

    class ContextMenuItem: public ContextMenuNode {
    public:
        ContextMenuItem(
            std::string title,
            std::shared_ptr<ContextManager> contextManager,
            std::function<void(const Context&)> action
        );
    protected:
        void renderMenuNode(const Context&) override;
    private:
        std::string title;
        std::function<void(const Context&)> action;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CONTEXTMENUITEM_H
