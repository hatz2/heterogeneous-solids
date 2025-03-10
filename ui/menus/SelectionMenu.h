//
// Created by Alberto Elorza Rubio on 18/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SELECTIONMENU_H
#define HETEROGENEOUS_SOLIDS_SELECTIONMENU_H

#include "../core/ContextMenuNode.h"
#include "../core/UI.h"
#include "../core/Menu.h"
#include "../dialogs/AddCellsDialog.h"

namespace hs {

    class SelectionMenu: public ContextMenuNode {
    public:
        SelectionMenu(std::shared_ptr<ContextManager> contextManager, UI& ui);

        void renderMenuNode(const hs::Context&) override;

    private:

        class SelectionVisitor: public NodeVisitor {
        public:
            explicit SelectionVisitor(const Context& context, SelectionMenu* selectionMenu);

            void doGroupNode(GroupNode& group3D) override;
            void doHeterogeneousSolid(hs::HeterogeneousSolid& heterogeneousSolid) override;
            void doCell(Cell& cell) override;
        private:
            const Context& context;
            SelectionMenu* selectionMenu;
        };

    protected:
        // DIALOGS

        std::shared_ptr<AddCellsDialog> addCellsDialog;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SELECTIONMENU_H
