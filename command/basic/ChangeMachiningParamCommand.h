//
// Created by Alberto Elorza Rubio on 08/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_CHANGEMACHININGPARAMCOMMAND_H
#define HETEROGENEOUS_SOLIDS_CHANGEMACHININGPARAMCOMMAND_H

#include <memory>
#include "../Command.h"
#include "../../heterogeneous_solids/machining/MachiningOperation.h"
#include "../../heterogeneous_solids/trimmed_cells/TrimmingNode.h"

namespace hs {

    class ChangeMachiningParamCommand: public Command, public MergeCommand<ChangeMachiningParamCommand> {
    public:
        ChangeMachiningParamCommand(
            const std::shared_ptr<TrimmingNode>& trimmedNode, const std::string& paramName, float value
        );

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;

        bool doDiscard() override;

        bool merge(hs::ChangeMachiningParamCommand& other) override;
    private:
        std::shared_ptr<TrimmingNode> trimmedNode;
        std::string paramName;
        float newValue;
        float previousValue;
        std::string description;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CHANGEMACHININGPARAMCOMMAND_H
