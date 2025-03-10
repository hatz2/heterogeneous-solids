//
// Created by Alberto Elorza Rubio on 17/12/2023.
//

#include "MachiningProcessHole.h"

namespace hs {
    MachiningProcess::Outcome MachiningProcessHole::subTrimmedCell(const MachiningProcess::Params& params) const {
        int axis = params.at("holeDir");
        float radS = params.at("holeRadiusS");
        float radT = params.at("holeRadiusT");
        float dispX = params.at("holeDispS");
        float dispY = params.at("holeDispT");

        glm::vec2 rad = { radS * 1.1, radT * 1.1 };
        glm::vec2 disp = { dispX, dispY };

        constexpr glm::vec2 cA1[4] = {
            { -0.32173356, 0.32173365 }, { -0.14404498, 0.49942216 },
            { 0.14404507, 0.49942216 }, { 0.32173362, 0.3217336 }
        };
        constexpr glm::vec2 cA2[4] = { { 0, 1 }, { 1.f/3, 1 }, { 2.f/3, 1 }, { 1, 1 } };

        constexpr glm::vec2 cB1[4] = {
            { 0.32173362, 0.3217336 }, { 0.49942222, 0.14404488 },
            { 0.49942216, -0.14404507 }, { 0.3217336, -0.32173362 }
        };
        constexpr glm::vec2 cB2[4] = { { 1, 1 }, { 1, 2.f/3 }, { 1, 1.f/3 }, { 1, 0 } };

        constexpr glm::vec2 cC1[4] = {
            { 0.3217336, -0.32173362 }, { 0.14404503, -0.49942216 },
            { -0.14404514, -0.4994221 }, { -0.32173368, -0.32173353 }
        };
        constexpr glm::vec2 cC2[4] = { { 1, 0 }, { 2.f/3, 0 }, { 1.f/3, 0 }, { 0, 0 } };

        constexpr glm::vec2 cD1[4] = {
            { -0.32173368, -0.32173353 }, { -0.49942222, -0.14404495 },
            { -0.4994221, 0.1440451 }, { -0.32173356, 0.32173365 }
        };
        constexpr glm::vec2 cD2[4] = { { 0, 0 }, { 0, 1.f/3 }, { 0, 2.f/3 }, { 0, 1 } };

        std::array<glm::vec3, 64> coefsA{}, coefsB{}, coefsC{}, coefsD{};

        switch (axis) {
            case 0:
                for (int idx = 0, i = 0; i <= 3; i++)
                    for (int j = 0; j <= 3; j++)
                        for (int k = 0; k <= 3; k++, idx++) {
                            auto cA = (cA1[k] * rad) + disp;
                            auto cB = (cB1[k] * rad) + disp;
                            auto cC = (cC1[k] * rad) + disp;
                            auto cD = (cD1[k] * rad) + disp;
                            auto u = (float)i/3.f;
                            auto vA = (cA.y + (((cA2[k].y - cA.y) / 3.f) * (float)j));
                            auto wA = (cA.x + (((cA2[k].x - cA.x) / 3.f) * (float)j));
                            coefsA[idx] = { u, vA, wA };
                            auto vB = (cB.y + (((cB2[k].y - cB.y) / 3.f) * (float)j));
                            auto wB = (cB.x + (((cB2[k].x - cB.x) / 3.f) * (float)j));
                            coefsB[idx] = { u, vB, wB };
                            auto vC = (cC.y + (((cC2[k].y - cC.y) / 3.f) * (float)j));
                            auto wC = (cC.x + (((cC2[k].x - cC.x) / 3.f) * (float)j));
                            coefsC[idx] = { u, vC, wC };
                            auto vD = (cD.y + (((cD2[k].y - cD.y) / 3.f) * (float)j));
                            auto wD = (cD.x + (((cD2[k].x - cD.x) / 3.f) * (float)j));
                            coefsD[idx] = { u, vD, wD };
                        }
                break;
            case 1:
                for (int idx = 0, i = 0; i <= 3; i++)
                    for (int j = 0; j <= 3; j++)
                        for (int k = 0; k <= 3; k++, idx++) {
                            auto cA = (cA1[i] * rad) + disp;
                            auto cB = (cB1[i] * rad) + disp;
                            auto cC = (cC1[i] * rad) + disp;
                            auto cD = (cD1[i] * rad) + disp;
                            auto v = (float)j/3.f;
                            auto wA = (cA.y + (((cA2[i].y - cA.y) / 3.f) * (float)k));
                            auto uA = (cA.x + (((cA2[i].x - cA.x) / 3.f) * (float)k));
                            coefsA[idx] = { uA, v, wA };
                            auto wB = (cB.y + (((cB2[i].y - cB.y) / 3.f) * (float)k));
                            auto uB = (cB.x + (((cB2[i].x - cB.x) / 3.f) * (float)k));
                            coefsB[idx] = { uB, v, wB };
                            auto wC = (cC.y + (((cC2[i].y - cC.y) / 3.f) * (float)k));
                            auto uC = (cC.x + (((cC2[i].x - cC.x) / 3.f) * (float)k));
                            coefsC[idx] = { uC, v, wC };
                            auto wD = (cD.y + (((cD2[i].y - cD.y) / 3.f) * (float)k));
                            auto uD = (cD.x + (((cD2[i].x - cD.x) / 3.f) * (float)k));
                            coefsD[idx] = { uD, v, wD };
                        }
                break;
            case 2:
                for (int idx = 0, i = 0; i <= 3; i++)
                    for (int j = 0; j <= 3; j++)
                        for (int k = 0; k <= 3; k++, idx++) {
                            auto cA = (cA1[j] * rad) + disp;
                            auto cB = (cB1[j] * rad) + disp;
                            auto cC = (cC1[j] * rad) + disp;
                            auto cD = (cD1[j] * rad) + disp;
                            auto w = (float)k/3.f;
                            auto uA = (cA.y + (((cA2[j].y - cA.y) / 3.f) * (float)i));
                            auto vA = (cA.x + (((cA2[j].x - cA.x) / 3.f) * (float)i));
                            coefsA[idx] = { uA, vA, w };
                            auto uB = (cB.y + (((cB2[j].y - cB.y) / 3.f) * (float)i));
                            auto vB = (cB.x + (((cB2[j].x - cB.x) / 3.f) * (float)i));
                            coefsB[idx] = { uB, vB, w };
                            auto uC = (cC.y + (((cC2[j].y - cC.y) / 3.f) * (float)i));
                            auto vC = (cC.x + (((cC2[j].x - cC.x) / 3.f) * (float)i));
                            coefsC[idx] = { uC, vC, w };
                            auto uD = (cD.y + (((cD2[j].y - cD.y) / 3.f) * (float)i));
                            auto vD = (cD.x + (((cD2[j].x - cD.x) / 3.f) * (float)i));
                            coefsD[idx] = { uD, vD, w };
                        }
                break;
            default:
                break;
        }

        return { coefsA, coefsB, coefsC, coefsD };
    }

    const MachiningProcess::Params& MachiningProcessHole::defaultParams() const {
        static MachiningProcess::Params params = {
            {"holeDir", { 0, uAxes } },
            {"holeRadiusS", { 0.5f, { 0, 1, 0.01 } } },
            {"holeRadiusT", { 0.5f, { 0, 1, 0.01 } } },
            {"holeDispS", { 0.5f, { 0, 1, 0.01 } } },
            {"holeDispT", { 0.5f, { 0, 1, 0.01 } } }
        };
        return params;
    }

    const char* MachiningProcessHole::name() const {
        return "Hole";
    }
} // hs