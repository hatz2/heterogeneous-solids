//
// Created by Alberto Elorza Rubio on 21/11/2023.
//

#include <glm/ext/matrix_transform.hpp>
#include <utility>
#include "Transform.h"

namespace hs {
    Transform::Transform() :
        localScale(1), localRotation(0), localTranslation(0),
        updated(true), modelMatrix(0), parentMatrix(1), parentTransform(nullptr)
    {

    }

    Transform::~Transform() {
        if (parentTransform) parentTransform->detachObserver(this);
    }

    std::optional<Transform*> Transform::getParent() const {
        if (parentTransform) return parentTransform;
        return std::nullopt;
    }

    void Transform::setParent(Transform& parent) {
        if (parentTransform) parentTransform->detachObserver(this);
        parentTransform = &parent;
        parentTransform->attachObserver(this);
        parentMatrix = parent.matrix();
        updateSubject(*this);
    }

    void Transform::removeParent() {
        if (parentTransform) parentTransform->detachObserver(this);
        parentTransform = nullptr;
        parentMatrix = glm::mat4(1);
        updateSubject(*this);
    }

    const glm::vec3& Transform::getScale() const {
        return localScale;
    }

    const glm::vec3& Transform::getRotation() const {
        return localRotation;
    }

    const glm::vec3& Transform::getTranslation() const {
        return localTranslation;
    }

    void Transform::setScale(glm::vec3 scale) {
        localScale = scale;
        updated = true;
        updateSubject(*this);
    }

    void Transform::setRotation(glm::vec3 rotation) {
        localRotation = rotation;
        updated = true;
        updateSubject(*this);
    }

    void Transform::setTranslation(glm::vec3 translation) {
        localTranslation = translation;
        updated = true;
        updateSubject(*this);
    }

    void Transform::scale(glm::vec3 scale) {
        localScale *= scale;
        updated = true;
        updateSubject(*this);
    }

    void Transform::rotate(glm::vec3 rotation) {
        localRotation += rotation;
        updated = true;
        updateSubject(*this);
    }

    void Transform::translate(glm::vec3 translation) {
        localTranslation += translation;
        updated = true;
        updateSubject(*this);
    }

    void Transform::resetScale() {
        localScale = glm::vec3(1);
        updated = true;
        updateSubject(*this);
    }

    void Transform::resetRotation() {
        localRotation = glm::vec3(0);
        updated = true;
        updateSubject(*this);
    }

    void Transform::resetTranslation() {
        localTranslation = glm::vec3(0);
        updated = true;
        updateSubject(*this);
    }

    void Transform::resetAll() {
        localScale = glm::vec3(1);
        localRotation = glm::vec3(0);
        localTranslation = glm::vec3(0);
        updated = true;
        updateSubject(*this);
    }

    glm::mat4 Transform::localMatrix() {
        if (updated) {
            auto rotation = glm::rotate(glm::mat4(1), glm::radians(localRotation.x), {1, 0, 0});
            rotation = glm::rotate(rotation, glm::radians(localRotation.y), {0, 1, 0});
            rotation = glm::rotate(rotation, glm::radians(localRotation.z), {0, 0, 1});
            modelMatrix =
                glm::translate(glm::mat4(1), localTranslation) *
                rotation *
                glm::scale(glm::mat4(1), localScale);
            updated = false;
        }
        return modelMatrix;
    }

    glm::mat4 Transform::matrix() {
        auto matrix = localMatrix();
        return parentMatrix * matrix;
    }

    void Transform::updateObserver(Transform& parent) {
        parentMatrix = parent.matrix();
        updateSubject(*this);
    }
} // hs