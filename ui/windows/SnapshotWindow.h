//
// Created by Alberto Elorza Rubio on 28/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SNAPSHOTWINDOW_H
#define HETEROGENEOUS_SOLIDS_SNAPSHOTWINDOW_H

#include "../core/ContextWindow.h"

namespace hs {

    class SnapshotWindow: public ContextWindow {
    public:
        SnapshotWindow(std::string title, std::shared_ptr<ContextManager> contextManager);
    protected:
        void renderBody(const hs::Context&) override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SNAPSHOTWINDOW_H
