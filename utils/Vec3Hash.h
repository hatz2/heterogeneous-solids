//
// Created by Alberto Elorza Rubio on 23/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_VEC3HASH_H
#define HETEROGENEOUS_SOLIDS_VEC3HASH_H

#include <functional>
#include <glm/glm.hpp>

namespace hs {

    template <typename T>
    struct VecHash {
        size_t operator()(const glm::vec<3, T>& v) const {
            return std::hash<T>()(v.x) ^ std::hash<T>()(v.y) ^ std::hash<T>()(v.z);
        }

        bool operator()(const glm::vec<3, T>& a, const glm::vec<3, T>& b) const {
            return a.x == b.x && a.y == b.y && a.z == b.z;
        }
    };

}

#endif //HETEROGENEOUS_SOLIDS_VEC3HASH_H
