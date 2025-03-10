//
// Created by Alberto Elorza Rubio on 04/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SWAPTRIMMINGNODECONTENTCOMMAND_H
#define HETEROGENEOUS_SOLIDS_SWAPTRIMMINGNODECONTENTCOMMAND_H

#include "../Command.h"
#include "../../heterogeneous_solids/trimmed_cells/TrimmedCell.h"

namespace hs {

    /// @todo Add no discard
    class SwapTrimmingNodeContentCommand: public Command {
    public:
        SwapTrimmingNodeContentCommand(
            std::shared_ptr<TrimmingNode> trimmingNode,
            std::shared_ptr<TrimmingNode> newContent
        );

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;
    private:
        static const std::string description;
        std::shared_ptr<TrimmingNode> trimmingNode;
        std::shared_ptr<TrimmingNode> newContent;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SWAPTRIMMINGNODECONTENTCOMMAND_H
