//
// Created by Alberto Elorza Rubio on 17/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MACHININGPROCESSHOLE_H
#define HETEROGENEOUS_SOLIDS_MACHININGPROCESSHOLE_H

#include "MachiningProcess.h"

namespace hs {

    class MachiningProcessHole: public MachiningProcess {
    public:
        [[nodiscard]] Outcome subTrimmedCell(const hs::MachiningProcess::Params& params) const override;
        [[nodiscard]] const Params& defaultParams() const override;
        [[nodiscard]] const char* name() const override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MACHININGPROCESSHOLE_H
