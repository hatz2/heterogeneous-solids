//
// Created by Alberto Elorza Rubio on 10/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_MACHININGPROCESSROTATION_H
#define HETEROGENEOUS_SOLIDS_MACHININGPROCESSROTATION_H

#include "MachiningProcess.h"

namespace hs {

    class MachiningProcessRotation: public MachiningProcess {
    public:
        [[nodiscard]] Outcome subTrimmedCell(const hs::MachiningProcess::Params& params) const override;
        [[nodiscard]] const Params& defaultParams() const override;
        [[nodiscard]] const char* name() const override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MACHININGPROCESSROTATION_H
