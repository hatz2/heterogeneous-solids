//
// Created by Alberto Elorza Rubio on 24/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_MACHININGPROCESSCHILD_H
#define HETEROGENEOUS_SOLIDS_MACHININGPROCESSCHILD_H

#include "MachiningProcess.h"

namespace hs {

    class MachiningProcessChild: public MachiningProcess {
    public:
        [[nodiscard]] Outcome subTrimmedCell(const MachiningProcess::Params& params) const override;
        [[nodiscard]] const Params& defaultParams() const override;
        [[nodiscard]] const char* name() const override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MACHININGPROCESSCHILD_H
