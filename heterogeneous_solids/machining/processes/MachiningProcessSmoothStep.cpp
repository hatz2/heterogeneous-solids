//
// Created by Alberto Elorza Rubio on 19/12/2023.
//

#include "MachiningProcessSmoothStep.h"

#include <functional>
#include <array>

namespace hs {
    MachiningProcess::Outcome MachiningProcessSmoothStep::subTrimmedCell(const MachiningProcess::Params& params) const {
        int axe = params.at("sStepAxe");
        float d0Down = params.at("sStepD0Down");
        float d1Down = params.at("sStepD1Down");
        float d0Up = params.at("sStepD0Up");
        float d1Up = params.at("sStepD1Up");

        std::array<glm::vec3, 64> coefs{};

        const std::array<float, 4> s = { d0Down, d0Down, d0Up, d0Up };
        const std::array<float, 4> m = { 1.f - d0Down - d1Down, 1.f - d0Down - d1Down,
                                         1.f - d0Up - d1Up, 1.f - d0Up - d1Up };

        const std::array<std::function<glm::vec3(int, int, int)>, 12> functions = {
            [&](int i, int j, int k) -> glm::vec3 { return { i/3., j/3., s[3-i] + ((k / 3.0) * m[3-i]) }; },
            [&](int i, int j, int k) -> glm::vec3 { return { i/3., s[3-i] + ((j / 3.0) * m[3-i]), k/3. }; },
            [&](int i, int j, int k) -> glm::vec3 { return { i/3., j/3., s[i] + ((k / 3.0) * m[i]) }; },
            [&](int i, int j, int k) -> glm::vec3 { return { i/3., s[i] + ((j / 3.0) * m[i]), k/3. }; },

            [&](int i, int j, int k) -> glm::vec3 { return { i/3., j/3., s[3-j] + ((k / 3.0) * m[3-j]) }; },
            [&](int i, int j, int k) -> glm::vec3 { return { s[3-j] + ((i / 3.0) * m[3-j]), j/3., k/3. }; },
            [&](int i, int j, int k) -> glm::vec3 { return { i/3., j/3., s[j] + ((k / 3.0) * m[j]) }; },
            [&](int i, int j, int k) -> glm::vec3 { return { s[j] + ((i / 3.0) * m[j]), j/3., k/3. }; },

            [&](int i, int j, int k) -> glm::vec3 { return { i/3., s[3-k] + ((j / 3.0) * m[3-k]), k/3. }; },
            [&](int i, int j, int k) -> glm::vec3 { return { s[3-k] + ((i / 3.0) * m[3-k]), j/3., k/3. }; },
            [&](int i, int j, int k) -> glm::vec3 { return { i/3., s[k] + ((j / 3.0) * m[k]), k/3. }; },
            [&](int i, int j, int k) -> glm::vec3 { return { s[k] + ((i / 3.0) * m[k]), j/3., k/3. }; }
        };
        auto target = functions[axe];

        for (int idx = 0, i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                for (int k = 0; k <= 3; k++, idx++)
                    coefs[idx] = target(i, j, k);

        return { coefs };
    }

    const MachiningProcess::Params& MachiningProcessSmoothStep::defaultParams() const {
        static MachiningProcess::Params params = {
            {"sStepAxe", { 0, machiningEdgeName } },
            {"sStepD0Down", { 0.15f, { 0, 1, 0.01 } } },
            {"sStepD1Down", { 0.5f, { 0, 1, 0.01 } } },
            {"sStepD0Up", { 0.0f, { 0, 1, 0.01 } } },
            {"sStepD1Up", { 0.0f, { 0, 1, 0.01 } } }
        };
        return params;
    }

    const char* MachiningProcessSmoothStep::name() const {
        return "Smooth Step";
    }
} // hs