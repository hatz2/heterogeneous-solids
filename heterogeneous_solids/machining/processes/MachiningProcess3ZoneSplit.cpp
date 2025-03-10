//
// Created by Alberto Elorza Rubio on 12/12/2023.
//

#include "MachiningProcess3ZoneSplit.h"

namespace hs {
    MachiningProcess::Outcome MachiningProcess3ZoneSplit::subTrimmedCell(const MachiningProcess::Params &params) const {
        int plane = params.at("split3plane");
        float d0 = params.at("split3d0");
        float d1 = params.at("split3d1");

        std::array<glm::vec3, 64> coefs0{}, coefs1{}, coefs2{};

        float mu0 = 1.f, su0 = 0.f;
        float mv0 = 1.f, sv0 = 0.f;
        float mw0 = 1.f, sw0 = 0.f;

        float mu1 = 1.f, su1 = 0.f;
        float mv1 = 1.f, sv1 = 0.f;
        float mw1 = 1.f, sw1 = 0.f;

        float mu2 = 1.f, su2 = 0.f;
        float mv2 = 1.f, sv2 = 0.f;
        float mw2 = 1.f, sw2 = 0.f;

        switch (plane) {
            case 0:
                mu0 = d0;
                mu1 = 1.f - d0 - d1; su1 = d0;
                mu2 = d1; su2 = 1.f - d1;
                break;
            case 1:
                mv0 = d0;
                mv1 = 1.f - d0 - d1; sv1 = d0;
                mv2 = d1; sv2 = 1.f - d1;
                break;
            case 2:
                mw0 = d0;
                mw1 = 1.f - d0 - d1; sw1 = d0;
                mw2 = d1; sw2 = 1.f - d1;
                break;
            default:
                break;
        }

        for (int idx = 0, i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                for (int k = 0; k <= 3; k++, idx++) {
                    coefs0[idx] = {
                        (mu0 * (float) i) / 3.f + su0,
                        (mv0 * (float) j) / 3.f + sv0,
                        (mw0 * (float) k) / 3.f + sw0
                    };
                    coefs1[idx] = {
                        (mu1 * (float) i) / 3.f + su1,
                        (mv1 * (float) j) / 3.f + sv1,
                        (mw1 * (float) k) / 3.f + sw1
                    };
                    coefs2[idx] = {
                        (mu2 * (float) i) / 3.f + su2,
                        (mv2 * (float) j) / 3.f + sv2,
                        (mw2 * (float) k) / 3.f + sw2
                    };
                }

        return {coefs0, coefs1, coefs2};
    }

    const MachiningProcess::Params &MachiningProcess3ZoneSplit::defaultParams() const {
        static MachiningProcess::Params params = {
            {"split3plane", { 0, uAxes } },
            {"split3d0", { 0.15f, { 0, 1, 0.01 } } },
            {"split3d1", { 0.15f, { 0, 1, 0.01 } } }
        };
        return params;
    }

    const char *MachiningProcess3ZoneSplit::name() const {
        return "Split three zones";
    }
} // hs