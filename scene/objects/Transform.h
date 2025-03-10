//
// Created by Alberto Elorza Rubio on 21/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_TRANSFORM_H
#define HETEROGENEOUS_SOLIDS_TRANSFORM_H

#include <glm/glm.hpp>
#include <memory>
#include <optional>
#include "../../utils/Observer.h"

namespace hs {

    class Transform: public Subject<Transform&>, private Observer<Transform&> {
    public:
        Transform();
        ~Transform() override;

        [[nodiscard]] std::optional<Transform*> getParent() const;
        void setParent(Transform& parent);
        void removeParent();

        [[nodiscard]] const glm::vec3& getScale() const;
        [[nodiscard]] const glm::vec3& getRotation() const;
        [[nodiscard]] const glm::vec3& getTranslation() const;

        void setScale(glm::vec3 scale);
        void setRotation(glm::vec3 rotation);
        void setTranslation(glm::vec3 translation);

        void scale(glm::vec3 scale);
        void rotate(glm::vec3 rotation);
        void translate(glm::vec3 translation);

        void resetScale();
        void resetRotation();
        void resetTranslation();
        void resetAll();

        glm::mat4 localMatrix();
        glm::mat4 matrix();
    private:
        glm::vec3 localScale;
        glm::vec3 localRotation;
        glm::vec3 localTranslation;

        bool updated;
        glm::mat4 modelMatrix;
        glm::mat4 parentMatrix;
        Transform* parentTransform;

        void updateObserver(Transform& parent) override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_TRANSFORM_H
