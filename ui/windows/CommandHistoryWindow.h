//
// Created by Alberto Elorza Rubio on 25/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_COMMANDHISTORYWINDOW_H
#define HETEROGENEOUS_SOLIDS_COMMANDHISTORYWINDOW_H

#include "../core/ContextWindow.h"

namespace hs {

    class CommandHistoryWindow: public ContextWindow {
    public:
        CommandHistoryWindow(std::string title, std::shared_ptr<ContextManager> contextManager);
    protected:
        void render() override;
        void renderBody(const hs::Context&) override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_COMMANDHISTORYWINDOW_H
