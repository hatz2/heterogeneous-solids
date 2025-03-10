//
// Created by Alberto Elorza Rubio on 08/12/2023.
//

#include "ObjectWindow.h"

#include "../components.h"
#include "../../heterogeneous_solids/HeterogeneousSolid.h"
#include "../../command/basic/UpdateDescriptionCommand.h"
#include "../../command/basic/UpdateVisibilityCommand.h"

#include <utility>

namespace hs {
    ObjectWindow::ObjectWindow(std::string title, std::shared_ptr<ContextManager> contextManager) :
        ContextWindow(std::move(title), std::move(contextManager))
    {

    }

    void ObjectWindow::renderBody(const Context& context) {
        if (auto heterogeneousSolid = context.getSelector().getHeterogeneousSolid()) {
            renderHeader(context, heterogeneousSolid->get().getState());
            renderHeterogeneousSolid(context, *heterogeneousSolid);
            renderTree(context, *heterogeneousSolid);
        } else if (auto group = context.getSelector().getGroupNode()) {
            renderHeader(context, group->get().getState());
            renderTree(context, *group);
        }
    }

    void ObjectWindow::renderTree(const Context& context, SceneNode& object) {
        ImGui::Spacing();
        ImGui::SeparatorText("Tree");
        if (auto parent = object.getParent()) {
            if (ImGui::Button("Select Parent"))
                context.getSelector().select(parent.value());
        }
        auto childCount = object.childCount();
        auto size = ImGui::GetContentRegionAvail();
        auto minHeight = 10 * ImGui::GetTextLineHeight();
        if (size.y < minHeight) size.y = minHeight;
        if (childCount > 0 && ImGui::BeginListBox("##children", size)) {
            for (int i = 0; i < childCount; i++) {
                auto child = object.getChild(i);
                ImGui::PushID(i);
                if (ImGui::Selectable(child->get().getState().getDescriptionOrDefault().c_str()))
                    context.getSelector().select(child.value());
                ImGui::PopID();
            }
            ImGui::EndListBox();
        }
    }

    void ObjectWindow::renderHeader(const Context& context, SceneNodeState& state) {
        std::string description = state.getDescription();
        if (InputTextWithHint("Description", state.getDefaultDescription().c_str(), &description))
            context.getCommandHistory().execute<UpdateDescriptionCommand>(description, state);

        bool visible = state.isVisible();
        if (ImGui::Checkbox("Show Object", &visible))
            context.getCommandHistory().execute<UpdateVisibilityCommand>(visible, state);
    }

    void ObjectWindow::renderHeterogeneousSolid(const Context& context, HeterogeneousSolid& heterogeneousSolid) {
        ImGui::SeparatorText("Heterogeneous Solid properties");
        auto activeMaterial = heterogeneousSolid.getMaterial();
        if (ImGui::BeginCombo(
            "Material", activeMaterial->getDescriptionProp().getDescriptionOrDefault().c_str())
            ) {
            int idx = 0;
            for (const auto& material : context.getMaterialEditor().getHeterogeneousMaterials()) {
                ImGui::PushID(idx++);
                auto selected = activeMaterial == material;
                if (ImGui::Selectable(material->getDescriptionProp().getDescriptionOrDefault().c_str(), selected))
                    heterogeneousSolid.setMaterial(material);
                ImGui::PopID();
            }
            ImGui::EndCombo();
        }
        int resolution = (int)heterogeneousSolid.getSharedData()->getBezierResolution();
        if (ImGui::InputInt("Bezier Resolution", &resolution)) {
            heterogeneousSolid.getSharedData()->setBezierResolution((float)resolution);
            heterogeneousSolid.needRecalculation(true, true);
        }
    }
} // hs