//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_UTILS_H
#define HETEROGENEOUS_SOLIDS_UTILS_H

#include <array>
#include "glm/glm.hpp"

namespace hs {

    float B(int i, float param);

    float BD(int i, float param);

    constexpr std::array<glm::vec3, 64> getDefaultCoefs() {
        std::array<glm::vec3, 64> coefs{};
        for (int i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                for (int k = 0; k <= 3; k++)
                    coefs[i * 16 + j * 4 + k] = {(float) i / 3.f, (float) j / 3.f, (float) k / 3.f};
        return coefs;
    }
} // hs

#endif //HETEROGENEOUS_SOLIDS_UTILS_H
