//
// Created by Alberto Elorza Rubio on 07/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_UPDATEVISIBILITYCOMMAND_H
#define HETEROGENEOUS_SOLIDS_UPDATEVISIBILITYCOMMAND_H

#include "../Command.h"
#include "../../utils/props.h"

namespace hs {

    class UpdateVisibilityCommand: public Command, public MergeCommand<UpdateVisibilityCommand> {
    public:
        UpdateVisibilityCommand(bool visible, VisibilityProp& visibilityProp);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;

        bool doDiscard() override;

        bool merge(UpdateVisibilityCommand& other) override;
    private:
        static const std::string description;
        VisibilityProp& visibilityProp;
        bool before;
        bool after;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_UPDATEVISIBILITYCOMMAND_H
