//
// Created by Alberto Elorza Rubio on 29/01/2024.
//

#include "SceneStatus.h"

namespace hs {
    const std::string& SceneStatus::getError() {
        return error;
    }

    void SceneStatus::setError(std::string error) {
        SceneStatus::error = std::move(error);
    }

    void SceneStatus::clearError() {
        SceneStatus::error.clear();
    }
} // hs