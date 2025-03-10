//
// Created by Alberto Elorza Rubio on 12/12/2023.
//

#include "DialogManager.h"

namespace hs {
    void DialogManager::render() {
        for (auto& dialog : dialogs)
            dialog->render();
    }

    void DialogManager::addDialog(const std::shared_ptr<Dialog>& dialog) {
        dialogs.push_back(dialog);
    }
} // hs