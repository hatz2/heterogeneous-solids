//
// Created by Alberto Elorza Rubio on 28/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MACHININGPROCESSGEARTEETH_H
#define HETEROGENEOUS_SOLIDS_MACHININGPROCESSGEARTEETH_H

#include "MachiningProcess.h"

namespace hs {

    class MachiningProcessGearTeeth: public MachiningProcess {
    public:
        [[nodiscard]] MachiningProcess::Outcome subTrimmedCell(const MachiningProcess::Params& params) const override;
        [[nodiscard]] const Params& defaultParams() const override;
        [[nodiscard]] const char* name() const override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MACHININGPROCESSGEARTEETH_H
