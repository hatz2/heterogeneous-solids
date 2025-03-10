//
// Created by Alberto Elorza Rubio on 08/12/2023.
//

#include "TFDDialogs.h"

#include "../../third_party/tinyfiledialogs/tinyfiledialogs.h"

namespace hs {
    std::optional<std::string> TFDDialogs::openFile(
        const std::string &title,
        const std::string &initialPath,
        std::initializer_list<std::pair<std::string, std::string>> filters
    ) {
        // TODO: Apply filters
        auto* result = tinyfd_openFileDialog(
            title.c_str(), (initialPath + "/").c_str(), 0, nullptr, nullptr, 0
        );
        if (result) {
            std::string value(result);
            free(result);
            return value;
        }
        return std::nullopt;
    }

    std::optional<std::string> TFDDialogs::saveFile(
        const std::string &title,
        const std::string &initialPath,
        std::initializer_list<std::pair<std::string, std::string>> filters
    ) {
        // TODO: Apply filters
        auto* result = tinyfd_saveFileDialog(
            title.c_str(), (initialPath + "/").c_str(), 0, nullptr, nullptr
        );
        if (result) {
            std::string value(result);
            free(result);
            return value;
        }
        return std::nullopt;
    }

    std::optional<std::string> TFDDialogs::selectFolder(
        const std::string &title,
        const std::string &initialPath
    ) {
        auto* result = tinyfd_selectFolderDialog(
            title.c_str(), (initialPath + "//").c_str()
        );
        if (result) {
            std::string value(result);
            free(result);
            return value;
        }
        return std::nullopt;
    }

    void TFDDialogs::notify(
        const std::string &title,
        const std::string &body,
        DialogIcon icon
    ) {
        const char* tfdIcon;
        switch (icon) {
            case DialogIcon::Error:
                tfdIcon = "Error";
                break;
            case DialogIcon::Warning:
                tfdIcon = "Warning";
                break;
            case DialogIcon::Info:
            default:
                tfdIcon = "Info";
                break;
        }
        tinyfd_notifyPopup(
            title.c_str(), body.c_str(), tfdIcon
        );
    }

    bool TFDDialogs::message(
        const std::string &title,
        const std::string &body,
        DialogButton button,
        DialogIcon icon
    ) {
        const char* tfdIcon;
        switch (icon) {
            case DialogIcon::Question:
                tfdIcon = "Question";
                break;
            case DialogIcon::Warning:
                tfdIcon = "Warning";
                break;
            case DialogIcon::Info:
            default:
                tfdIcon = "Info";
                break;
        }
        const char* tfdType;
        switch (button) {
            case DialogButton::Ok:
                tfdType = "ok";
                break;
            case DialogButton::OkCancel:
                tfdType = "okcancel";
                break;
        }
        return tinyfd_messageBox(
            title.c_str(), body.c_str(), tfdType, tfdIcon, 0
        ) == 1;
    }
} // hs