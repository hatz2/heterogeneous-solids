//
// Created by Alberto Elorza Rubio on 11/12/2023.
//

#include "MachiningProcessCut.h"

namespace hs {
    MachiningProcess::Outcome MachiningProcessCut::subTrimmedCell(const MachiningProcess::Params& params) const {
        std::array<glm::vec3, 64> coefs{};

        int plane = params.at("cutPlane");
        float d0 = params.at("cutD0");
        float d1 = params.at("cutD1");

        auto mu = 1.f, su = 0.f;
        auto mv = 1.f, sv = 0.f;
        auto mw = 1.f, sw = 0.f;

        switch (plane) {
            case 0:
                mu = 1.f - (d0 + d1);
                su = d0;
                break;
            case 1:
                mv = 1.f - (d0 + d1);
                sv = d0;
                break;
            case 2:
                mw = 1.f - (d0 + d1);
                sw = d0;
                break;
            default:
                break;
        }

        for (int idx = 0, i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                for (int k = 0; k <= 3; k++, idx++)
                    coefs[idx] = {
                        (mu * (float) i) / 3.f + su,
                        (mv * (float) j) / 3.f + sv,
                        (mw * (float) k) / 3.f + sw
                    };

        return {coefs};
    }

    const MachiningProcess::Params& MachiningProcessCut::defaultParams() const {
        static MachiningProcess::Params params = {
            {"cutPlane", { 0, uAxes } },
            {"cutD0", { 0.25f, { 0, 1, 0.01 } } },
            {"cutD1", { 0.25f, { 0, 1, 0.01 } } },
        };
        return params;
    }

    const char* MachiningProcessCut::name() const {
        return "Cut";
    }
} // hs