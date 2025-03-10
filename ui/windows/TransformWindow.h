//
// Created by Alberto Elorza Rubio on 15/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_TRANSFORMWINDOW_H
#define HETEROGENEOUS_SOLIDS_TRANSFORMWINDOW_H

#include "../core/ContextWindow.h"

namespace hs {

    class TransformWindow: public ContextWindow {
    public:
        explicit TransformWindow(std::string title, std::shared_ptr<ContextManager> contextManager);
    protected:
        void renderBody(const Context&) override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_TRANSFORMWINDOW_H
