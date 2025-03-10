//
// Created by Alberto Elorza Rubio on 19/12/2023.
//

#include "MachiningProcessHoleRing.h"

#include <functional>

namespace hs {
    MachiningProcess::Outcome MachiningProcessHoleRing::subTrimmedCell(const MachiningProcess::Params& params) const {
        int axis = params.at("holeRingDir");
        float radInS = params.at("holeRingInRadS");
        float radInT = params.at("holeRingInRadT");
        float radOutS = params.at("holeRingOutRadS");
        float radOutT = params.at("holeRoleOutRadT");
        float dispX = params.at("holeRingDispS");
        float dispY = params.at("holeRingDispT");

        glm::vec2 inRad { radInS * 1.1, radInT * 1.1 };
        glm::vec2 outRad { radOutS * 1.1, radOutT * 1.1 };
        glm::vec2 disp { dispX, dispY };

        constexpr glm::vec2 cA1[4] = {
            { -0.32173356, 0.32173365 }, { -0.14404498, 0.49942216 },
            { 0.14404507, 0.49942216 }, { 0.32173362, 0.3217336 }
        };
        constexpr glm::vec2 cA2[4] = {
            { 0, 1 }, { 1.f/3, 1 }, { 2.f/3, 1 }, { 1, 1 }
        };
        constexpr glm::vec2 cB1[4] = {
            { 0.32173362, 0.3217336 }, { 0.49942222, 0.14404488 },
            { 0.49942216, -0.14404507 }, { 0.3217336, -0.32173362 }
        };
        constexpr glm::vec2 cB2[4] = {
            { 1, 1 }, { 1, 2.f/3 }, { 1, 1.f/3 }, { 1, 0 }
        };
        constexpr glm::vec2 cC1[4] = {
            { 0.3217336, -0.32173362 }, { 0.14404503, -0.49942216 },
            { -0.14404514, -0.4994221 }, { -0.32173368, -0.32173353 }
        };
        constexpr glm::vec2 cC2[4] = {
            { 1, 0 }, { 2.f/3, 0 }, { 1.f/3, 0 }, { 0, 0 }
        };
        constexpr glm::vec2 cD1[4] = {
            { -0.32173368, -0.32173353 }, { -0.49942222, -0.14404495 },
            { -0.4994221, 0.1440451 }, { -0.32173356, 0.32173365 }
        };
        constexpr glm::vec2 cD2[4] = {
            { 0, 0 }, { 0, 1.f/3 }, { 0, 2.f/3 }, { 0, 1 }
        };

        std::array<glm::vec3, 64> cfsAA{}, cfsAB{}, cfsBA{}, cfsBB{}, cfsCA{}, cfsCB{}, cfsDA{}, cfsDB{};

        int idx = 0;

        auto doU = [&](int i, int j, int k) {
            glm::vec2 cAA = (cA1[k] * inRad) + disp, cAB = (cA1[k] * outRad) + disp,
                cBA = (cB1[k] * inRad) + disp, cBB = (cB1[k] * outRad) + disp,
                cCA = (cC1[k] * inRad) + disp, cCB = (cC1[k] * outRad) + disp,
                cDA = (cD1[k] * inRad) + disp, cDB = (cD1[k] * outRad) + disp;
            float u = (float)i/3.f;
            float vAB = cAA.y + (((cAB.y - cAA.y) / 3.f) * (float)j);
            float wAB = cAA.x + (((cAB.x - cAA.x) / 3.f) * (float)j);
            cfsAB[idx] = { u, vAB, wAB };
            float vAA = cAB.y + (((cA2[k].y - cAB.y) / 3.f) * (float)j);
            float wAA = cAB.x + (((cA2[k].x - cAB.x) / 3.f) * (float)j);
            cfsAA[idx] = { u, vAA, wAA };
            float vBB = cBA.y + (((cBB.y - cBA.y) / 3.f) * (float)j);
            float wBB = cBA.x + (((cBB.x - cBA.x) / 3.f) * (float)j);
            cfsBB[idx] = { u, vBB, wBB };
            float vBA = cBB.y + (((cB2[k].y - cBB.y) / 3.f) * (float)j);
            float wBA = cBB.x + (((cB2[k].x - cBB.x) / 3.f) * (float)j);
            cfsBA[idx] = { u, vBA, wBA };
            float vCB = cCA.y + (((cCB.y - cCA.y) / 3.f) * (float)j);
            float wCB = cCA.x + (((cCB.x - cCA.x) / 3.f) * (float)j);
            cfsCB[idx] = { u, vCB, wCB };
            float vCA = cCB.y + (((cC2[k].y - cCB.y) / 3.f) * (float)j);
            float wCA = cCB.x + (((cC2[k].x - cCB.x) / 3.f) * (float)j);
            cfsCA[idx] = { u, vCA, wCA };
            float vDB = cDA.y + (((cDB.y - cDA.y) / 3.f) * (float)j);
            float wDB = cDA.x + (((cDB.x - cDA.x) / 3.f) * (float)j);
            cfsDB[idx] = { u, vDB, wDB };
            float vDA = cDB.y + (((cD2[k].y - cDB.y) / 3.f) * (float)j);
            float wDA = cDB.x + (((cD2[k].x - cDB.x) / 3.f) * (float)j);
            cfsDA[idx] = { u, vDA, wDA };
        };

        auto doV = [&](int i, int j, int k) {
            glm::vec2 cAA = (cA1[i] * inRad) + disp, cAB = (cA1[i] * outRad) + disp,
                cBA = (cB1[i] * inRad) + disp, cBB = (cB1[i] * outRad) + disp,
                cCA = (cC1[i] * inRad) + disp, cCB = (cC1[i] * outRad) + disp,
                cDA = (cD1[i] * inRad) + disp, cDB = (cD1[i] * outRad) + disp;
            float v = (float)j/3.f;
            float wAB = cAA.y + (((cAB.y - cAA.y) / 3.f) * (float)k);
            float uAB = cAA.x + (((cAB.x - cAA.x) / 3.f) * (float)k);
            cfsAB[idx] = { uAB, v, wAB };
            float wAA = cAB.y + (((cA2[i].y - cAB.y) / 3.f) * (float)k);
            float uAA = cAB.x + (((cA2[i].x - cAB.x) / 3.f) * (float)k);
            cfsAA[idx] = { uAA, v, wAA };
            float wBB = cBA.y + (((cBB.y - cBA.y) / 3.f) * (float)k);
            float uBB = cBA.x + (((cBB.x - cBA.x) / 3.f) * (float)k);
            cfsBB[idx] = { uBB, v, wBB };
            float wBA = cBB.y + (((cB2[i].y - cBB.y) / 3.f) * (float)k);
            float uBA = cBB.x + (((cB2[i].x - cBB.x) / 3.f) * (float)k);
            cfsBA[idx] = { uBA, v, wBA };
            float wCB = cCA.y + (((cCB.y - cCA.y) / 3.f) * (float)k);
            float uCB = cCA.x + (((cCB.x - cCA.x) / 3.f) * (float)k);
            cfsCB[idx] = { uCB, v, wCB };
            float wCA = cCB.y + (((cC2[i].y - cCB.y) / 3.f) * (float)k);
            float uCA = cCB.x + (((cC2[i].x - cCB.x) / 3.f) * (float)k);
            cfsCA[idx] = { uCA, v, wCA };
            float wDB = cDA.y + (((cDB.y - cDA.y) / 3.f) * (float)k);
            float uDB = cDA.x + (((cDB.x - cDA.x) / 3.f) * (float)k);
            cfsDB[idx] = { uDB, v, wDB };
            float wDA = cDB.y + (((cD2[i].y - cDB.y) / 3.f) * (float)k);
            float uDA = cDB.x + (((cD2[i].x - cDB.x) / 3.f) * (float)k);
            cfsDA[idx] = { uDA, v, wDA };
        };

        auto doW = [&](int i, int j, int k) {
            glm::vec2 cAA = (cA1[j] * inRad) + disp, cAB = (cA1[j] * outRad) + disp,
                cBA = (cB1[j] * inRad) + disp, cBB = (cB1[j] * outRad) + disp,
                cCA = (cC1[j] * inRad) + disp, cCB = (cC1[j] * outRad) + disp,
                cDA = (cD1[j] * inRad) + disp, cDB = (cD1[j] * outRad) + disp;
            float w = (float)k/3.f;
            float uAB = cAA.y + (((cAB.y - cAA.y) / 3.f) * (float)i);
            float vAB = cAA.x + (((cAB.x - cAA.x) / 3.f) * (float)i);
            cfsAB[idx] = { uAB, vAB, w };
            float uAA = cAB.y + (((cA2[j].y - cAB.y) / 3.f) * (float)i);
            float vAA = cAB.x + (((cA2[j].x - cAB.x) / 3.f) * (float)i);
            cfsAA[idx] = { uAA, vAA, w };
            float uBB = cBA.y + (((cBB.y - cBA.y) / 3.f) * (float)i);
            float vBB = cBA.x + (((cBB.x - cBA.x) / 3.f) * (float)i);
            cfsBB[idx] = { uBB, vBB, w };
            float uBA = cBB.y + (((cB2[j].y - cBB.y) / 3.f) * (float)i);
            float vBA = cBB.x + (((cB2[j].x - cBB.x) / 3.f) * (float)i);
            cfsBA[idx] = { uBA, vBA, w };
            float uCB = cCA.y + (((cCB.y - cCA.y) / 3.f) * (float)i);
            float vCB = cCA.x + (((cCB.x - cCA.x) / 3.f) * (float)i);
            cfsCB[idx] = { uCB, vCB, w };
            float uCA = cCB.y + (((cC2[j].y - cCB.y) / 3.f) * (float)i);
            float vCA = cCB.x + (((cC2[j].x - cCB.x) / 3.f) * (float)i);
            cfsCA[idx] = { uCA, vCA, w };
            float uDB = cDA.y + (((cDB.y - cDA.y) / 3.f) * (float)i);
            float vDB = cDA.x + (((cDB.x - cDA.x) / 3.f) * (float)i);
            cfsDB[idx] = { uDB, vDB, w };
            float uDA = cDB.y + (((cD2[j].y - cDB.y) / 3.f) * (float)i);
            float vDA = cDB.x + (((cD2[j].x - cDB.x) / 3.f) * (float)i);
            cfsDA[idx] = { uDA, vDA, w };
        };

        const std::array<std::function<void(int, int, int)>, 3> functions = { doU, doV, doW };
        auto target = functions[axis];

        for (int i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                for (int k = 0; k <= 3; k++, idx++)
                    target(i, j, k);

        return { cfsAA, cfsAB, cfsBA, cfsBB, cfsCA, cfsCB, cfsDA, cfsDB };
    }

    const MachiningProcess::Params& MachiningProcessHoleRing::defaultParams() const {
        static MachiningProcess::Params params = {
            {"holeRingDir", { 0, uAxes } },
            {"holeRingInRadS", { 0.5f, { 0, 1, 0.01 } } },
            {"holeRingInRadT", { 0.5f, { 0, 1, 0.01 } } },
            {"holeRingOutRadS", { 0.75f, { 0, 1, 0.01 } } },
            {"holeRoleOutRadT", { 0.75f, { 0, 1, 0.01 } } },
            {"holeRingDispS", { 0.5f, { 0, 1, 0.01 } } },
            {"holeRingDispT", { 0.5f, { 0, 1, 0.01 } } }
        };
        return params;
    }

    const char* MachiningProcessHoleRing::name() const {
        return "Hole Ring";
    }
} // hs