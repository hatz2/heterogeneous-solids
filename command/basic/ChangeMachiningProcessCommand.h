//
// Created by Alberto Elorza Rubio on 08/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_CHANGEMACHININGPROCESSCOMMAND_H
#define HETEROGENEOUS_SOLIDS_CHANGEMACHININGPROCESSCOMMAND_H

#include "../Command.h"
#include "../../heterogeneous_solids/trimmed_cells/TrimmedCell.h"
#include <memory>

namespace hs {

    // This command only works if ChangeTrimmingNodeCommand is also applied for node changes
    // otherwise it would lead to unexpected behaviour (swiping the wrong process in the wrong nodes)
    class ChangeMachiningProcessCommand: public Command, public MergeCommand<ChangeMachiningProcessCommand> {
    public:
        ChangeMachiningProcessCommand(const std::shared_ptr<TrimmingNode>& trimmedNode, MachiningProcess& process);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;

        bool doDiscard() override;

        bool merge(hs::ChangeMachiningProcessCommand &other) override;
    private:
        std::shared_ptr<TrimmingNode> trimmedNode;
        std::reference_wrapper<MachiningProcess> previousProcess;
        std::reference_wrapper<MachiningProcess> newProcess;
        std::string description;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CHANGEMACHININGPROCESSCOMMAND_H
