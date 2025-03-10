//
// Created by Alberto Elorza Rubio on 28/12/2023.
//

#include "MachiningProcessGearTeeth.h"

#include <glm/ext/matrix_transform.hpp>

namespace hs {
    MachiningProcess::Outcome MachiningProcessGearTeeth::subTrimmedCell(const MachiningProcess::Params& params) const {
        int teethAxe = std::min(std::max(0, (int)params.at("teethAxe")), 7);
        float teethWidth = params.at("teethWidth");
        float baseHeight = params.at("teethBaseHeight");

        auto s = 1 - teethWidth;
        auto w = 0.5 - (1.5 * teethWidth);

        std::array<float, 4> p0 = { baseHeight, baseHeight, 1, 1 };
        std::array<float, 4> p1 = { 1.f - baseHeight, 1.f - baseHeight, 0, 0 };

        auto rotateAroundZ = [](float degrees) -> glm::mat4 {
            return glm::rotate(glm::mat4(1), glm::radians(degrees), { 0, 0, 1 });
        };

        glm::mat4 rotation;
        auto operate = [&rotation](glm::vec3& item, glm::vec3 offset) {
            item = glm::vec3(rotation * glm::vec4(item, 0)) + offset;
        };

        std::array<glm::vec3, 64> c0{}, c1{}, c2{}, c3{}, c4{};

        for (int idx = 0, i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                for (int k = 0; k <= 3; k++, idx++) {
                    switch (teethAxe) {
                        case 0:
                            rotation = rotateAroundZ(-90);
                            c0[idx] = { (float(i)/3.0), (1.0-baseHeight) + ((float(j)/3.0) * baseHeight), (float(k)/3.0) * teethWidth };
                            operate(c0[idx], {0, 1, 0});
                            c1[idx] = { (float(i)/3.0), p1[k] + ((float(j)/3.0) * p0[k]), teethWidth + ((float(k)/3.0) * w) };
                            operate(c1[idx], {0, 1, 0});
                            c2[idx] = { (float(i)/3.0), (float(j)/3.0), (0.5 - (teethWidth/2.0)) + ((float(k)/3.0) * teethWidth) };
                            operate(c2[idx], {0, 1, 0});
                            c3[idx] = { (float(i)/3.0), p1[3-k] + ((float(j)/3.0) * p0[3-k]), 0.5 + (teethWidth/2.0) + ((float(k)/3.0) * w) };
                            operate(c3[idx], {0, 1, 0});
                            c4[idx] = { (float(i)/3.0), (1.0-baseHeight) + ((float(j)/3.0) * baseHeight), s + ((float(k)/3.0) * teethWidth) };
                            operate(c4[idx], {0, 1, 0});
                            break;
                        case 1:
                            rotation = rotateAroundZ(90);
                            c0[idx] = { (float(i)/3.0) * teethWidth, (1.0-baseHeight) + ((float(j)/3.0) * baseHeight), float(k)/3.0 };
                            operate(c0[idx], {1, 0, 0});
                            c1[idx] = { teethWidth + ((float(i)/3.0) * w), p1[i] + ((float(j)/3.0) * p0[i]), float(k)/3.0 };
                            operate(c1[idx], {1, 0, 0});
                            c2[idx] = { (0.5 - (teethWidth/2.0)) + (float(i)/3.0) * teethWidth, float(j)/3.0, float(k)/3.0 };
                            operate(c2[idx], {1, 0, 0});
                            c3[idx] = { 0.5 + (teethWidth/2.0) + ((float(i)/3.0) * w), p1[3-i] + ((float(j)/3.0) * p0[3-i]), float(k)/3.0 };
                            operate(c3[idx], {1, 0, 0});
                            c4[idx] = { s + ((float(i)/3.0) * teethWidth), (1.0-baseHeight) + ((float(j)/3.0) * baseHeight), float(k)/3.0 };
                            operate(c4[idx], {1, 0, 0});
                            break;
                        case 2:
                            rotation = rotateAroundZ(-90);
                            c0[idx] = { (float)i/3.0, ((float)j/3.0) * baseHeight, ((float)k/3.0) * teethWidth };
                            operate(c0[idx], {0, 1, 0});
                            c1[idx] = { (float)i/3.0, ((float)j/3.0) * p0[k], teethWidth + (((float)k/3.0) * w) };
                            operate(c1[idx], {0, 1, 0});
                            c2[idx] = { (float)i/3.0, (float)j/3.0, (0.5 - (teethWidth/2.0)) + ((float)k/3.0) * teethWidth };
                            operate(c2[idx], {0, 1, 0});
                            c3[idx] = { (float)i/3.0, ((float)j/3.0) * p0[3-k], 0.5 + (teethWidth/2.0) + (((float)k/3.0) * w) };
                            operate(c3[idx], {0, 1, 0});
                            c4[idx] = { (float)i/3.0, (float)j/3.0 * baseHeight, s + ((float)k/3.0) * teethWidth };
                            operate(c4[idx], {0, 1, 0});
                            break;
                        case 3:
                            rotation = rotateAroundZ(90);
                            c0[idx] = { (float(i)/3.0) * teethWidth, (float(j)/3.0) * baseHeight, float(k)/3.0 };
                            operate(c0[idx], {1, 0, 0});
                            c1[idx] = { teethWidth + ((float(i)/3.0) * w), (float(j)/3.0) * p0[i], float(k)/3.0 };
                            operate(c1[idx], {1, 0, 0});
                            c2[idx] = { (0.5 - (teethWidth/2.0)) + (float(i)/3.0) * teethWidth, float(j)/3.0, float(k)/3.0 };
                            operate(c2[idx], {1, 0, 0});
                            c3[idx] = { 0.5 + (teethWidth/2.0) + ((float(i)/3.0) * w), (float(j)/3.0) * p0[3-i], float(k)/3.0 };
                            operate(c3[idx], {1, 0, 0});
                            c4[idx] = { s + ((float(i)/3.0) * teethWidth), (float(j)/3.0) * baseHeight, float(k)/3.0 };
                            operate(c4[idx], {1, 0, 0});
                            break;
                        case 4:
                            c0[idx] = { (float(i)/3.0), (1.0-baseHeight) + ((float(j)/3.0) * baseHeight), (float(k)/3.0) * teethWidth };
                            c1[idx] = { (float(i)/3.0), p1[k] + ((float(j)/3.0) * p0[k]), teethWidth + ((float(k)/3.0) * w) };
                            c2[idx] = { (float(i)/3.0), (float(j)/3.0), (0.5 - (teethWidth/2.0)) + ((float(k)/3.0) * teethWidth) };
                            c3[idx] = { (float(i)/3.0), p1[3-k] + ((float(j)/3.0) * p0[3-k]), 0.5 + (teethWidth/2.0) + ((float(k)/3.0) * w) };
                            c4[idx] = { (float(i)/3.0), (1.0-baseHeight) + ((float(j)/3.0) * baseHeight), s + ((float(k)/3.0) * teethWidth) };
                            break;
                        case 5:
                            c0[idx] = { (float(i)/3.0) * teethWidth, (1.0-baseHeight) + ((float(j)/3.0) * baseHeight), float(k)/3.0 };
                            c1[idx] = { teethWidth + ((float(i)/3.0) * w), p1[i] + ((float(j)/3.0) * p0[i]), float(k)/3.0 };
                            c2[idx] = { (0.5 - (teethWidth/2.0)) + (float(i)/3.0) * teethWidth, float(j)/3.0, float(k)/3.0 };
                            c3[idx] = { 0.5 + (teethWidth/2.0) + ((float(i)/3.0) * w), p1[3-i] + ((float(j)/3.0) * p0[3-i]), float(k)/3.0 };
                            c4[idx] = { s + ((float(i)/3.0) * teethWidth), (1.0-baseHeight) + ((float(j)/3.0) * baseHeight), float(k)/3.0 };
                            break;
                        case 6:
                            c0[idx] = { (float)i/3.0, ((float)j/3.0) * baseHeight, ((float)k/3.0) * teethWidth };
                            c1[idx] = { (float)i/3.0, ((float)j/3.0) * p0[k], teethWidth + (((float)k/3.0) * w) };
                            c2[idx] = { (float)i/3.0, (float)j/3.0, (0.5 - (teethWidth/2.0)) + ((float)k/3.0) * teethWidth };
                            c3[idx] = { (float)i/3.0, ((float)j/3.0) * p0[3-k], 0.5 + (teethWidth/2.0) + (((float)k/3.0) * w) };
                            c4[idx] = { (float)i/3.0, (float)j/3.0 * baseHeight, s + ((float)k/3.0) * teethWidth };
                            break;
                        case 7:
                            c0[idx] = { (float(i)/3.0) * teethWidth, (float(j)/3.0) * baseHeight, float(k)/3.0 };
                            c1[idx] = { teethWidth + ((float(i)/3.0) * w), (float(j)/3.0) * p0[i], float(k)/3.0 };
                            c2[idx] = { (0.5 - (teethWidth/2.0)) + (float(i)/3.0) * teethWidth, float(j)/3.0, float(k)/3.0 };
                            c3[idx] = { 0.5 + (teethWidth/2.0) + ((float(i)/3.0) * w), (float(j)/3.0) * p0[3-i], float(k)/3.0 };
                            c4[idx] = { s + ((float(i)/3.0) * teethWidth), (float(j)/3.0) * baseHeight, float(k)/3.0 };
                            break;
                        default:
                            break;
                    }
                }

        return { c0, c1, c2, c3, c4 };
    }

    const MachiningProcess::Params& MachiningProcessGearTeeth::defaultParams() const {
        static MachiningProcess::Params params = {
            {"teethAxe", { 0, { 0, 7, 1 } } },
            {"teethWidth", { 0.1f, { 0, 1, 0.01 } } },
            {"teethBaseHeight", { 0.05f, { 0, 1, 0.01 } } },
        };
        return params;
    }

    const char* MachiningProcessGearTeeth::name() const {
        return "Gear Teeth";
    }
} // hs