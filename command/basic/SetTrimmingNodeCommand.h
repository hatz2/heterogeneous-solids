//
// Created by Alberto Elorza Rubio on 09/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SETTRIMMINGNODECOMMAND_H
#define HETEROGENEOUS_SOLIDS_SETTRIMMINGNODECOMMAND_H

#include "../Command.h"
#include "../../heterogeneous_solids/trimmed_cells/TrimmedCell.h"

namespace hs {

    class SetTrimmingNodeCommand: public Command, public MergeCommand<SetTrimmingNodeCommand> {
    public:
        SetTrimmingNodeCommand(TrimmedCell& trimmedCell, const std::shared_ptr<TrimmingNode>& trimmingNode);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;

        bool doDiscard() override;

        bool merge(hs::SetTrimmingNodeCommand& other) override;
    private:
        std::string description;
        TrimmedCell& trimmedCell;
        std::shared_ptr<TrimmingNode> newNode;
        std::shared_ptr<TrimmingNode> previousNode;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SETTRIMMINGNODECOMMAND_H
