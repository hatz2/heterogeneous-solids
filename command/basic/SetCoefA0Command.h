//
// Created by Alberto Elorza Rubio on 13/03/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SETCOEFA0COMMAND_H
#define HETEROGENEOUS_SOLIDS_SETCOEFA0COMMAND_H

#include "../Command.h"
#include "../../heterogeneous_solids/coefs/CellCoef.h"

namespace hs {

    class SetCoefA0Command: public Command, public MergeCommand<SetCoefA0Command> {
    public:
        SetCoefA0Command(MaterialCoef& materialCoef, float a0);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;

        bool doDiscard() override;

        bool merge(SetCoefA0Command& other) override;
    private:
        const static std::string description;
        MaterialCoef& materialCoef;
        float oldA0;
        float newA0;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SETCOEFA0COMMAND_H
