//
// Created by Alberto Elorza Rubio on 22/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SELECTIONCONTROLLER_H
#define HETEROGENEOUS_SOLIDS_SELECTIONCONTROLLER_H

#include <unordered_map>
#include <optional>
#include <glm/glm.hpp>
#include <variant>
#include "../shaders/Uniform.h"
#include "../utils/Vec3Hash.h"

namespace hs {
    class SceneNode;

    class SelectionController {
    public:
        using Selectable = std::variant<std::reference_wrapper<SceneNode>>;

        explicit SelectionController(Uniform selectionUniform);
        SelectionController(const SelectionController&) = delete;

        [[nodiscard]] Uniform getSelectionUniform() const;
        void setSelectionUniform(Uniform selectionUniform);

        void subscribeNextObject(Selectable object);

        [[nodiscard]] glm::vec3 getLast();

        std::optional<Selectable> getResult(glm::vec2 coords);
    private:
        Uniform selectionUniform;
        unsigned int indexCounter;
        glm::ivec3 lastIndex;
        std::unordered_map<glm::ivec3, Selectable, VecHash<int>, VecHash<int>> subscriptions;

        glm::ivec3 createNext();
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SELECTIONCONTROLLER_H
