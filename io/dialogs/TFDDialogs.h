//
// Created by Alberto Elorza Rubio on 08/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_TFDDIALOGS_H
#define HETEROGENEOUS_SOLIDS_TFDDIALOGS_H

#include "DialogsFacade.h"

namespace hs {

    class TFDDialogs: public DialogsFacade {
    public:
        TFDDialogs() = default;
        TFDDialogs(const TFDDialogs&) = default;

        std::optional<std::string> openFile(
            const std::string &title,
            const std::string &initialPath,
            std::initializer_list<std::pair<std::string, std::string>> filters
        ) override;
        std::optional<std::string> saveFile(
            const std::string &title,
            const std::string &initialPath,
            std::initializer_list<std::pair<std::string, std::string>> filters
        ) override;
        std::optional<std::string> selectFolder(
            const std::string &title,
            const std::string &initialPath
        ) override;
        void notify(
            const std::string &title,
            const std::string &body,
            DialogIcon icon
        ) override;
        bool message(
            const std::string &title,
            const std::string &body,
            DialogButton button,
            DialogIcon icon
        ) override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_TFDDIALOGS_H
