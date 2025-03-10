//
// Created by Alberto Elorza Rubio on 08/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_OBJECTWINDOW_H
#define HETEROGENEOUS_SOLIDS_OBJECTWINDOW_H

#include "../core/ContextWindow.h"

namespace hs {

    class ObjectWindow: public ContextWindow {
    public:
        ObjectWindow(std::string title, std::shared_ptr<ContextManager> contextManager);
    protected:
        void renderBody(const Context &) override;
    private:
        static void renderHeader(const Context&, SceneNodeState&);
        static void renderTree(const Context&, SceneNode&);
        static void renderHeterogeneousSolid(const Context&, HeterogeneousSolid&);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_OBJECTWINDOW_H
