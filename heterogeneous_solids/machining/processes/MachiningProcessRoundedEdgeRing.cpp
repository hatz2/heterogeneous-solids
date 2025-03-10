//
// Created by Alberto Elorza Rubio on 12/01/2024.
//

#include "MachiningProcessRoundedEdgeRing.h"

#include <functional>

namespace hs {
    MachiningProcess::Outcome MachiningProcessRoundedEdgeRing::subTrimmedCell(const MachiningProcess::Params& params) const {
        int edge = params.at("roundedRingEdge");
        float innerRad = params.at("roundedRingInnerRadius");
        float outerRad = params.at("roundedRingOuterRadius");

        constexpr glm::vec2 cA1[4] = {
            { 0, 0.5 }, { 1/6., 0.5 },
            { 2/6., 0.5 }, { 0.5, 0.5 }
        };
        constexpr glm::vec2 cA2[4] = {
            { 0, 1 }, { 0.26521647, 1 },
            { 0.51957023, 0.89464307 }, { 0.70710665, 0.70710665 }
        };

        constexpr glm::vec2 cB1[4] = {
            { 0.5, 0.5 }, { 0.5, 2/6. },
            { 0.5, 1/6. }, { 0.5, 0 }
        };
        constexpr glm::vec2 cB2[4] = {
            { 0.70710665, 0.70710665 }, { 0.89464307, 0.51957023 },
            { 1, 0.26521647 }, { 1, 0 }
        };

        std::array<glm::vec3, 64> cfsA{}, cfsB{}, cfsC{}, cfsD{}, cfsE{};

        const std::array<std::function<std::array<glm::vec3, 5>(int, int, int)>, 12> functions = {
            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto u = (float)i/3.0;
                auto vA = (cA1[k].y * innerRad) + ((((cA2[k].y-cA1[k].y) * innerRad) / 3.0) * (float)j);
                auto wA = (cA1[k].x * innerRad) + ((((cA2[k].x-cA1[k].x) * innerRad) / 3.0) * (float)j);
                auto vB = (cB1[k].y * innerRad) + ((((cB2[k].y-cB1[k].y) * innerRad) / 3.0) * (float)j);
                auto wB = (cB1[k].x * innerRad) + ((((cB2[k].x-cB1[k].x) * innerRad) / 3.0) * (float)j);
                auto vC = ((cA1[k].y * innerRad) / 3.0) * (float)j;
                auto wC = cA1[k].x * innerRad;
                auto vD = (cA2[k].y * innerRad) + (cA2[k].y * (((outerRad - innerRad) / 3.0) * (float)j));
                auto wD = (cA2[k].x * innerRad) + (cA2[k].x * (((outerRad - innerRad) / 3.0) * (float)j));
                auto vE = (cB2[k].y * innerRad) + (cB2[k].y * (((outerRad - innerRad) / 3.0) * (float)j));
                auto wE = (cB2[k].x * innerRad) + (cB2[k].x * (((outerRad - innerRad) / 3.0) * (float)j));
                return {{ { u, vA, wA }, { u, vB, wB }, { u, vC, wC }, { u, vD, wD }, { u, vE, wE } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto u = (float)i/3.0;
                auto vA = (cA1[k].y * innerRad) + ((((cA2[k].y-cA1[k].y) * innerRad) / 3.0) * (float)j);
                auto wA = (cA1[k].x * innerRad) + ((((cA2[k].x-cA1[k].x) * innerRad) / 3.0) * (float)j);
                auto vB = (cB1[k].y * innerRad) + ((((cB2[k].y-cB1[k].y) * innerRad) / 3.0) * (float)j);
                auto wB = (cB1[k].x * innerRad) + ((((cB2[k].x-cB1[k].x) * innerRad) / 3.0) * (float)j);
                auto vC = ((cA1[k].y * innerRad) / 3.0) * (float)j;
                auto wC = cA1[k].x * innerRad;
                auto vD = (cA2[k].y * innerRad) + (cA2[k].y * (((outerRad - innerRad) / 3.0) * (float)j));
                auto wD = (cA2[k].x * innerRad) + (cA2[k].x * (((outerRad - innerRad) / 3.0) * (float)j));
                auto vE = (cB2[k].y * innerRad) + (cB2[k].y * (((outerRad - innerRad) / 3.0) * (float)j));
                auto wE = (cB2[k].x * innerRad) + (cB2[k].x * (((outerRad - innerRad) / 3.0) * (float)j));
                return {{
                    { u, wA, -vA + 1.0 }, { u, wB, -vB + 1.0 }, { u, wC, -vC + 1.0 },
                    { u, wD, -vD + 1.0 }, { u, wE, -vE + 1.0 }
                }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto u = (float)i/3.0;
                auto vA = (cA1[k].y * innerRad) + ((((cA2[k].y-cA1[k].y) * innerRad) / 3.0) * (float)j);
                auto wA = (cA1[k].x * innerRad) + ((((cA2[k].x-cA1[k].x) * innerRad) / 3.0) * (float)j);
                auto vB = (cB1[k].y * innerRad) + ((((cB2[k].y-cB1[k].y) * innerRad) / 3.0) * (float)j);
                auto wB = (cB1[k].x * innerRad) + ((((cB2[k].x-cB1[k].x) * innerRad) / 3.0) * (float)j);
                auto vC = ((cA1[k].y * innerRad) / 3.0) * (float)j;
                auto wC = cA1[k].x * innerRad;
                auto vD = (cA2[k].y * innerRad) + (cA2[k].y * (((outerRad - innerRad) / 3.0) * (float)j));
                auto wD = (cA2[k].x * innerRad) + (cA2[k].x * (((outerRad - innerRad) / 3.0) * (float)j));
                auto vE = (cB2[k].y * innerRad) + (cB2[k].y * (((outerRad - innerRad) / 3.0) * (float)j));
                auto wE = (cB2[k].x * innerRad) + (cB2[k].x * (((outerRad - innerRad) / 3.0) * (float)j));
                return {{
                    { u, -wA + 1.0, vA }, { u, -wB + 1.0, vB }, { u, -wC + 1.0, vC },
                    { u, -wD + 1.0, vD }, { u, -wE + 1.0, vE }
                }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto u = (float)i/3.0;
                auto vA = (cA1[k].y * innerRad) + ((((cA2[k].y-cA1[k].y) * innerRad) / 3.0) * (float)j);
                auto wA = (cA1[k].x * innerRad) + ((((cA2[k].x-cA1[k].x) * innerRad) / 3.0) * (float)j);
                auto vB = (cB1[k].y * innerRad) + ((((cB2[k].y-cB1[k].y) * innerRad) / 3.0) * (float)j);
                auto wB = (cB1[k].x * innerRad) + ((((cB2[k].x-cB1[k].x) * innerRad) / 3.0) * (float)j);
                auto vC = ((cA1[k].y * innerRad) / 3.0) * (float)j;
                auto wC = cA1[k].x * innerRad;
                auto vD = (cA2[k].y * innerRad) + (cA2[k].y * (((outerRad - innerRad) / 3.0) * (float)j));
                auto wD = (cA2[k].x * innerRad) + (cA2[k].x * (((outerRad - innerRad) / 3.0) * (float)j));
                auto vE = (cB2[k].y * innerRad) + (cB2[k].y * (((outerRad - innerRad) / 3.0) * (float)j));
                auto wE = (cB2[k].x * innerRad) + (cB2[k].x * (((outerRad - innerRad) / 3.0) * (float)j));
                return {{
                    { u, -vA + 1.0, -wA + 1.0 }, { u, -vB + 1.0, -wB + 1.0 }, { u, -vC + 1.0, -wC + 1.0 },
                    { u, -vD + 1.0, -wD + 1.0 }, { u, -vE + 1.0, -wE + 1.0 }
                }};
            },

            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto v = (float)j/3.0;
                auto wA = (cA1[i].y * innerRad) + ((((cA2[i].y-cA1[i].y) * innerRad) / 3.0) * (float)k);
                auto uA = (cA1[i].x * innerRad) + ((((cA2[i].x-cA1[i].x) * innerRad) / 3.0) * (float)k);
                auto wB = (cB1[i].y * innerRad) + ((((cB2[i].y-cB1[i].y) * innerRad) / 3.0) * (float)k);
                auto uB = (cB1[i].x * innerRad) + ((((cB2[i].x-cB1[i].x) * innerRad) / 3.0) * (float)k);
                auto wC = ((cA1[i].y * innerRad) / 3.0) * (float)k;
                auto uC = cA1[i].x * innerRad;
                auto wD = (cA2[i].y * innerRad) + (cA2[i].y * (((outerRad - innerRad) / 3.0) * (float)k));
                auto uD = (cA2[i].x * innerRad) + (cA2[i].x * (((outerRad - innerRad) / 3.0) * (float)k));
                auto wE = (cB2[i].y * innerRad) + (cB2[i].y * (((outerRad - innerRad) / 3.0) * (float)k));
                auto uE = (cB2[i].x * innerRad) + (cB2[i].x * (((outerRad - innerRad) / 3.0) * (float)k));
                return {{ { uA, v, wA }, { uB, v, wB }, { uC, v, wC }, { uD, v, wD }, { uE, v, wE } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto v = (float)j/3.0;
                auto wA = (cA1[i].y * innerRad) + ((((cA2[i].y-cA1[i].y) * innerRad) / 3.0) * (float)k);
                auto uA = (cA1[i].x * innerRad) + ((((cA2[i].x-cA1[i].x) * innerRad) / 3.0) * (float)k);
                auto wB = (cB1[i].y * innerRad) + ((((cB2[i].y-cB1[i].y) * innerRad) / 3.0) * (float)k);
                auto uB = (cB1[i].x * innerRad) + ((((cB2[i].x-cB1[i].x) * innerRad) / 3.0) * (float)k);
                auto wC = ((cA1[i].y * innerRad) / 3.0) * (float)k;
                auto uC = cA1[i].x * innerRad;
                auto wD = (cA2[i].y * innerRad) + (cA2[i].y * (((outerRad - innerRad) / 3.0) * (float)k));
                auto uD = (cA2[i].x * innerRad) + (cA2[i].x * (((outerRad - innerRad) / 3.0) * (float)k));
                auto wE = (cB2[i].y * innerRad) + (cB2[i].y * (((outerRad - innerRad) / 3.0) * (float)k));
                auto uE = (cB2[i].x * innerRad) + (cB2[i].x * (((outerRad - innerRad) / 3.0) * (float)k));
                return {{
                    { wA, v, -uA + 1.0 }, { wB, v, -uB + 1.0 }, { wC, v, -uC + 1.0 },
                    { wD, v, -uD + 1.0 }, { wE, v, -uE + 1.0 }
                }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto v = (float)j/3.0;
                auto wA = (cA1[i].y * innerRad) + ((((cA2[i].y-cA1[i].y) * innerRad) / 3.0) * (float)k);
                auto uA = (cA1[i].x * innerRad) + ((((cA2[i].x-cA1[i].x) * innerRad) / 3.0) * (float)k);
                auto wB = (cB1[i].y * innerRad) + ((((cB2[i].y-cB1[i].y) * innerRad) / 3.0) * (float)k);
                auto uB = (cB1[i].x * innerRad) + ((((cB2[i].x-cB1[i].x) * innerRad) / 3.0) * (float)k);
                auto wC = ((cA1[i].y * innerRad) / 3.0) * (float)k;
                auto uC = cA1[i].x * innerRad;
                auto wD = (cA2[i].y * innerRad) + (cA2[i].y * (((outerRad - innerRad) / 3.0) * (float)k));
                auto uD = (cA2[i].x * innerRad) + (cA2[i].x * (((outerRad - innerRad) / 3.0) * (float)k));
                auto wE = (cB2[i].y * innerRad) + (cB2[i].y * (((outerRad - innerRad) / 3.0) * (float)k));
                auto uE = (cB2[i].x * innerRad) + (cB2[i].x * (((outerRad - innerRad) / 3.0) * (float)k));
                return {{
                    { -wA + 1.0, v, uA }, { -wB + 1.0, v, uB }, { -wC + 1.0, v, uC },
                    { -wD + 1.0, v, uD }, { -wE + 1.0, v, uE }
                }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto v = (float)j/3.0;
                auto wA = (cA1[i].y * innerRad) + ((((cA2[i].y-cA1[i].y) * innerRad) / 3.0) * (float)k);
                auto uA = (cA1[i].x * innerRad) + ((((cA2[i].x-cA1[i].x) * innerRad) / 3.0) * (float)k);
                auto wB = (cB1[i].y * innerRad) + ((((cB2[i].y-cB1[i].y) * innerRad) / 3.0) * (float)k);
                auto uB = (cB1[i].x * innerRad) + ((((cB2[i].x-cB1[i].x) * innerRad) / 3.0) * (float)k);
                auto wC = ((cA1[i].y * innerRad) / 3.0) * (float)k;
                auto uC = cA1[i].x * innerRad;
                auto wD = (cA2[i].y * innerRad) + (cA2[i].y * (((outerRad - innerRad) / 3.0) * (float)k));
                auto uD = (cA2[i].x * innerRad) + (cA2[i].x * (((outerRad - innerRad) / 3.0) * (float)k));
                auto wE = (cB2[i].y * innerRad) + (cB2[i].y * (((outerRad - innerRad) / 3.0) * (float)k));
                auto uE = (cB2[i].x * innerRad) + (cB2[i].x * (((outerRad - innerRad) / 3.0) * (float)k));
                return {{
                    { -uA + 1.0, v, -wA + 1.0 }, { -uB + 1.0, v, -wB + 1.0 }, { -uC + 1.0, v, -wC + 1.0 },
                    { -uD + 1.0, v, -wD + 1.0 }, { -uE + 1.0, v, -wE + 1.0 }
                }};
            },

            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto w = (float)k/3.0;
                auto uA = (cA1[j].y * innerRad) + ((((cA2[j].y-cA1[j].y) * innerRad) / 3.0) * (float)i);
                auto vA = (cA1[j].x * innerRad) + ((((cA2[j].x-cA1[j].x) * innerRad) / 3.0) * (float)i);
                auto uB = (cB1[j].y * innerRad) + ((((cB2[j].y-cB1[j].y) * innerRad) / 3.0) * (float)i);
                auto vB = (cB1[j].x * innerRad) + ((((cB2[j].x-cB1[j].x) * innerRad) / 3.0) * (float)i);
                auto uC = ((cA1[j].y * innerRad) / 3.0) * (float)i;
                auto vC = cA1[j].x * innerRad;
                auto uD = (cA2[j].y * innerRad) + (cA2[j].y * (((outerRad - innerRad) / 3.0) * (float)i));
                auto vD = (cA2[j].x * innerRad) + (cA2[j].x * (((outerRad - innerRad) / 3.0) * (float)i));
                auto uE = (cB2[j].y * innerRad) + (cB2[j].y * (((outerRad - innerRad) / 3.0) * (float)i));
                auto vE = (cB2[j].x * innerRad) + (cB2[j].x * (((outerRad - innerRad) / 3.0) * (float)i));
                return {{ { uA, vA, w }, { uB, vB, w }, { uC, vC, w }, { uD, vD, w }, { uE, vE, w } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto w = (float)k/3.0;
                auto uA = (cA1[j].y * innerRad) + ((((cA2[j].y-cA1[j].y) * innerRad) / 3.0) * (float)i);
                auto vA = (cA1[j].x * innerRad) + ((((cA2[j].x-cA1[j].x) * innerRad) / 3.0) * (float)i);
                auto uB = (cB1[j].y * innerRad) + ((((cB2[j].y-cB1[j].y) * innerRad) / 3.0) * (float)i);
                auto vB = (cB1[j].x * innerRad) + ((((cB2[j].x-cB1[j].x) * innerRad) / 3.0) * (float)i);
                auto uC = ((cA1[j].y * innerRad) / 3.0) * (float)i;
                auto vC = cA1[j].x * innerRad;
                auto uD = (cA2[j].y * innerRad) + (cA2[j].y * (((outerRad - innerRad) / 3.0) * (float)i));
                auto vD = (cA2[j].x * innerRad) + (cA2[j].x * (((outerRad - innerRad) / 3.0) * (float)i));
                auto uE = (cB2[j].y * innerRad) + (cB2[j].y * (((outerRad - innerRad) / 3.0) * (float)i));
                auto vE = (cB2[j].x * innerRad) + (cB2[j].x * (((outerRad - innerRad) / 3.0) * (float)i));
                return {{
                    { vA, -uA + 1.0, w }, { vB, -uB + 1.0, w }, { vC, -uC + 1.0, w },
                    { vD, -uD + 1.0, w }, { vE, -uE + 1.0, w }
                }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto w = (float)k/3.0;
                auto uA = (cA1[j].y * innerRad) + ((((cA2[j].y-cA1[j].y) * innerRad) / 3.0) * (float)i);
                auto vA = (cA1[j].x * innerRad) + ((((cA2[j].x-cA1[j].x) * innerRad) / 3.0) * (float)i);
                auto uB = (cB1[j].y * innerRad) + ((((cB2[j].y-cB1[j].y) * innerRad) / 3.0) * (float)i);
                auto vB = (cB1[j].x * innerRad) + ((((cB2[j].x-cB1[j].x) * innerRad) / 3.0) * (float)i);
                auto uC = ((cA1[j].y * innerRad) / 3.0) * (float)i;
                auto vC = cA1[j].x * innerRad;
                auto uD = (cA2[j].y * innerRad) + (cA2[j].y * (((outerRad - innerRad) / 3.0) * (float)i));
                auto vD = (cA2[j].x * innerRad) + (cA2[j].x * (((outerRad - innerRad) / 3.0) * (float)i));
                auto uE = (cB2[j].y * innerRad) + (cB2[j].y * (((outerRad - innerRad) / 3.0) * (float)i));
                auto vE = (cB2[j].x * innerRad) + (cB2[j].x * (((outerRad - innerRad) / 3.0) * (float)i));
                return {{
                    { -vA + 1.0, uA, w }, { -vB + 1.0, uB, w }, { -vC + 1.0, uC, w },
                    { -vD + 1.0, uD, w }, { -vE + 1.0, uE, w }
                }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 5> {
                auto w = (float)k/3.0;
                auto uA = (cA1[j].y * innerRad) + ((((cA2[j].y-cA1[j].y) * innerRad) / 3.0) * (float)i);
                auto vA = (cA1[j].x * innerRad) + ((((cA2[j].x-cA1[j].x) * innerRad) / 3.0) * (float)i);
                auto uB = (cB1[j].y * innerRad) + ((((cB2[j].y-cB1[j].y) * innerRad) / 3.0) * (float)i);
                auto vB = (cB1[j].x * innerRad) + ((((cB2[j].x-cB1[j].x) * innerRad) / 3.0) * (float)i);
                auto uC = ((cA1[j].y * innerRad) / 3.0) * (float)i;
                auto vC = cA1[j].x * innerRad;
                auto uD = (cA2[j].y * innerRad) + (cA2[j].y * (((outerRad - innerRad) / 3.0) * (float)i));
                auto vD = (cA2[j].x * innerRad) + (cA2[j].x * (((outerRad - innerRad) / 3.0) * (float)i));
                auto uE = (cB2[j].y * innerRad) + (cB2[j].y * (((outerRad - innerRad) / 3.0) * (float)i));
                auto vE = (cB2[j].x * innerRad) + (cB2[j].x * (((outerRad - innerRad) / 3.0) * (float)i));
                return {{
                    { -uA + 1.0, -vA + 1.0, w }, { -uB + 1.0, -vB + 1.0, w }, { -uC + 1.0, -vC + 1.0, w },
                    { -uD + 1.0, -vD + 1.0, w }, { -uE + 1.0, -vE + 1.0, w }
                }};
            },
        };
        auto target = functions[edge];

        for (int idx = 0, i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                for (int k = 0; k <= 3; k++, idx++) {
                    auto coefs = target(i, j, k);
                    cfsA[idx] = coefs[0];
                    cfsB[idx] = coefs[1];
                    cfsC[idx] = coefs[2];
                    cfsD[idx] = coefs[3];
                    cfsE[idx] = coefs[4];
                }

        return { cfsA, cfsB, cfsC, cfsD, cfsE };
    }

    const MachiningProcess::Params& MachiningProcessRoundedEdgeRing::defaultParams() const {
        static MachiningProcess::Params params = {
            {"roundedRingEdge", { 0, machiningEdgeName } },
            {"roundedRingInnerRadius", { 0.5f, { 0.f, 1.f, 0.1f } } },
            {"roundedRingOuterRadius", { 1.f, { 0.f, 1.f, 0.1f } } },
        };
        return params;
    }

    const char* MachiningProcessRoundedEdgeRing::name() const {
        return "Rounded Edge Ring";
    }
} // hs