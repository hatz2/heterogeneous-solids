//
// Created by Alberto Elorza Rubio on 25/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_COMMANDHISTORY_H
#define HETEROGENEOUS_SOLIDS_COMMANDHISTORY_H

#include <vector>
#include <memory>

#include "Command.h"
#include "../utils/Observer.h"

#include <spdlog/spdlog.h>

namespace hs {

    enum class CommandHistoryEvent {
        Do,
        DoMerge,
        Redo,
        Undo,
        Discard
    };

    class CommandHistory {
    public:
        using Container = std::vector<std::unique_ptr<Command>>;

        CommandHistory();

        template <class C, class ...Args>
        void execute(Args&&...);

        template <class C>
        void execute(std::unique_ptr<C> command);

        [[nodiscard]] bool canUndo() const;
        [[nodiscard]] bool canRedo() const;
        [[nodiscard]] size_t count() const;
        [[nodiscard]] bool empty() const;
        [[nodiscard]] bool updated() const;
        void setCheckpoint();

        void undo();
        void redo();
        void clear();

        Container::iterator begin();
        Container::iterator done();
        Container::iterator end();

        [[nodiscard]] Subject<CommandHistoryEvent, const Command&>& getExecutionSubject();

    private:
        Subject<CommandHistoryEvent, const Command&> executionSubject;
        Container history;
        unsigned int offset;
        unsigned int checkpoint;
    };

    template <class C, class ...Args>
    void CommandHistory::execute(Args&&... args) {
        execute<C>(std::make_unique<C>(std::forward<Args>(args)...));
    }

    template <class C>
    void CommandHistory::execute(std::unique_ptr<C> command) {
        static_assert(std::is_convertible<C*, Command*>::value);
        if (offset) {
            history.resize(history.size() - offset);
            offset = 0;
        }
        if (!history.empty()) {
            auto* previous = dynamic_cast<MergeCommand<C>*>(history.back().get());
            if (previous && previous->merge(*command)) {
                spdlog::debug("Doing merged command: {}", command->getDescription());
                history.back()->execute();
                if (!history.back()->doDiscard())
                    executionSubject.updateSubject(CommandHistoryEvent::DoMerge, *history.back());
                else {
                    auto item = std::move(history.back());
                    history.pop_back();
                    executionSubject.updateSubject(CommandHistoryEvent::Discard, *item);
                }
                return;
            }
        }
        spdlog::debug("Doing command: {}", command->getDescription());
        command->execute();
        if (!command->doDiscard()) {
            history.push_back(std::move(command));
            executionSubject.updateSubject(CommandHistoryEvent::Do, *history.back());
        } else executionSubject.updateSubject(CommandHistoryEvent::Discard, *command);
    }

} // hs

#endif //HETEROGENEOUS_SOLIDS_COMMANDHISTORY_H
