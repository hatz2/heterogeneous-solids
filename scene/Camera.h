//
// Created by Alberto Elorza Rubio on 19/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_CAMERA_H
#define HETEROGENEOUS_SOLIDS_CAMERA_H

#include <glm/glm.hpp>

namespace hs {

    enum class CameraMode {
        Perspective,
        Parallel
    };

    class Camera {
    public:
        Camera();
        Camera(const Camera&) = default;

        [[nodiscard]] float getFovY() const;
        void setFovY(float fovY);

        [[nodiscard]] float getAspect() const;
        void setAspect(float aspect);

        [[nodiscard]] float getZNearPerspective() const;
        void setZNearPerspective(float zNear);

        [[nodiscard]] float getZFarPerspective() const;
        void setZFarPerspective(float zFar);

        [[nodiscard]] float getZNearParallel() const;
        void setZNearParallel(float zNear);

        [[nodiscard]] float getZFarParallel() const;
        void setZFarParallel(float zFar);

        [[nodiscard]] float getWidth() const;
        void setWidth(float width);

        [[nodiscard]] float getHeight() const;
        void setHeight(float height);

        [[nodiscard]] glm::vec3 getPosition() const;
        void setPosition(glm::vec3 position);

        [[nodiscard]] glm::vec3 getLookAt() const;
        void setLookAt(glm::vec3 lookAt);

        [[nodiscard]] glm::vec3 getUp() const;
        void setUp(glm::vec3 up);

        [[nodiscard]] CameraMode getMode() const;
        void setMode(CameraMode mode);

        void translate(glm::vec3 movement);
        void translatePosition(glm::vec3 movement);
        void rotate(float angle, glm::vec3 axis);
        void orbit(float angle, glm::vec3 axis);
        void completeOrbit(float angleSide, float angleUp);
        void zoomFov(float value);

        [[nodiscard]] glm::vec3 direction() const;

        [[nodiscard]] glm::mat4 view() const;
        [[nodiscard]] glm::mat4 projection() const;
        [[nodiscard]] glm::mat4 perspectiveProjection() const;
        [[nodiscard]] glm::mat4 parallelProjection() const;
    private:
        // Aspect value
        float aspect;
        // Perspective Projection values
        float fovY, zNearPerspective, zFarPerspective;
        // Parallel Projection values
        float width, height, zNearParallel, zFarParallel;
        // View Projection values
        glm::vec3 position, lookAt, up;
        // Projection mode
        CameraMode mode;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CAMERA_H
