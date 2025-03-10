//
// Created by Alberto Elorza Rubio on 12/12/2023.
//

#include "MachiningProcessSplit.h"

namespace hs {
    MachiningProcess::Outcome MachiningProcessSplit::subTrimmedCell(const MachiningProcess::Params &params) const {
        int plane = params.at("splitPlane");
        float d = params.at("splitD");

        std::array<glm::vec3, 64> coefs0{}, coefs1{};

        float mu0 = 1.f, su0 = 0.f;
        float mv0 = 1.f, sv0 = 0.f;
        float mw0 = 1.f, sw0 = 0.f;

        float mu1 = 1.f, su1 = 0.f;
        float mv1 = 1.f, sv1 = 0.f;
        float mw1 = 1.f, sw1 = 0.f;

        switch (plane) {
            case 0:
                mu0 = d;
                mu1 = 1.f - d; su1 = d;
                break;
            case 1:
                mv0 = d;
                mv1 = 1.f - d; sv1 = d;
                break;
            case 2:
                mw0 = d;
                mw1 = 1.f - d; sw1 = d;
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
                }

        return {coefs0, coefs1};
    }

    const MachiningProcess::Params &MachiningProcessSplit::defaultParams() const {
        static MachiningProcess::Params params = {
            {"splitPlane", { 0, uAxes } },
            {"splitD", { 0.5f, { 0, 1, 0.01 } } }
        };
        return params;
    }

    const char *MachiningProcessSplit::name() const {
        return "Split";
    }
} // hs