//
// Created by Alberto Elorza Rubio on 01/12/2023.
//

#include "CameraEventHandler.h"

namespace hs {
    CameraEventHandler::CameraEventHandler(Camera &camera): camera(camera) {

    }

    void CameraEventHandler::handle(const MouseEvent& event) {
        switch (event.index()) {
            case 1: {
                auto &dragEvent = std::get<1>(event);
                switch (dragEvent.button) {
                    case MouseButton::Left:
                        break;
                    case MouseButton::Middle: {
                        glm::vec3 axis = glm::normalize(camera.direction());
                        camera.translate(
                            glm::cross(axis, { 0, dragEvent.relativeX * -0.07, 0 }) +
                            glm::vec3{ 0, dragEvent.relativeY * -0.08, 0 }
                        );
                        break;
                    }
                    case MouseButton::Right:
                        camera.completeOrbit(dragEvent.relativeY * 0.5f, dragEvent.relativeX * 0.5f);
                        break;
                }
                break;
            }
            case 2: {
                auto &scrollEvent = std::get<2>(event);
                float factor = scrollEvent.shift ? 2 : 4;
                float delta = scrollEvent.delta >= 0 ? 1 : -1;
                glm::vec3 translation = camera.direction() * delta / factor;
                camera.translatePosition(translation);
                break;
            }
        }
    }

    void CameraEventHandler::handle(const KeyEvent& event) {
        if (event.key == ImGuiKey_O) {
            camera.setLookAt(glm::vec3(0));
            if (event.shift) camera.setPosition(glm::vec3(0, 2, 5));
        }
    }
} // hs