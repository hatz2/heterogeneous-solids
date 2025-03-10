//
// Created by Alberto Elorza Rubio on 23/11/2023.
//

#include "CameraWindow.h"

#include <imgui.h>
#include <utility>

namespace hs {
    void CameraWindow::renderBody(const Context& context) {
        ImGui::SeparatorText("Properties");
        Camera& camera = context.getScene().getCamera();
        int mode = camera.getMode() == CameraMode::Parallel;
        if (ImGui::Combo("Camera mode", &mode, "Perspective\0Parallel\0"))
            camera.setMode(mode ? CameraMode::Parallel : CameraMode::Perspective);
        auto position = camera.getPosition();
        if (ImGui::DragFloat3("Position", value_ptr(position)))
            camera.setPosition(position);
        auto lookAt = camera.getLookAt();
        if (ImGui::DragFloat3("Look At", value_ptr(lookAt)))
            camera.setLookAt(lookAt);

        ImGui::BeginDisabled();
        auto up = camera.getUp();
        ImGui::DragFloat3("Up", value_ptr(up));
        ImGui::EndDisabled();

        ImGui::PushItemWidth(65);
        if (camera.getMode() == CameraMode::Parallel) {
            auto width = camera.getWidth();
            if (ImGui::DragFloat("Width", &width, 1, 0, 0, "%.1f"))
                camera.setWidth(width);

            ImGui::SameLine();
            auto height = camera.getHeight();
            if (ImGui::DragFloat("Height", &height, 1, 0, 0, "%.1f"))
                camera.setHeight(height);

            auto near = camera.getZNearParallel();
            if (ImGui::DragFloat("Near Plane", &near, 1, 0, 0, "%.2f"))
                camera.setZNearParallel(near);

            ImGui::SameLine();
            auto far = camera.getZFarParallel();
            if (ImGui::DragFloat("Far Plane", &far, 1, 0, 0, "%.2f"))
                camera.setZFarParallel(far);
        } else {
            auto fovY = camera.getFovY();
            if (ImGui::DragFloat("Fov Y", &fovY, 1, 0, 0, "%.2f"))
                camera.setFovY(fovY);

            auto near = camera.getZNearPerspective();
            if (ImGui::DragFloat("Near Plane", &near, 1, 0, 0, "%.2f"))
                camera.setZNearPerspective(near);

            ImGui::SameLine();
            auto far = camera.getZFarPerspective();
            if (ImGui::DragFloat("Far Plane", &far, 1, 0, 0, "%.2f"))
                camera.setZFarPerspective(far);
        }
        ImGui::PopItemWidth();
    }

    CameraWindow::CameraWindow(std::string title, const std::shared_ptr<ContextManager>& contextManager) :
        ContextWindow(std::move(title), contextManager)
    {

    }
} // hs