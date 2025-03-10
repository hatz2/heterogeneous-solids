//
// Created by Alberto Elorza Rubio on 30/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_TREEVIEWWINDOW_H
#define HETEROGENEOUS_SOLIDS_TREEVIEWWINDOW_H

#include "../core/ContextWindow.h"

namespace hs {

    class TreeViewWindow: public ContextWindow {
    public:
        TreeViewWindow(std::string name, std::shared_ptr<ContextManager> contextManager);
    protected:
        void renderBody(const Context&) override;
    private:
        void doObjectTree(const Context& context, SceneNode& object);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_TREEVIEWWINDOW_H
