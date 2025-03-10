//
// Created by Alberto Elorza Rubio on 19/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MACHININGPROCESSSMOOTHSTEP_H
#define HETEROGENEOUS_SOLIDS_MACHININGPROCESSSMOOTHSTEP_H

#include "MachiningProcess.h"

namespace hs {

    class MachiningProcessSmoothStep: public MachiningProcess {
    public:
        [[nodiscard]] Outcome subTrimmedCell(const hs::MachiningProcess::Params& params) const override;
        [[nodiscard]] const Params& defaultParams() const override;
        [[nodiscard]] const char* name() const override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MACHININGPROCESSSMOOTHSTEP_H
