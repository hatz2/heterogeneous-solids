//
// Created by Alberto Elorza Rubio on 09/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_CONTEXTMENUNODE_H
#define HETEROGENEOUS_SOLIDS_CONTEXTMENUNODE_H

#include "MenuNode.h"
#include "../../context/Context.h"
#include "../../context/ContextManager.h"

namespace hs {

    class ContextMenuNode: public MenuNode {
    public:
        explicit ContextMenuNode(std::shared_ptr<ContextManager> contextManager);
        void renderMenuNode() override;
    protected:
        std::shared_ptr<ContextManager> contextManager;
        virtual void renderMenuNode(const Context&) = 0;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CONTEXTMENUNODE_H
