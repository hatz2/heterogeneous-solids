//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#include "utils.h"

#include <glm/glm.hpp>

namespace hs {
    float B(int i, float param) {
        switch (i) {
            case 0:
                return powf(1.f - param, 3);
            case 1:
                return 3.f * powf(1.f - param, 2) * param;
            case 2:
                return 3.f * powf(param, 2) * (1.f - param);
            case 3:
                return powf(param, 3);
            default:
                return 0.f;
        }
    }

    float BD(int i, float param) {
        switch (i) {
            case 0:
                return (6.f * param) - 3.f - (3.f * powf(param, 2));
            case 1:
                return (9.f * powf(param, 2)) - (12.f * param) + 3.f;
            case 2:
                return (6.f * param) - (9.f * powf(param, 2));
            case 3:
                return 3.f * powf(param, 2);
            default:
                return 0.f;
        }
    }
} // hs