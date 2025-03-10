//
// Created by Alberto Elorza Rubio on 13/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_CONTEXTDIALOG_H
#define HETEROGENEOUS_SOLIDS_CONTEXTDIALOG_H

#include "Dialog.h"
#include "../../context/Context.h"
#include "../../context/ContextManager.h"

namespace hs {

    class ContextDialog: public Dialog {
    public:
        ContextDialog(std::string title, std::shared_ptr<ContextManager> contextManager);
    protected:
        std::shared_ptr<ContextManager> contextManager;
        DoClose renderBody() override;
        virtual DoClose renderBody(const Context& context) = 0;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CONTEXTDIALOG_H
