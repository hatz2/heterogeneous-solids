//
// Created by Alberto Elorza Rubio on 26/12/2023.
//

#include "CommandHistory.h"

namespace hs {
    CommandHistory::CommandHistory() : history(), offset(0), checkpoint(0) {

    }

    bool CommandHistory::canUndo() const {
        return history.size() > offset;
    }

    bool CommandHistory::canRedo() const {
        return offset > 0;
    }

    size_t CommandHistory::count() const {
        return history.size();
    }

    bool CommandHistory::empty() const {
        return history.empty();
    }

    bool CommandHistory::updated() const {
        return history.size() - offset != checkpoint;
    }

    void CommandHistory::setCheckpoint() {
        checkpoint = history.size() - offset;
    }

    void CommandHistory::undo() {
        if (canUndo()) {
            offset++;
            auto& command = history[history.size() - offset];
            spdlog::debug("Undoing Command: {}", command->getDescription());
            command->undo();
            executionSubject.updateSubject(CommandHistoryEvent::Undo, *command);
        }
    }

    void CommandHistory::redo() {
        if (canRedo()) {
            auto& command = history[history.size() - offset];
            spdlog::debug("Redoing Command: {}", command->getDescription());
            command->execute();
            offset--;
            executionSubject.updateSubject(CommandHistoryEvent::Redo, *command);
        }
    }

    void CommandHistory::clear() {
        offset = 0;
        history.clear();
        spdlog::debug("Command history cleared");
    }

    CommandHistory::Container::iterator CommandHistory::begin() {
        return history.begin();
    }

    CommandHistory::Container::iterator CommandHistory::done() {
        return history.end() - offset;
    }

    CommandHistory::Container::iterator CommandHistory::end() {
        return history.end();
    }

    Subject<CommandHistoryEvent, const Command&>& CommandHistory::getExecutionSubject() {
        return executionSubject;
    }
} // hs