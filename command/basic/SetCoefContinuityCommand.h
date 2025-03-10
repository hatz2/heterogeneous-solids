//
// Created by Alberto Elorza Rubio on 04/04/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SETCOEFCONTINUITYCOMMAND_H
#define HETEROGENEOUS_SOLIDS_SETCOEFCONTINUITYCOMMAND_H

#include "../Command.h"
#include "../../heterogeneous_solids/coefs/MaterialCoef.h"

namespace hs {

    class SetCoefContinuityCommand: public Command, public MergeCommand<SetCoefContinuityCommand> {
    public:
        SetCoefContinuityCommand(MaterialCoef& materialCoef, bool continuity);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;

        bool doDiscard() override;

        bool merge(SetCoefContinuityCommand& other) override;
    private:
        const static std::string description;
        MaterialCoef& materialCoef;
        bool oldContinuity;
        bool newContinuity;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SETCOEFCONTINUITYCOMMAND_H
