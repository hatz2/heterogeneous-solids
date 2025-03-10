//
// Created by Alberto Elorza Rubio on 01/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_EDITMENU_H
#define HETEROGENEOUS_SOLIDS_EDITMENU_H

#include "../core/ContextMenuNode.h"

namespace hs {

    class EditMenu: public ContextMenuNode {
    public:
        explicit EditMenu(std::shared_ptr<ContextManager> manager);
    protected:
        void renderMenuNode(const Context& context) override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_EDITMENU_H
