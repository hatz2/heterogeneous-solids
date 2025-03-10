//
// Created by Alberto Elorza Rubio on 27/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_RENDERPROCESSWINDOW_H
#define HETEROGENEOUS_SOLIDS_RENDERPROCESSWINDOW_H

#include "../core/ContextWindow.h"

namespace hs {

    class RenderProcessWindow: public ContextWindow {
    protected:
        void renderBody(const hs::Context &) override;
    public:
        RenderProcessWindow(std::string title, std::shared_ptr<ContextManager> contextManager);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_RENDERPROCESSWINDOW_H
