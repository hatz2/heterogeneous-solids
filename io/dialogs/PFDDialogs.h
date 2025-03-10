//
// Created by Alberto Elorza Rubio on 25/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_PFDDIALOGS_H
#define HETEROGENEOUS_SOLIDS_PFDDIALOGS_H

#include "DialogsFacade.h"

namespace hs {

    class PFDDialogs: public DialogsFacade {
    private:
        static std::vector<std::string> transformFilters(
            std::initializer_list<std::pair<std::string, std::string>> filters
        );
    public:
        PFDDialogs() = default;
        PFDDialogs(const PFDDialogs&) = default;

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

#endif //HETEROGENEOUS_SOLIDS_PFDDIALOGS_H
