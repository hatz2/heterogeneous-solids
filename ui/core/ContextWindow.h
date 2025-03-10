//
// Created by Alberto Elorza Rubio on 18/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_CONTEXTWINDOW_H
#define HETEROGENEOUS_SOLIDS_CONTEXTWINDOW_H

#include <memory>
#include "Window.h"
#include "../../context/Context.h"
#include "../../context/ContextManager.h"

namespace hs {

    class ContextWindow: public Window {
    public:
        ContextWindow(std::string title, std::shared_ptr<ContextManager> contextManager);
    protected:
        std::shared_ptr<ContextManager> contextManager;
        virtual void renderBody(const Context&) = 0;
        void renderBody() override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CONTEXTWINDOW_H
