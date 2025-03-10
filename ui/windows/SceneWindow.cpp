//
// Created by Alberto Elorza Rubio on 13/11/2023.
//

#include "SceneWindow.h"

#include "../../shaders/ShaderError.h"

#include <imgui.h>

#include <memory>
#include <utility>
#include <optional>
#include <imgui_internal.h>
#include "ImGuizmo.h"
#include "../../command/basic/ApplyTranslationCommand.h"
#include "../../command/basic/ApplyRotationCommand.h"
#include "../../command/basic/ApplyScaleCommand.h"

namespace hs {
    SceneWindow::SceneWindow(
        std::string name,
        std::shared_ptr<Context> context,
        std::shared_ptr<ContextManager> contextManager,
        unsigned int resolution
    ) :
        ContextWindow(std::move(name), std::move(contextManager)),
        context(std::move(context)),
        sceneMultisampledFrameBuffer(FrameBuffer::getSharedFrameBuffer(resolution, resolution, true)),
        sceneOutputFrameBuffer(std::make_unique<FrameBuffer>(resolution, resolution)),
        selectColorFrameBuffer(FrameBuffer::getSharedFrameBuffer(resolution, resolution)),
        resolution(resolution)
    {

    }

    void SceneWindow::renderBody(const Context& context) {
        setFlags(context.getCommandHistory().updated() ? ImGuiWindowFlags_UnsavedDocument : ImGuiWindowFlags_None);

        if (const auto& error = context.getSceneStatus().getError(); !error.empty()) {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", error.c_str());
            ImGui::Spacing();
            if (ImGui::Button("Retry")) context.getSceneStatus().clearError();
            return;
        }

        auto& renderer = context.getRenderer();
        auto& scene = context.getScene();

        std::string error;
        sceneMultisampledFrameBuffer->begin();
        try {
            scene.getCamera().setAspect(sceneMultisampledFrameBuffer->getAspect());
            renderer.render(context.getRenderProfile(), scene);
        } catch (const ShaderError& ex) {
            error = ex.what();
            spdlog::warn("Shader Error: {}", error);
        } catch (const std::runtime_error& ex) {
            sceneMultisampledFrameBuffer->end();
            spdlog::warn("Unexpected exception: {}", error);
            throw ex;
        }
        sceneMultisampledFrameBuffer->end();

        if (!error.empty()) {
            context.getSceneStatus().setError(error);
            return;
        }
        sceneMultisampledFrameBuffer->copyTo(*sceneOutputFrameBuffer);

        auto size = ImGui::GetContentRegionAvail();
        ImVec2 uv0(0, 1);
        ImVec2 uv1(1, 0);
        if (size.x < size.y) {
            float gap = (1 - (size.x / size.y)) / 2;
            uv0.x = gap;
            uv1.x = 1 - gap;
        } else if (size.y < size.x) {
            float gap = (1 - (size.y / size.x)) / 2;
            uv0.y = 1 - gap;
            uv1.y = gap;
        }

        ImGuiIO& io = ImGui::GetIO();

        auto cursor = ImGui::GetCursorScreenPos();
        ImGui::Image(reinterpret_cast<ImTextureID>(sceneOutputFrameBuffer->getTextureId()), size, uv0, uv1);

        if (applyTransforms(context, cursor, size) ||  !ImGui::IsItemHovered()) return;

        if (ImGui::IsItemClicked(0)) {
            selectColorFrameBuffer->begin();
            try {
                auto glmVec = [](ImVec2 imguiVec) -> glm::vec2 { return { imguiVec.x, imguiVec.y }; };
                auto mousePosition = glmVec(ImGui::GetMousePos()) - glmVec(ImGui::GetItemRectMin());
                auto windowSize = glmVec(ImGui::GetItemRectSize());
                auto mouseRelative = mousePosition / windowSize;
                glm::vec2 mouseCoords { (mouseRelative.x * (uv1.x - uv0.x)) + uv0.x, (mouseRelative.y * (uv1.y - uv0.y)) + uv0.y };
                glm::vec2 mouseCoordsResolution = mouseCoords * (float)resolution;

                scene.getCamera().setAspect(selectColorFrameBuffer->getAspect());
                auto result = renderer.renderColorSelection(
                    context.getRenderProfile(), scene
                )->getResult(mouseCoordsResolution);
                if (result.has_value()) context.getEventManager().handle(SelectionEvent { result.value() });
            } catch (const ShaderError& ex) {
                error = ex.what();
                spdlog::warn("Shader Error: {}", error);
            } catch (const std::runtime_error& ex) {
                selectColorFrameBuffer->end();
                spdlog::warn("Unexpected exception: {}", error);
                throw ex;
            }
            selectColorFrameBuffer->end();
        }

        auto checkDrag = [&context, &io](ImGuiMouseButton imguiButton, MouseButton mouseButton) {
            if (ImGui::IsMouseDragging(imguiButton)) {
                auto drag = io.MouseDelta;
                context.getEventManager().handle(DragMouseEvent { drag.x, -drag.y, mouseButton, io.KeyShift });
            }
        };

        checkDrag(ImGuiMouseButton_Left, MouseButton::Left);
        checkDrag(ImGuiMouseButton_Middle, MouseButton::Middle);
        checkDrag(ImGuiMouseButton_Right, MouseButton::Right);

        ImGui::SetItemUsingMouseWheel();
        float scroll = io.MouseWheel;
        if (scroll != 0) context.getEventManager().handle(ScrollMouseEvent { scroll, io.KeyShift });

        if (!ImGui::IsWindowFocused()) return;

        for (ImGuiKey key = ImGuiKey_Keyboard_BEGIN; key < ImGuiKey_Keyboard_END; key = (ImGuiKey)(key + 1)) {
            if (!ImGui::IsKeyPressed(key)) continue;
            context.getEventManager().handle(KeyEvent {
                key,
                ImGui::GetKeyName(key),
                io.KeyShift,
                io.KeyCtrl,
                io.KeyAlt
            });
        }
    }

    void SceneWindow::renderBody() {
        if (ImGui::IsWindowFocused()) contextManager->setContext(context);

        renderBody(*context);
    }

    void SceneWindow::render() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        Window::render();
        ImGui::PopStyleVar();
    }

    bool SceneWindow::applyTransforms(const Context& context, ImVec2 drawPosition, ImVec2 drawSize) {
        auto optionalTransform = context.getSelector().getSelectedObject().getOwnedTransform();
        if (!optionalTransform) return false;
        auto& transform = optionalTransform.value().get();
        auto& scene = context.getScene();

        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(drawPosition.x, drawPosition.y, drawSize.x, drawSize.y);
        scene.getCamera().setAspect(drawSize.x/drawSize.y);

        glm::mat4 matrix = transform.matrix();
        glm::mat4 deltaMatrix{};
        ImGuizmo::OPERATION operation;

        TransformGizmo transformGizmo = context.getSceneTools().getTransformGizmo();
        switch (transformGizmo) {
            case TransformGizmo::Translation:
                operation = ImGuizmo::TRANSLATE;
                break;
            case TransformGizmo::Rotation:
                operation = ImGuizmo::ROTATE;
                break;
            case TransformGizmo::Scale:
                operation = ImGuizmo::SCALE;
                break;
        }

        glm::mat4 viewMatrix = scene.getCamera().view();

        float projectionScale = drawSize.x > drawSize.y ? drawSize.x / drawSize.y : 1;
        // TODO: fix the parallel projection for the gizmo
        glm::mat4 projectionMatrix = glm::scale(
            scene.getCamera().perspectiveProjection(),
            glm::vec3(projectionScale, projectionScale, 1)
        );

        ImGuizmo::Manipulate(
            glm::value_ptr(viewMatrix),
            glm::value_ptr(projectionMatrix),
            operation,
            ImGuizmo::WORLD,
            glm::value_ptr(matrix),
            glm::value_ptr(deltaMatrix)
        );
        if (!ImGuizmo::IsUsing()) return false;

        // Ensure transforms are done in the child space
        if (auto parent = transform.getParent()) {
            glm::mat4 parentMatrix = parent.value()->matrix();
            glm::mat4 childMatrix = transform.localMatrix();
            deltaMatrix = glm::inverse(childMatrix) * glm::inverse(parentMatrix) * matrix;
        }

        glm::vec3 translation{}, rotation{}, scale{};
        ImGuizmo::DecomposeMatrixToComponents(
            glm::value_ptr(deltaMatrix), glm::value_ptr(translation),
            glm::value_ptr(rotation), glm::value_ptr(scale)
        );
        switch (transformGizmo) {
            case TransformGizmo::Translation:
                context.getCommandHistory().execute<ApplyTranslationCommand>(transform, translation, false);
                break;
            case TransformGizmo::Rotation:
                context.getCommandHistory().execute<ApplyRotationCommand>(transform, rotation, false);
                break;
            case TransformGizmo::Scale:
                context.getCommandHistory().execute<ApplyScaleCommand>(transform, scale, false);
                break;
        }

        return true;
    }
} // hs