//
// Created by Alberto Elorza Rubio on 07/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_VECTOR_H
#define HETEROGENEOUS_SOLIDS_VECTOR_H

#include <optional>
#include <vector>
#include <memory>

namespace hs::ext {

    template <class T>
    std::optional<std::reference_wrapper<T>> tryGet(const std::vector<std::unique_ptr<T>>& vector, size_t index) {
        if (vector.size() <= index) return std::nullopt;
        return *vector[index];
    }

    template <class T>
    std::optional<std::unique_ptr<T>> tryRemove(std::vector<std::unique_ptr<T>>& vector, size_t index) {
        if (vector.size() <= index) return std::nullopt;
        auto it = vector.begin() + index;
        std::unique_ptr<T> data = std::move(*it);
        vector.erase(it);
        return data;
    }

} // hs

#endif //HETEROGENEOUS_SOLIDS_VECTOR_H
