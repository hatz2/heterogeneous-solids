//
// Created by Alberto Elorza Rubio on 15/02/2024.
//

#include "TransformWindow.h"
#include "../../command/basic/ApplyTranslationCommand.h"
#include "../../command/basic/ApplyRotationCommand.h"
#include "../../command/basic/ApplyScaleCommand.h"

namespace hs {
    TransformWindow::TransformWindow(std::string title, std::shared_ptr<ContextManager> contextManager) :
        ContextWindow(std::move(title), std::move(contextManager))
    {

    }

    void TransformWindow::renderBody(const Context& context) {
        auto& sceneTools = context.getSceneTools();
        ImVec4 colorOrig = ImGui::GetStyleColorVec4(ImGuiCol_Button);
        ImVec4 noColor = ImVec4(0, 0, 0, 0);
        ImVec4 eachColor[3] = {
            sceneTools.getTransformGizmo() == TransformGizmo::Translation ? colorOrig : noColor,
            sceneTools.getTransformGizmo() == TransformGizmo::Rotation ? colorOrig : noColor,
            sceneTools.getTransformGizmo() == TransformGizmo::Scale ? colorOrig : noColor,
        };

        ImGui::PushStyleColor(ImGuiCol_Button, eachColor[0]);
        if (ImGui::Button(ICON_MD_CONTROL_CAMERA)) sceneTools.setTransformGizmo(TransformGizmo::Translation);
        ImGui::PopStyleColor();

        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, eachColor[1]);
        if (ImGui::Button(ICON_MD_LOOP)) sceneTools.setTransformGizmo(TransformGizmo::Rotation);
        ImGui::PopStyleColor();

        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, eachColor[2]);
        if (ImGui::Button(ICON_MD_ASPECT_RATIO)) sceneTools.setTransformGizmo(TransformGizmo::Scale);
        ImGui::PopStyleColor();

        ImGui::Separator();
        if (auto selectionTransform = context.getSelector().getSelectedObject().getOwnedTransform()) {
            auto& transform = selectionTransform->get();
            glm::vec3 translation = transform.getTranslation();
            if (ImGui::DragFloat3("Position", glm::value_ptr(translation)))
                context.getCommandHistory().execute<ApplyTranslationCommand>(transform, translation, true);

            glm::vec3 rotation = transform.getRotation();
            if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation)))
                context.getCommandHistory().execute<ApplyRotationCommand>(transform, rotation, true);

            glm::vec3 scale = transform.getScale();
            if (ImGui::DragFloat3("Scale", glm::value_ptr(scale)))
                context.getCommandHistory().execute<ApplyScaleCommand>(transform, scale, true);
        }
    }
} // hs