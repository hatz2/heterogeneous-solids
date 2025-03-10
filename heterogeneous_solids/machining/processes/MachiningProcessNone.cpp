//
// Created by Alberto Elorza Rubio on 11/12/2023.
//

#include "MachiningProcessNone.h"

namespace hs {
    MachiningProcess::Outcome MachiningProcessNone::subTrimmedCell(const MachiningProcess::Params& params) const {
        return {};
    }

    const char* MachiningProcessNone::name() const {
        return "No Process";
    }

    const MachiningProcess::Params& MachiningProcessNone::defaultParams() const {
        static Params params = {};
        return params;
    }
} // hs