//
// Created by Alberto Elorza Rubio on 01/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_BEZIERDATA_H
#define HETEROGENEOUS_SOLIDS_BEZIERDATA_H

#include <array>

namespace hs {

    struct PointAndTangentsST {
        glm::vec3 point;
        glm::vec3 tgS;
        glm::vec3 tgT;
    };

    struct PointAndTangentsUVW {
        glm::vec3 point;
        glm::vec3 tgU;
        glm::vec3 tgV;
        glm::vec3 tgW;
    };

    const size_t CurveCount = 12;

    const std::array<std::array<unsigned int, 4>, CurveCount> isoCurveCoefs = {{
        // – Indices de las cuatro iso-curvas en u –––––––––––––––––––––––––––––
        {{ 0, 16, 32, 48 }}, {{  3, 19, 35, 51 }}, {{ 12, 28, 44, 60 }}, {{ 15, 31, 47, 63 }},
        // – Indices de las cuatro iso-curvas en v –––––––––––––––––––––––––––––
        {{ 0,  4,  8, 12 }}, {{  3,  7, 11, 15 }}, {{ 48, 52, 56, 60 }}, {{ 51, 55, 59, 63 }},
        // – Indices de las cuatro iso-curvas en w –––––––––––––––––––––––––––––
        {{ 0,  1,  2,  3 }}, {{ 12, 13, 14, 15 }}, {{ 48, 49, 50, 51 }}, {{ 60, 61, 62, 63 }}
    }};

    const size_t SurfaceCount = 6;

    const std::array<std::array<unsigned int, 16>, SurfaceCount> isoSurfaceCoefs = {{
        // – Indices de las dos iso-superficies en u –––––––––––––––––––––––––––
        {{  0,  4,  8, 12,  1,  5,  9, 13,  2,  6, 10, 14,  3,  7, 11, 15 }},
        {{ 51, 55, 59, 63, 50, 54, 58, 62, 49, 53, 57, 61, 48, 52, 56, 60 }},
        // – Indices de las dos iso-superficies en v –––––––––––––––––––––––––––
        {{ 0,  1,  2,  3, 16, 17, 18, 19, 32, 33, 34, 35, 48, 49, 50, 51 }},
        {{ 15, 14, 13, 12, 31, 30, 29, 28, 47, 46, 45, 44, 63, 62, 61, 60 }},
        // – Indices de las dos iso-superficies en w –––––––––––––––––––––––––––
        {{ 48, 52, 56, 60, 32, 36, 40, 44, 16, 20, 24, 28,  0,  4,  8, 12 }},
        {{ 3,  7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51, 55, 59, 63 }}
    }};

    const std::array<std::array<unsigned int, 8>, 8> cornerPointNeighbors = {{
        {{ 0, 1, 4, 5, 16, 17, 20, 21 }},
        {{ 3, 2, 7, 6, 19, 18, 23, 22 }},
        {{ 12, 13, 8, 9, 28, 29, 24, 25 }},
        {{ 15, 14, 11, 10, 31, 30, 27, 26 }},
        {{ 48, 49, 52, 53, 32, 33, 36, 37 }},
        {{ 51, 50, 55, 54, 35, 34, 39, 38 }},
        {{ 60, 61, 56, 57, 44, 45, 40, 41 }},
        {{ 63, 62, 47, 46, 59, 58, 43, 42 }}
    }};

    const double BezierCircleTg = 0.552284749831;

} // hs

#endif //HETEROGENEOUS_SOLIDS_BEZIERDATA_H
