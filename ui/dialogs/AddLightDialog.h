//
// Created by Alberto Elorza Rubio on 13/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_ADDLIGHTDIALOG_H
#define HETEROGENEOUS_SOLIDS_ADDLIGHTDIALOG_H

#include "../core/ContextDialog.h"

namespace hs {

    class AddLightDialog: public ContextDialog {
    public:
        AddLightDialog(std::string title, std::shared_ptr<ContextManager> contextManager);
        void reset() override;
    protected:
        DoClose renderBody(const hs::Context &context) override;
    private:
        static const std::string DefaultName;
        std::string name;
        LightType lightType;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_ADDLIGHTDIALOG_H
