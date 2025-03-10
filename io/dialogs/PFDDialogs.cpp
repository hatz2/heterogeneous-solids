//
// Created by Alberto Elorza Rubio on 25/11/2023.
//

#include "PFDDialogs.h"
#include <portable-file-dialogs.h>

namespace hs {
    std::vector<std::string> PFDDialogs::transformFilters(
        std::initializer_list<std::pair<std::string, std::string>> filters
    ) {
        std::vector<std::string> finalFilters;
        for (const auto& pair: filters) {
            finalFilters.push_back(pair.first + " (" + pair.second + ")");
            finalFilters.push_back(pair.second);
        }
        return finalFilters;
    }

    std::optional<std::string> PFDDialogs::openFile(
        const std::string& title,
        const std::string& initialPath,
        std::initializer_list<std::pair<std::string, std::string>> filters
    ) {
        auto openFile = pfd::open_file(title, initialPath, transformFilters(filters));
        auto results = openFile.result();
        if (!results.empty()) return results[0];
        return std::nullopt;
    }

    std::optional<std::string> PFDDialogs::saveFile(
        const std::string& title,
        const std::string& initialPath,
        std::initializer_list<std::pair<std::string, std::string>> filters
    ) {
        auto saveFile = pfd::save_file(title, initialPath, transformFilters(filters));
        auto result = saveFile.result();
        if (!result.empty()) return result;
        return std::nullopt;
    }

    std::optional<std::string> PFDDialogs::selectFolder(
        const std::string& title,
        const std::string& initialPath
    ) {
        auto selectFolder = pfd::select_folder(title, initialPath);
        auto result = selectFolder.result();
        if (!result.empty()) return result;
        return std::nullopt;
    }

    void PFDDialogs::notify(
        const std::string &title,
        const std::string &body,
        DialogIcon icon
    ) {
        pfd::icon pfdIcon;
        switch (icon) {
            case DialogIcon::Error:
                pfdIcon = pfd::icon::error;
                break;
            case DialogIcon::Warning:
                pfdIcon = pfd::icon::warning;
                break;
            case DialogIcon::Info:
            default:
                pfdIcon = pfd::icon::info;
                break;
        }
        pfd::notify(title, body, pfdIcon);
    }

    bool PFDDialogs::message(
        const std::string& title,
        const std::string& body,
        DialogButton button,
        DialogIcon icon
    ) {
        pfd::choice choice;
        switch (button) {
            case DialogButton::Ok:
                choice = pfd::choice::ok;
                break;
            case DialogButton::OkCancel:
                choice = pfd::choice::ok_cancel;
                break;
        }
        pfd::icon pfdIcon;
        switch (icon) {
            case DialogIcon::Error:
                pfdIcon = pfd::icon::error;
                break;
            case DialogIcon::Warning:
                pfdIcon = pfd::icon::warning;
                break;
            case DialogIcon::Info:
                pfdIcon = pfd::icon::info;
                break;
            case DialogIcon::Question:
                pfdIcon = pfd::icon::question;
                break;
        }
        return pfd::message(title, body, choice, pfdIcon).result() == pfd::button::ok;
    }
} // hs