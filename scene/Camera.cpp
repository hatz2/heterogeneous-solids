//
// Created by Alberto Elorza Rubio on 19/11/2023.
//

#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace hs {
    Camera::Camera() :
        aspect(1),
        fovY(120), zNearPerspective(0.01), zFarPerspective(150),
        width(12), height(12), zNearParallel(-100), zFarParallel(150),
        position({0, 2, 5}), lookAt(0), up({0, 1, 0}),
        mode(CameraMode::Perspective)
    {

    }

    float Camera::getFovY() const {
        return fovY;
    }

    void Camera::setFovY(float fovY) {
        Camera::fovY = fovY;
    }

    float Camera::getAspect() const {
        return aspect;
    }

    void Camera::setAspect(float aspect) {
        Camera::aspect = aspect;
    }

    float Camera::getZNearPerspective() const {
        return zNearPerspective;
    }

    void Camera::setZNearPerspective(float zNear) {
        Camera::zNearPerspective = zNear;
    }

    float Camera::getZFarPerspective() const {
        return zFarPerspective;
    }

    void Camera::setZFarPerspective(float zFar) {
        Camera::zFarPerspective = zFar;
    }

    float Camera::getZNearParallel() const {
        return zNearParallel;
    }

    void Camera::setZNearParallel(float zNear) {
        Camera::zNearParallel = zNear;
    }

    float Camera::getZFarParallel() const {
        return zFarParallel;
    }

    void Camera::setZFarParallel(float zFar) {
        Camera::zFarParallel = zFar;
    }

    float Camera::getWidth() const {
        return width;
    }

    void Camera::setWidth(float width) {
        Camera::width = width;
    }

    float Camera::getHeight() const {
        return height;
    }

    void Camera::setHeight(float height) {
        Camera::height = height;
    }

    glm::vec3 Camera::getPosition() const {
        return position;
    }

    void Camera::setPosition(glm::vec3 position) {
        Camera::position = position;
    }

    glm::vec3 Camera::getLookAt() const {
        return lookAt;
    }

    void Camera::setLookAt(glm::vec3 lookAt) {
        Camera::lookAt = lookAt;
    }

    glm::vec3 Camera::getUp() const {
        return up;
    }

    void Camera::setUp(glm::vec3 up) {
        Camera::up = up;
    }

    CameraMode Camera::getMode() const {
        return mode;
    }

    void Camera::setMode(CameraMode mode) {
        Camera::mode = mode;
    }

    void Camera::translate(glm::vec3 movement) {
        Camera::lookAt += movement;
        Camera::position += movement;
    }

    void Camera::translatePosition(glm::vec3 movement) {
        Camera::position += movement;
    }

    void Camera::rotate(float angle, glm::vec3 axis) {
        glm::vec3 vector = lookAt - position;
        glm::vec3 rotatedVector = glm::rotate(vector, glm::radians(angle), axis);
        lookAt = rotatedVector + position;
    }

    void Camera::orbit(float angle, glm::vec3 axis) {
        glm::vec3 vector = position - lookAt;
        glm::vec3 rotatedVector = glm::rotate(vector, glm::radians(angle), axis);
        position = rotatedVector + lookAt;
    }

    void Camera::completeOrbit(float angleSide, float angleUp) {
        glm::vec3 vector = position - lookAt;
        // Prevent vector 0 edge case
        if (glm::all(glm::epsilonEqual(vector, { 0, 0, 0 }, glm::epsilon<float>())))
            vector = { 0, 0, 1 };

        glm::vec3 side = glm::cross(vector, up);

        // Prevent collinear edge case
        if (glm::all(glm::epsilonEqual(side, { 0, 0, 0 }, glm::epsilon<float>())))
            side = { 1, 0, 0 };

        vector = glm::rotate(vector, glm::radians(angleSide), side);
        up = glm::normalize(glm::vec3{0, -glm::cross(vector, side).y, 0});
        vector = glm::rotate(vector, glm::radians(angleUp), up);
        position = vector + lookAt;
    }

    void Camera::zoomFov(float value) {
        fovY = glm::clamp(fovY + value, 10.f, 120.f);
    }

    glm::vec3 Camera::direction() const {
        return lookAt - position;
    }

    glm::mat4 Camera::view() const {
        glm::vec3 vector = position - lookAt;
        // Prevent vector 0 edge case
        if (glm::all(glm::epsilonEqual(vector, { 0, 0, 0 }, glm::epsilon<float>())))
            vector = { 1, 0, 0 };

        glm::vec3 side = glm::cross(vector, up);

        // Prevent collinear edge case
        if (glm::all(glm::epsilonEqual(side, { 0, 0, 0 }, glm::epsilon<float>())))
            return glm::lookAt(vector + lookAt, position - vector, { 0, 0, 1 });

        return glm::lookAt(vector + lookAt, position - vector, up);
    }

    glm::mat4 Camera::projection() const {
        switch (mode) {
            default:
            case CameraMode::Perspective:
                return perspectiveProjection();
            case CameraMode::Parallel:
                return parallelProjection();
        }
    }

    glm::mat4 Camera::perspectiveProjection() const {
        return glm::perspective(glm::radians(fovY), aspect, zNearPerspective, zFarPerspective);
    }

    glm::mat4 Camera::parallelProjection() const {
        return glm::ortho(-width*aspect/2, width*aspect/2, -height/2, height/2, zNearParallel, zFarParallel);
    }
} // hs