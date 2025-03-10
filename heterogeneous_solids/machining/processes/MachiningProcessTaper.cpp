//
// Created by Alberto Elorza Rubio on 18/12/2023.
//

#include "MachiningProcessTaper.h"

#include <functional>
#include <array>

namespace hs {
    MachiningProcess::Outcome MachiningProcessTaper::subTrimmedCell(const MachiningProcess::Params& params) const {
        int axe = params.at("taperAxe");
        float d0 = params.at("taperD0");
        float d1 = params.at("taperD1");

        std::array<glm::vec3, 64> coefs{};

        const std::array<float, 4> s = { 0, 0, d0/3.f, d0 };
        const std::array<float, 4> m = { 1, 1, 1 - ((d0 + d1)/3), 1-(d0+d1) };

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

    const MachiningProcess::Params& MachiningProcessTaper::defaultParams() const {
        static MachiningProcess::Params params = {
            {"taperAxe", { 0, machiningEdgeName } },
            {"taperD0", { 0.1f, { 0, 1, 0.01 } } },
            {"taperD1", { 0.1f, { 0, 1, 0.01 } } }
        };
        return params;
    }

    const char* MachiningProcessTaper::name() const {
        return "Taper";
    }
} // hs