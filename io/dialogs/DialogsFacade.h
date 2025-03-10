//
// Created by Alberto Elorza Rubio on 25/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_DIALOGSFACADE_H
#define HETEROGENEOUS_SOLIDS_DIALOGSFACADE_H

#include <string>
#include <optional>
#include <vector>

namespace hs {

    enum class DialogIcon {
        Error,
        Warning,
        Info,
        Question
    };

    enum class DialogButton {
        Ok,
        OkCancel
    };

    class DialogsFacade {
    public:
        virtual std::optional<std::string> openFile(
            const std::string& title,
            const std::string& initialPath,
            std::initializer_list<std::pair<std::string, std::string>> filters
        ) = 0;
        virtual std::optional<std::string> saveFile(
            const std::string& title,
            const std::string& initialPath,
            std::initializer_list<std::pair<std::string, std::string>> filters
        ) = 0;
        virtual std::optional<std::string> selectFolder(
            const std::string& title,
            const std::string& initialPath
        ) = 0;
        virtual void notify(
            const std::string& title,
            const std::string& body,
            DialogIcon icon
        ) = 0;
        virtual bool message(
            const std::string& title,
            const std::string& body,
            DialogButton button,
            DialogIcon icon
        ) = 0;
        virtual ~DialogsFacade() = default;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_DIALOGSFACADE_H
