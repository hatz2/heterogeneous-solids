//
// Created by Alberto Elorza Rubio on 20/12/2023.
//

#include "MachiningProcessQuarterTube.h"
#include "../../BezierData.h"

#include <functional>

namespace hs {
    MachiningProcess::Outcome MachiningProcessQuarterTube::subTrimmedCell(const MachiningProcess::Params& params) const {
        int edge = params.at("qTubeEdge");
        float iRadS = params.at("qTubeInnerRadS");
        float oRadS = params.at("qTubeOuterRadS");
        float iRadT = params.at("qTubeInnerRadT");
        float oRadT = params.at("qTubeOuterRadT");

        std::array<glm::vec3, 64> coefs{};

        float fS = (oRadS - iRadS) / 3.f;
        float fT = (oRadT - iRadT) / 3.f;
        auto tg = (float)BezierCircleTg;

        const std::array<glm::vec2, 4> c = {{
            { 0.f, 1.f }, { tg, 1.f }, { 1.f, tg }, { 1.f, 0.f }
        }};

        auto t = [&](int idx, int param) { return c[idx].y * (iRadT + (fT * (float)param)); };
        auto s = [&](int idx, int param) { return c[idx].x * (iRadS + (fS * (float)param)); };

        const std::array<std::function<glm::vec3(int, int, int)>, 12> functions = {
            [&](int i, int j, int k) -> glm::vec3 { return { (float)i/3.f, t(k,j), s(k, j) }; },
            [&](int i, int j, int k) -> glm::vec3 { return { (float)i/3.f, s(k,j), 1 - t(k, j) }; },
            [&](int i, int j, int k) -> glm::vec3 { return { (float)i/3.f, 1 - s(k,j), t(k, j) }; },
            [&](int i, int j, int k) -> glm::vec3 { return { (float)i/3.f, 1 - t(k,j), 1 - s(k, j) }; },

            [&](int i, int j, int k) -> glm::vec3 { return { s(i, k), (float)j/3.f, t(i, k) }; },
            [&](int i, int j, int k) -> glm::vec3 { return { t(i, k), (float)j/3.f, 1 - s(i, k) }; },
            [&](int i, int j, int k) -> glm::vec3 { return { 1 - t(i, k), (float)j/3.f, s(i, k) }; },
            [&](int i, int j, int k) -> glm::vec3 { return { 1 - s(i, k), (float)j/3.f, 1 - t(i, k) }; },

            [&](int i, int j, int k) -> glm::vec3 { return { t(j, i), s(j, i), (float)k/3.f }; },
            [&](int i, int j, int k) -> glm::vec3 { return { s(j, i), 1 - t(j, i), (float)k/3.f }; },
            [&](int i, int j, int k) -> glm::vec3 { return { 1 - s(j, i), t(j, i), (float)k/3.f }; },
            [&](int i, int j, int k) -> glm::vec3 { return { 1 - t(j, i), 1 - s(j, i), (float)k/3.f }; }
        };
        auto target = functions[edge];

        for (int idx = 0, i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                for (int k = 0; k <= 3; k++, idx++)
                    coefs[idx] = target(i, j, k);

        return { coefs };
    }

    const MachiningProcess::Params& MachiningProcessQuarterTube::defaultParams() const {
        static MachiningProcess::Params params = {
            {"qTubeEdge", { 0, isoCrvName } },
            {"qTubeInnerRadS", { 0.5f, { 0, 1, 0.01 } } },
            {"qTubeOuterRadS", { 1.f, { 0, 1, 0.01 } } },
            {"qTubeInnerRadT", { 0.5f, { 0, 1, 0.01 } } },
            {"qTubeOuterRadT", { 1.f, { 0, 1, 0.01 } } }
        };
        return params;
    }

    const char* MachiningProcessQuarterTube::name() const {
        return "Quarter Tube";
    }
} // hs