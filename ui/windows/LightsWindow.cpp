//
// Created by Alberto Elorza Rubio on 26/11/2023.
//

#include "LightsWindow.h"
#include "../components.h"
#include "constants.h"
#include "../core/UI.h"
#include "../dialogs/AddLightDialog.h"
#include <imgui.h>

namespace hs {
    LightsWindow::LightsWindow(std::string title, std::shared_ptr<ContextManager> contextManager, UI& ui) :
        ContextWindow(std::move(title),
        std::move(contextManager)),
        lightDialog(std::make_shared<AddLightDialog>("Add New Light", LightsWindow::contextManager))
    {
        ui.getDialogManager().addDialog(lightDialog);

        setFlags(ImGuiWindowFlags_MenuBar);
    }

    void LightsWindow::renderBody(const Context& context) {
        LightSet& lights = context.getScene().getLights();

        if (ImGui::BeginMenuBar()) {
            if (ImGui::MenuItem("Create")) {
                lightDialog->show();
            }
            ImGui::EndMenuBar();
        }

        ImGui::BeginDisabled(context.getRenderProfile().isUseIbl() && context.getRenderProfile().isUsePbr());
        bool ambientEnabled = lights.getAmbientLight().isEnabled();
        ImGui::BeginDisabled(!ambientEnabled);
        auto ambient = lights.getAmbientLight().getLightProps().getIA();
        if (ImGui::ColorEdit3("", glm::value_ptr(ambient))) {
            lights.getAmbientLight().getLightProps().setIA(ambient);
        }
        ImGui::EndDisabled();
        ImGui::SameLine();
        if (ImGui::Checkbox("Ambient light", &ambientEnabled)) {
            lights.getAmbientLight().setEnabled(ambientEnabled);
            lights.compile();
        }
        ImGui::EndDisabled();
        int item_current = !lights.getModelingLight().isEnabled();
        if (ImGui::Combo("Light Sources", &item_current, "Modeling\0Custom\0")) {
            lights.getModelingLight().setEnabled(!((bool)item_current));
            lights.compile();
        }
        ImGui::Spacing();
        switch (item_current) {
            case 0:
                ImGui::SeparatorText("Modeling light properties");
                ImGui::BeginDisabled();
                positionalLightProps(context.getScene().getLights().getModelingLight().getLightProps());
                ImGui::EndDisabled();
                ImGui::Separator();
                commonLightProps(context.getScene().getLights().getModelingLight().getLightProps(), context);
                break;
            case 1:
                customLightsTable(lights, context);
                break;
            default:
                break;
        }
        ImGui::Spacing();
        if (ImGui::CollapsingHeader("Summary")) {
            if (ImGui::TreeNodeEx("Lights", DefaultOpenTreeBranchFlags)) {
                ImGui::TreeNodeEx(
                    context.getScene().getLights().getAmbientLight().getName().c_str(),
                    DefaultTreeLeafFlags
                );
                ImGui::TreeNodeEx(
                    context.getScene().getLights().getModelingLight().getName().c_str(),
                    ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen
                );
                if (ImGui::TreeNodeEx("Custom Lights", DefaultOpenTreeBranchFlags)) {
                    for (const auto& light : context.getScene().getLights().getCustomLights()) {
                        ImGui::TreeNodeEx(
                            light.getName().c_str(),
                            DefaultTreeLeafFlags
                        );
                    }
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }
            if (ImGui::TreeNodeEx("Visible Lights", DefaultOpenTreeBranchFlags)) {
                for (const auto& light : context.getScene().getLights()) {
                    ImGui::TreeNodeEx(
                        light.get().getName().c_str(),
                        DefaultTreeLeafFlags
                    );
                }
                ImGui::TreePop();
            }
        }
    }

    void LightsWindow::commonLightProps(LightProps& lightProps, const Context& context) {
        auto diffuse = lightProps.getID();
        if (ImGui::ColorEdit3("Diffuse", glm::value_ptr(diffuse)))
            lightProps.setID(diffuse);

        ImGui::BeginDisabled(context.getRenderProfile().isUsePbr());
        auto specular = lightProps.getIS();
        if (ImGui::ColorEdit3("Specular", glm::value_ptr(specular)))
            lightProps.setIS(specular);
        ImGui::EndDisabled();

        ImGui::PushItemWidth(65);
        float gamma = lightProps.getGamma();
        if (ImGui::SliderAngle("Gamma", &gamma, 0, 90))
            lightProps.setGamma(gamma);
    }

    void LightsWindow::positionalLightProps(LightProps& lightProps) {
        auto position = lightProps.getPosition();
        if (ImGui::DragFloat3("Position", value_ptr(position)))
            lightProps.setPosition(position);

        auto lookAt = lightProps.getLookAt();
        if (ImGui::DragFloat3("Look At", value_ptr(lookAt)))
            lightProps.setLookAt(lookAt);
    }

    void LightsWindow::customLightsTable(LightSet& lights, const Context& context) {
        ImGui::SeparatorText("Custom lights settings");
        static ImGuiTableFlags flags = ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Resizable;
        const int selectedLightId = lights.getEditingLight();
        if (ImGui::BeginTable("Lights Table", 3, flags)) {
            ImGui::TableSetupColumn("On", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();
            auto& customLights = lights.getCustomLights();
            for (auto it = customLights.begin(); it < customLights.end(); it++) {
                int id = (int)std::distance(customLights.begin(), it);
                ImGui::PushID(id);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                bool on = it->isEnabled();
                if (ImGui::Checkbox("##on", &on)) {
                    it->setEnabled(on);
                    lights.compile();
                }
                ImGui::TableNextColumn();
                ImGui::Text("%s", it->getName().c_str());
                ImGui::TableNextColumn();
                LightType lightType = it->getLightType();
                if (lightTypeCombo("##type", lightType)) {
                    it->setLightType(lightType);
                }
                ImGui::SameLine();
                if (ImGui::Selectable(
                    "##select",
                    id == selectedLightId,
                    ImGuiSelectableFlags_SpanAllColumns
                )) {
                    lights.setEditingLight(id);
                }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
        if (selectedLightId >= 0) {
            auto& light = lights.getCustomLights()[selectedLightId];
            ImGui::SeparatorText((light.getName() + " properties").c_str());
            std::string name = light.getName();
            if (InputText("Name", &name)) light.setName(name);
            ImGui::Separator();
            positionalLightProps(light.getLightProps());
            ImGui::Separator();
            commonLightProps(light.getLightProps(), context);
            ImGui::Separator();
            if (ImGui::Button("Clone Light")) {
                lights.getCustomLights().push_back(light);
                lights.compile();
            }
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0, 0.6f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0, 0.7f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0, 0.8f, 0.8f));
            bool doDelete = ImGui::Button("Delete Light");
            ImGui::PopStyleColor(3);
            if (doDelete) {
                lights.removeEditingLight();
                lights.compile();
                return;
            }
        }
    }
} // hs