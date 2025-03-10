//
// Created by Alberto Elorza Rubio on 24/02/2024.
//

#include "MachiningProcessChild.h"

#include "../../utils.h"

namespace hs {
    MachiningProcess::Outcome MachiningProcessChild::subTrimmedCell(const MachiningProcess::Params& params) const {
        return {
            getDefaultCoefs()
        };
    }

    const MachiningProcess::Params& MachiningProcessChild::defaultParams() const {
        static MachiningProcess::Params params;
        return params;
    }

    const char* MachiningProcessChild::name() const {
        return "Child";
    }
} // hs