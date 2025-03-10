//
// Created by Alberto Elorza Rubio on 07/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_COMMANDGROUP_H
#define HETEROGENEOUS_SOLIDS_COMMANDGROUP_H

#include "../Command.h"

#include <vector>
#include <memory>

namespace hs {

    class CommandGroup: public Command {
    public:
        explicit CommandGroup(std::vector<std::unique_ptr<Command>> commands);
        CommandGroup(std::string description, std::vector<std::unique_ptr<Command>> commands);
        CommandGroup(const CommandGroup&) = delete;

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;
    private:
        std::vector<std::unique_ptr<Command>> commands;
        std::string description;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_COMMANDGROUP_H
