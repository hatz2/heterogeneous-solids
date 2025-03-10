//
// Created by Alberto Elorza Rubio on 29/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_TRIMMINGWINDOW_H
#define HETEROGENEOUS_SOLIDS_TRIMMINGWINDOW_H

#include "../core/ContextWindow.h"

namespace hs {

    class TrimmingWindow: public ContextWindow {
    public:
        TrimmingWindow(std::string title, std::shared_ptr<ContextManager> contextManager);
    protected:
        void renderBody(const Context&) override;
    private:
        static void renderMenu(const Context&, TrimmedCell&);
        static void renderTrimmedCell(const Context&, TrimmedCell&);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_TRIMMINGWINDOW_H
