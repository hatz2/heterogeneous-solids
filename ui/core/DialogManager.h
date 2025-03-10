//
// Created by Alberto Elorza Rubio on 12/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_DIALOGMANAGER_H
#define HETEROGENEOUS_SOLIDS_DIALOGMANAGER_H

#include <memory>
#include <vector>
#include "Dialog.h"

namespace hs {

    class DialogManager {
    public:
        DialogManager() = default;

        void render();

        void addDialog(const std::shared_ptr<Dialog>& dialog);
    private:
        std::vector<std::shared_ptr<Dialog>> dialogs;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_DIALOGMANAGER_H
