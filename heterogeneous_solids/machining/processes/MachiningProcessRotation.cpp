//
// Created by Alberto Elorza Rubio on 10/01/2024.
//

#include <glm/gtx/transform.hpp>
#include "MachiningProcessRotation.h"

namespace hs {
    MachiningProcess::Outcome MachiningProcessRotation::subTrimmedCell(const MachiningProcess::Params& params) const {
        float angle = params.at("angle");

        float axisX = params.at("axisX");
        float axisY = params.at("axisY");
        float axisZ = params.at("axisZ");

        auto rotation = glm::translate(
            glm::rotate(
                glm::translate(glm::mat4(1), { 0.5, 0.5, 0.5 }),
                glm::radians(angle), { axisX, axisY, axisZ }
            ),
            { -0.5, -0.5f, -0.5}
        );

        std::array<glm::vec3, 64> coefs{};
        for (int idx = 0, i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                for (int k = 0; k <= 3; k++, idx++) {
                    auto coef = rotation * glm::vec4{ (float)i/3.f, (float)j/3.f, (float)k/3.f, 1 };
                    coefs[idx] = {
                        std::min(1.f, std::max(coef.x, 0.f)),
                        std::min(1.f, std::max(coef.y, 0.f)),
                        std::min(1.f, std::max(coef.z, 0.f))
                    };
                }
        return { coefs };
    }

    const MachiningProcess::Params& MachiningProcessRotation::defaultParams() const {
        static MachiningProcess::Params params = {
            {"angle", { 90.f, { 0., 360., 1. } } },
            {"axisX", { 1, { 0, 1, 1 } } },
            {"axisY", { 0, { 0, 1, 1 } } },
            {"axisZ", { 0, { 0, 1, 1 } } },
        };
        return params;
    }

    const char* MachiningProcessRotation::name() const {
        return "Rotation";
    }
} // hs