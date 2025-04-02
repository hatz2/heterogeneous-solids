//
// Created by Alberto Elorza Rubio on 18/01/2024.
//

#include "MaterialsWindow.h"
#include "../components.h"
#include "../../command/basic/UpdateDescriptionCommand.h"

#include <imgui.h>

namespace hs {
    MaterialsWindow::MaterialsWindow(std::string title, std::shared_ptr<ContextManager> contextManager) :
        ContextWindow(std::move(title), std::move(contextManager))
    {
        setFlags(ImGuiWindowFlags_MenuBar);
    }

    void MaterialsWindow::renderBody(const Context& context) {
        auto& materialEditor = context.getMaterialEditor();

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("New")) {
                if (ImGui::MenuItem("Material")) {
                    auto material = std::make_shared<Material>();
                    materialEditor.setSelected(material);
                    materialEditor.getMaterials().insert(material);
                }
                if (ImGui::MenuItem("Heterogeneous Material")) {
                    auto heterogeneousMaterial = std::make_shared<HeterogeneousMaterial>();
                    materialEditor.setSelected(heterogeneousMaterial);
                    materialEditor.getMaterials().insert(heterogeneousMaterial->getPrimaryMaterial());
                    materialEditor.getMaterials().insert(heterogeneousMaterial->getSecondaryMaterial());
                    materialEditor.getHeterogeneousMaterials().insert(heterogeneousMaterial);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Delete")) {
                if (ImGui::MenuItem("Unused Materials"))
                    materialEditor.getMaterials().erase_if([](auto& material) {
                        return material.use_count() <= 1;
                    });
                if (ImGui::MenuItem("Unused Heterogeneous Materials"))
                    materialEditor.getHeterogeneousMaterials().erase_if([](auto& material) {
                        return material.use_count() <= 1;
                    });
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        const char* noSelection = "No selection";
        auto optMaterial = materialEditor.getSelected();
        auto getDescription = [](
            std::variant<std::shared_ptr<Material>, std::shared_ptr<HeterogeneousMaterial>>& mat
        ) {
            switch (mat.index()) {
                case 0:
                    return "(Simple) " + std::get<0>(mat)->getDescriptionProp().getDescriptionOrDefault();
                case 1:
                    return "(Heterogeneous) " + std::get<1>(mat)->getDescriptionProp().getDescriptionOrDefault();
            }
            return std::string();
        };
        if (ImGui::BeginCombo(
            "Material", optMaterial.has_value() ? getDescription(optMaterial.value()).c_str() : noSelection)
        ) {
            if (ImGui::Selectable(noSelection, !optMaterial.has_value()))
                materialEditor.unselect();
            int idx = 0;
            for (const auto& material : materialEditor.getHeterogeneousMaterials()) {
                ImGui::PushID(idx++);
                if (ImGui::Selectable(
                    ("(Heterogeneous) " + material->getDescriptionProp().getDescriptionOrDefault()).c_str(), false
                ))
                    materialEditor.setSelected(material);
                ImGui::PopID();
            }
            for (auto material : materialEditor.getMaterials()) {
                ImGui::PushID(idx++);
                if (ImGui::Selectable(
                    ("(Simple) " + material->getDescriptionProp().getDescriptionOrDefault()).c_str(), false
                ))
                    materialEditor.setSelected(material);
                ImGui::PopID();
            }
            ImGui::EndCombo();
        }
        if (optMaterial) {
            auto& material = optMaterial.value();
            switch (material.index()) {
                case 0:
                    renderMaterial(context, *std::get<0>(material));
                    break;
                case 1:
                    renderHeterogeneousMaterial(context, *std::get<1>(material));
                    break;
            }
        }
    }

    void MaterialsWindow::renderHeterogeneousMaterial(const Context& context, HeterogeneousMaterial& hsMaterial) {
        auto& materialEditor = context.getMaterialEditor();
        auto& state = hsMaterial.getDescriptionProp();

        ImGui::Spacing();
        ImGui::Separator();
        std::string description = state.getDescription();
        if (InputTextWithHint(
            "Description", state.getDefaultDescription().c_str(), &description
        )) state.setDescription(description);

        ImGui::Spacing();
        if (ImGui::CollapsingHeader("Properties: Heterogeneous Behave", ImGuiTreeNodeFlags_DefaultOpen)) {
            int materialType = (int)hsMaterial.getType();
            if (ImGui::Combo(
                "Type", &materialType, "Primary\0Secondary\0Continuous\0Functionally Graded\0Composite\0"
            )) hsMaterial.setType((MaterialType)materialType);
            if (hsMaterial.getType() == MaterialType::FunctionallyGraded) {
                ImGui::SeparatorText("Properties");
                bool usingCorrectedPerlin = hsMaterial.isUsingCorrectedPerlin();
                if (ImGui::Checkbox("Using Corrected Perlin", &usingCorrectedPerlin)) {
                    hsMaterial.setUsingCorrectedPerlin(usingCorrectedPerlin);
                }
            } else if (hsMaterial.getType() == MaterialType::Composite) {
                ImGui::SeparatorText("Properties");
                glm::vec2 range = hsMaterial.getValueRange();
                if (ImGui::DragFloat2("Range", glm::value_ptr(range))) {
                    hsMaterial.setValueRange(range);
                }
                glm::vec4 coefs = hsMaterial.getCoefs();
                if (ImGui::DragFloat4("Coefficients", glm::value_ptr(coefs))) {
                    hsMaterial.setCoefs(coefs);
                }
                if (ImGui::CollapsingHeader("Feature Point Set")) {
                    auto& featurePoints = hsMaterial.getFeaturePoints();
                    int pointCount = (int) featurePoints.size();
                    if (ImGui::DragInt("Point Count", &pointCount, 0.2f, 1, 10, "%d Points",
                                       ImGuiSliderFlags_AlwaysClamp)) {
                        hsMaterial.getFeaturePoints().resize(pointCount);
                    }
                    for (int i = 0; i < featurePoints.size(); i++) {
                        ImGui::DragFloat3(("Point:" + std::to_string(i + 1)).c_str(),
                                          glm::value_ptr(featurePoints[i]));
                    }
                }
            }
        }
        if (ImGui::CollapsingHeader("Properties: Primary", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::PushID("Primary");
            pickMaterial(materialEditor, hsMaterial, true);
            ImGui::Spacing();
            materialsProperties(context, *hsMaterial.getPrimaryMaterial());
            ImGui::PopID();
        }
        if (ImGui::CollapsingHeader("Properties: Secondary", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::PushID("Secondary");
            pickMaterial(materialEditor, hsMaterial, false);
            ImGui::Spacing();
            materialsProperties(context, *hsMaterial.getSecondaryMaterial());
            ImGui::PopID();
        }
    }

    void MaterialsWindow::renderMaterial(const Context& context, Material& material) {
        auto& state = material.getDescriptionProp();

        ImGui::Spacing();
        ImGui::Separator();
        std::string description = state.getDescription();
        if (InputTextWithHint(
            "Description", state.getDefaultDescription().c_str(), &description
        )) state.setDescription(description);

        ImGui::Spacing();
        if (ImGui::CollapsingHeader("Properties", ImGuiTreeNodeFlags_DefaultOpen)) materialsProperties(context, material);
    }

    void MaterialsWindow::materialsProperties(const Context& context, Material& material) {
        const RenderProfile& profile = context.getRenderProfile();

        glm::vec3 ka = material.getKA();
        if (ImGui::ColorEdit3("Ambient Color", glm::value_ptr(ka)))
            material.setKA(ka);

        glm::vec3 kd = material.getKD();
        if (ImGui::ColorEdit3("Diffuse Color", glm::value_ptr(kd)))
            material.setKD(kd);

        glm::vec3 ks = material.getKS();
        ImGui::BeginDisabled(profile.isUsePbr());
        if (ImGui::ColorEdit3("Specular Color", glm::value_ptr(ks)))
            material.setKS(ks);
        ImGui::EndDisabled();

        float shininess = material.getShininess();
        ImGui::BeginDisabled(profile.isUsePbr());
        if (ImGui::DragFloat("Shininess", &shininess, 0.1, 0, 128, "%.2f", ImGuiSliderFlags_AlwaysClamp))
            material.setShininess(shininess);
        ImGui::EndDisabled();

        float roughness = material.getRoughness();
        ImGui::BeginDisabled(!profile.isUsePbr());
        if (ImGui::DragFloat("Roughness", &roughness, 0.01, 0, 1, "%.2f", ImGuiSliderFlags_AlwaysClamp))
            material.setRoughness(roughness);
        ImGui::EndDisabled();

        float metallic = material.getMetallic();
        ImGui::BeginDisabled(!profile.isUsePbr());
        if (ImGui::DragFloat("Metallic", &metallic, 0.01, 0, 1, "%.2f", ImGuiSliderFlags_AlwaysClamp))
            material.setMetallic(metallic);
        ImGui::EndDisabled();
    }

    void MaterialsWindow::pickMaterial(MaterialEditor& materialEditor, HeterogeneousMaterial& hsMaterial, bool primary) {
        auto activeMaterial = primary ? hsMaterial.getPrimaryMaterial() : hsMaterial.getSecondaryMaterial();
        if (ImGui::BeginCombo(
            "Material", activeMaterial->getDescriptionProp().getDescriptionOrDefault().c_str())
        ) {
            int idx = 0;
            for (const auto& material : materialEditor.getMaterials()) {
                ImGui::PushID(idx++);
                auto selected = activeMaterial == material;
                if (ImGui::Selectable(material->getDescriptionProp().getDescriptionOrDefault().c_str(), selected)) {
                    if (primary) hsMaterial.setPrimaryMaterial(material);
                    else hsMaterial.setSecondaryMaterial(material);
                }
                ImGui::PopID();
            }
            ImGui::EndCombo();
        }
    }
} // 