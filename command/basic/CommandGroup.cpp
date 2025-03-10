//
// Created by Alberto Elorza Rubio on 07/01/2024.
//

#include "CommandGroup.h"

#include <utility>
#include <spdlog/spdlog.h>

namespace hs {
    CommandGroup::CommandGroup(std::vector<std::unique_ptr<Command>> commands) :
        description(
            CommandGroup::commands.size() == 1
            ? CommandGroup::commands.front()->getDescription()
            : std::to_string(CommandGroup::commands.size()) + " actions"
        ), commands(std::move(commands))
    {

    }

    CommandGroup::CommandGroup(std::string description, std::vector<std::unique_ptr<Command>> commands) :
        description(std::move(description)), commands(std::move(commands))
    {

    }

    void CommandGroup::execute() {
        for (auto& command : commands) {
            spdlog::debug("CommandGroup => Executing Subcommand: {}", command->getDescription());
            command->execute();
        }
    }

    void CommandGroup::undo() {
        for (auto it = commands.rbegin(); it < commands.rend(); it++) {
            auto& command = *it;
            spdlog::debug("CommandGroup => Undoing Subcommand: {}", command->getDescription());
            command->undo();
        }
    }

    const std::string& CommandGroup::getDescription() {
        return description;
    }
} // hs