//
// Created by Alberto Elorza Rubio on 29/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MESSAGEDIALOG_H
#define HETEROGENEOUS_SOLIDS_MESSAGEDIALOG_H

#include "../core/Dialog.h"

namespace hs {

    class MessageDialog: public Dialog {
    public:
        explicit MessageDialog(std::string title);

        [[nodiscard]] const std::string& getMessage() const;
        void setMessage(const std::string& message);
    private:
        DoClose renderBody() override;
        std::string message;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MESSAGEDIALOG_H
