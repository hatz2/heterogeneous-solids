//
// Created by Alberto Elorza Rubio on 12/01/2024.
//

#include "MachiningProcessRoundedEdge.h"

#include <functional>

namespace hs {
    MachiningProcess::Outcome MachiningProcessRoundedEdge::subTrimmedCell(const MachiningProcess::Params& params) const {
        int edge = params.at("roundedEdge");
        float rad = params.at("roundedRadius");

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

        std::array<glm::vec3, 64> cfsA{}, cfsB{}, cfsC{};

        const std::array<std::function<std::array<glm::vec3, 3>(int, int, int)>, 12> functions = {
            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto u = (float)i/3.0;
                auto vA = (cA1[k].y * rad) + ((((cA2[k].y-cA1[k].y) * rad) / 3.0) * (float)j);
                auto wA = (cA1[k].x * rad) + ((((cA2[k].x-cA1[k].x) * rad) / 3.0) * (float)j);
                auto vB = (cB1[k].y * rad) + ((((cB2[k].y-cB1[k].y) * rad) / 3.0) * (float)j);
                auto wB = (cB1[k].x * rad) + ((((cB2[k].x-cB1[k].x) * rad) / 3.0) * (float)j);
                auto vC = ((cA1[k].y * rad) / 3.0) * (float)j;
                auto wC = cA1[k].x * rad;
                return {{ { u, vA, wA }, { u, vB, wB }, { u, vC, wC } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto u = (float)i/3.0;
                auto vA = (cA1[k].y * rad) + ((((cA2[k].y-cA1[k].y) * rad) / 3.0) * (float)j);
                auto wA = (cA1[k].x * rad) + ((((cA2[k].x-cA1[k].x) * rad) / 3.0) * (float)j);
                auto vB = (cB1[k].y * rad) + ((((cB2[k].y-cB1[k].y) * rad) / 3.0) * (float)j);
                auto wB = (cB1[k].x * rad) + ((((cB2[k].x-cB1[k].x) * rad) / 3.0) * (float)j);
                auto vC = ((cA1[k].y * rad) / 3.0) * (float)j;
                auto wC = cA1[k].x * rad;
                return {{ { u, wA, -vA + 1.0 }, { u, wB, -vB + 1.0 }, { u, wC, -vC + 1.0 } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto u = (float)i/3.0;
                auto vA = (cA1[k].y * rad) + ((((cA2[k].y-cA1[k].y) * rad) / 3.0) * (float)j);
                auto wA = (cA1[k].x * rad) + ((((cA2[k].x-cA1[k].x) * rad) / 3.0) * (float)j);
                auto vB = (cB1[k].y * rad) + ((((cB2[k].y-cB1[k].y) * rad) / 3.0) * (float)j);
                auto wB = (cB1[k].x * rad) + ((((cB2[k].x-cB1[k].x) * rad) / 3.0) * (float)j);
                auto vC = ((cA1[k].y * rad) / 3.0) * (float)j;
                auto wC = cA1[k].x * rad;
                return {{ { u, -wA + 1.0, vA }, { u, -wB + 1.0, vB }, { u, -wC + 1.0, vC } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto u = (float)i/3.0;
                auto vA = (cA1[k].y * rad) + ((((cA2[k].y-cA1[k].y) * rad) / 3.0) * (float)j);
                auto wA = (cA1[k].x * rad) + ((((cA2[k].x-cA1[k].x) * rad) / 3.0) * (float)j);
                auto vB = (cB1[k].y * rad) + ((((cB2[k].y-cB1[k].y) * rad) / 3.0) * (float)j);
                auto wB = (cB1[k].x * rad) + ((((cB2[k].x-cB1[k].x) * rad) / 3.0) * (float)j);
                auto vC = ((cA1[k].y * rad) / 3.0) * (float)j;
                auto wC = cA1[k].x * rad;
                return {{ { u, -vA + 1.0, -wA + 1.0 }, { u, -vB + 1.0, -wB + 1.0 }, { u, -vC + 1.0, -wC + 1.0 } }};
            },

            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto v = (float)j/3.0;
                auto wA = (cA1[i].y * rad) + ((((cA2[i].y-cA1[i].y) * rad) / 3.0) * (float)k);
                auto uA = (cA1[i].x * rad) + ((((cA2[i].x-cA1[i].x) * rad) / 3.0) * (float)k);
                auto wB = (cB1[i].y * rad) + ((((cB2[i].y-cB1[i].y) * rad) / 3.0) * (float)k);
                auto uB = (cB1[i].x * rad) + ((((cB2[i].x-cB1[i].x) * rad) / 3.0) * (float)k);
                auto wC = ((cA1[i].y * rad) / 3.0) * (float)k;
                auto uC = cA1[i].x * rad;
                return {{ { uA, v, wA }, { uB, v, wB }, { uC, v, wC } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto v = (float)j/3.0;
                auto wA = (cA1[i].y * rad) + ((((cA2[i].y-cA1[i].y) * rad) / 3.0) * (float)k);
                auto uA = (cA1[i].x * rad) + ((((cA2[i].x-cA1[i].x) * rad) / 3.0) * (float)k);
                auto wB = (cB1[i].y * rad) + ((((cB2[i].y-cB1[i].y) * rad) / 3.0) * (float)k);
                auto uB = (cB1[i].x * rad) + ((((cB2[i].x-cB1[i].x) * rad) / 3.0) * (float)k);
                auto wC = ((cA1[i].y * rad) / 3.0) * (float)k;
                auto uC = cA1[i].x * rad;
                return {{ { wA, v, -uA + 1.0 }, { wB, v, -uB + 1.0 }, { wC, v, -uC + 1.0 } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto v = (float)j/3.0;
                auto wA = (cA1[i].y * rad) + ((((cA2[i].y-cA1[i].y) * rad) / 3.0) * (float)k);
                auto uA = (cA1[i].x * rad) + ((((cA2[i].x-cA1[i].x) * rad) / 3.0) * (float)k);
                auto wB = (cB1[i].y * rad) + ((((cB2[i].y-cB1[i].y) * rad) / 3.0) * (float)k);
                auto uB = (cB1[i].x * rad) + ((((cB2[i].x-cB1[i].x) * rad) / 3.0) * (float)k);
                auto wC = ((cA1[i].y * rad) / 3.0) * (float)k;
                auto uC = cA1[i].x * rad;
                return {{ { -wA + 1.0, v, uA }, { -wB + 1.0, v, uB }, { -wC + 1.0, v, uC } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto v = (float)j/3.0;
                auto wA = (cA1[i].y * rad) + ((((cA2[i].y-cA1[i].y) * rad) / 3.0) * (float)k);
                auto uA = (cA1[i].x * rad) + ((((cA2[i].x-cA1[i].x) * rad) / 3.0) * (float)k);
                auto wB = (cB1[i].y * rad) + ((((cB2[i].y-cB1[i].y) * rad) / 3.0) * (float)k);
                auto uB = (cB1[i].x * rad) + ((((cB2[i].x-cB1[i].x) * rad) / 3.0) * (float)k);
                auto wC = ((cA1[i].y * rad) / 3.0) * (float)k;
                auto uC = cA1[i].x * rad;
                return {{ { -uA + 1.0, v, -wA + 1.0 }, { -uB + 1.0, v, -wB + 1.0 }, { -uC + 1.0, v, -wC + 1.0 } }};
            },

            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto w = (float)k/3.0;
                auto uA = (cA1[j].y * rad) + ((((cA2[j].y-cA1[j].y) * rad) / 3.0) * (float)i);
                auto vA = (cA1[j].x * rad) + ((((cA2[j].x-cA1[j].x) * rad) / 3.0) * (float)i);
                auto uB = (cB1[j].y * rad) + ((((cB2[j].y-cB1[j].y) * rad) / 3.0) * (float)i);
                auto vB = (cB1[j].x * rad) + ((((cB2[j].x-cB1[j].x) * rad) / 3.0) * (float)i);
                auto uC = ((cA1[j].y * rad) / 3.0) * (float)i;
                auto vC = cA1[j].x * rad;
                return {{ { uA, vA, w }, { uB, vB, w }, { uC, vC, w } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto w = (float)k/3.0;
                auto uA = (cA1[j].y * rad) + ((((cA2[j].y-cA1[j].y) * rad) / 3.0) * (float)i);
                auto vA = (cA1[j].x * rad) + ((((cA2[j].x-cA1[j].x) * rad) / 3.0) * (float)i);
                auto uB = (cB1[j].y * rad) + ((((cB2[j].y-cB1[j].y) * rad) / 3.0) * (float)i);
                auto vB = (cB1[j].x * rad) + ((((cB2[j].x-cB1[j].x) * rad) / 3.0) * (float)i);
                auto uC = ((cA1[j].y * rad) / 3.0) * (float)i;
                auto vC = cA1[j].x * rad;
                return {{ { vA, -uA + 1.0, w }, { vB, -uB + 1.0, w }, { vC, -uC + 1.0, w } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto w = (float)k/3.0;
                auto uA = (cA1[j].y * rad) + ((((cA2[j].y-cA1[j].y) * rad) / 3.0) * (float)i);
                auto vA = (cA1[j].x * rad) + ((((cA2[j].x-cA1[j].x) * rad) / 3.0) * (float)i);
                auto uB = (cB1[j].y * rad) + ((((cB2[j].y-cB1[j].y) * rad) / 3.0) * (float)i);
                auto vB = (cB1[j].x * rad) + ((((cB2[j].x-cB1[j].x) * rad) / 3.0) * (float)i);
                auto uC = ((cA1[j].y * rad) / 3.0) * (float)i;
                auto vC = cA1[j].x * rad;
                return {{ { -vA + 1.0, uA, w }, { -vB + 1.0, uB, w }, { -vC + 1.0, uC, w } }};
            },
            [&](int i, int j, int k) -> std::array<glm::vec3, 3> {
                auto w = (float)k/3.0;
                auto uA = (cA1[j].y * rad) + ((((cA2[j].y-cA1[j].y) * rad) / 3.0) * (float)i);
                auto vA = (cA1[j].x * rad) + ((((cA2[j].x-cA1[j].x) * rad) / 3.0) * (float)i);
                auto uB = (cB1[j].y * rad) + ((((cB2[j].y-cB1[j].y) * rad) / 3.0) * (float)i);
                auto vB = (cB1[j].x * rad) + ((((cB2[j].x-cB1[j].x) * rad) / 3.0) * (float)i);
                auto uC = ((cA1[j].y * rad) / 3.0) * (float)i;
                auto vC = cA1[j].x * rad;
                return {{ { -uA + 1.0, -vA + 1.0, w }, { -uB + 1.0, -vB + 1.0, w }, { -uC + 1.0, -vC + 1.0, w } }};
            }
        };
        auto target = functions[edge];

        for (int idx = 0, i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                for (int k = 0; k <= 3; k++, idx++) {
                    auto coefs = target(i, j, k);
                    cfsA[idx] = coefs[0];
                    cfsB[idx] = coefs[1];
                    cfsC[idx] = coefs[2];
                }

        return { cfsA, cfsB, cfsC };
    }

    const MachiningProcess::Params& MachiningProcessRoundedEdge::defaultParams() const {
        static MachiningProcess::Params params = {
            {"roundedEdge", { 0, machiningEdgeName } },
            {"roundedRadius", { 1.f, { 0.f, 1.f, 0.1f } } },
        };
        return params;
    }

    const char* MachiningProcessRoundedEdge::name() const {
        return "Rounded Edge";
    }
} // hs