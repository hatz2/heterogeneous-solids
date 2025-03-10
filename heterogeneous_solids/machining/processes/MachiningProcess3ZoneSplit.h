//
// Created by Alberto Elorza Rubio on 12/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MACHININGPROCESS3ZONESPLIT_H
#define HETEROGENEOUS_SOLIDS_MACHININGPROCESS3ZONESPLIT_H

#include "MachiningProcess.h"

namespace hs {

    class MachiningProcess3ZoneSplit: public MachiningProcess {
    public:
        Outcome subTrimmedCell(const hs::MachiningProcess::Params& params) const override;
        [[nodiscard]] const Params& defaultParams() const override;
        const char* name() const override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MACHININGPROCESS3ZONESPLIT_H
