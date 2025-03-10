//
// Created by Alberto Elorza Rubio on 29/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SCENESTATUS_H
#define HETEROGENEOUS_SOLIDS_SCENESTATUS_H

#include <string>

namespace hs {

    class SceneStatus {
    public:
        SceneStatus() = default;

        [[nodiscard]] const std::string& getError();
        void setError(std::string error);
        void clearError();
    private:
        std::string error;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SCENESTATUS_H
