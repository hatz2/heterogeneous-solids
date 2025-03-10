//
// Created by Alberto Elorza Rubio on 25/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_COMMAND_H
#define HETEROGENEOUS_SOLIDS_COMMAND_H

#include <string>

namespace hs {

    class Command {
    public:
        /// @brief runs the action
        virtual void execute() = 0;
        /// @brief runs the inverse action
        virtual void undo() = 0;
        /// @brief returns the command description
        virtual const std::string& getDescription() = 0;
        /// @brief used whenever the execution result might have no effect:
        ///         - invalid actions detected at execution
        ///         - nullified actions, ej: the initial value is equals to the new one
        /// @returns whether the command must be taken off the history
        virtual bool doDiscard() {
            return false;
        }

        virtual ~Command() = default;
    };

    template <typename T>
    class MergeCommand {
    public:
        /// @brief tries to update the command properties with the other command properties
        /// @returns whether the merge was successful
        virtual bool merge(T& other) = 0;

        virtual ~MergeCommand() = default;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_COMMAND_H
