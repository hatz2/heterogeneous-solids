//
// Created by Alberto Elorza Rubio on 11/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MACHININGPROCESSNONE_H
#define HETEROGENEOUS_SOLIDS_MACHININGPROCESSNONE_H

#include "MachiningProcess.h"

namespace hs {

    class MachiningProcessNone: public MachiningProcess {
    public:
        [[nodiscard]] Outcome subTrimmedCell(const MachiningProcess::Params& params) const override;
        [[nodiscard]] const Params& defaultParams() const override;
        [[nodiscard]] const char* name() const override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MACHININGPROCESSNONE_H
