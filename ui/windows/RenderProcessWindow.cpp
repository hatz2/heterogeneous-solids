//
// Created by Alberto Elorza Rubio on 27/11/2023.
//

#include "RenderProcessWindow.h"

#include <utility>
#include <imgui.h>

namespace hs {
    void RenderProcessWindow::renderBody(const Context& context) {
        auto& profile = context.getRenderProfile();
        if (ImGui::CollapsingHeader("Background", ImGuiTreeNodeFlags_DefaultOpen)) {
            auto background = profile.getBackgroundColor();
            if (ImGui::ColorEdit4("Color", value_ptr(background))) {
                profile.setBackgroundColor(background);
            }
        }
        if (ImGui::CollapsingHeader("Lines", ImGuiTreeNodeFlags_DefaultOpen)) {
            bool showMainLines = profile.isShowMainLines();
            if (ImGui::Checkbox("Show Main Lines", &showMainLines))
                profile.setShowMainLines(showMainLines);
            ImGui::BeginDisabled(!showMainLines);
            auto mainLinesColor = profile.getMainLinesColor();
            if (ImGui::ColorEdit4("Main Lines Color", glm::value_ptr(mainLinesColor)))
                profile.setMainLinesColor(mainLinesColor);
            auto mainLinesThickness = profile.getMainLinesThickness();
            if (ImGui::DragFloat("Main Lines Thickness", &mainLinesThickness, 0.1, 0.5, 10, "%.1f")) {
                profile.setMainLinesThickness(mainLinesThickness);
            }
            ImGui::EndDisabled();

            bool showDetailedLines = profile.isShowDetailedLines();
            if (ImGui::Checkbox("Show Detailed Lines", &showDetailedLines))
                profile.setShowDetailedLines(showDetailedLines);
            ImGui::BeginDisabled(!showDetailedLines);
            auto detailedLinesColor = profile.getDetailedLinesColor();
            if (ImGui::ColorEdit4("Detailed Lines Color", glm::value_ptr(detailedLinesColor)))
                profile.setDetailedLinesColor(detailedLinesColor);
            auto detailedLinesThickness = profile.getDetailedLinesThickness();
            if (ImGui::DragFloat("Detailed Lines Thickness", &detailedLinesThickness, 0.1, 0.5, 10, "%.1f"))
                profile.setDetailedLinesThickness(detailedLinesThickness);
            ImGui::EndDisabled();

            bool showNormalField = profile.isShowNormalField();
            if (ImGui::Checkbox("Show Normal Field", &showNormalField))
                profile.setShowNormalField(showNormalField);
            ImGui::BeginDisabled(!showNormalField);
            auto normalFieldColor = profile.getNormalFieldColor();
            if (ImGui::ColorEdit4("Normal Field Color", glm::value_ptr(normalFieldColor)))
                profile.setNormalFieldColor(normalFieldColor);
            auto normalFieldThickness = profile.getNormalFieldThickness();
            if (ImGui::DragFloat("Normal Field Thickness", &normalFieldThickness, 0.1, 0.5, 10, "%.1f"))
                profile.setNormalFieldThickness(normalFieldThickness);
            ImGui::EndDisabled();
        }
        if (ImGui::CollapsingHeader("Surfaces", ImGuiTreeNodeFlags_DefaultOpen)) {
            bool showSurfaces = profile.isShowSurfaces();
            if (ImGui::Checkbox("Show Surfaces", &showSurfaces))
                profile.setShowSurfaces(showSurfaces);
            ImGui::BeginDisabled(!showSurfaces);
            ImGui::Spacing();
            int showDetailedSurfaces = profile.isDetailedSurfaces();
            bool a = ImGui::RadioButton("Main surfaces", &showDetailedSurfaces, 0);
            bool b = ImGui::RadioButton("Detailed surfaces", &showDetailedSurfaces, 1);
            if (a || b) profile.setDetailedSurfaces(showDetailedSurfaces);
            ImGui::EndDisabled();
        }
        if (ImGui::CollapsingHeader("Vertices", ImGuiTreeNodeFlags_DefaultOpen)) {
            bool showVertices = profile.isShowVertices();
            if (ImGui::Checkbox("Show Vertices", &showVertices))
                profile.setShowVertices(showVertices);
            ImGui::BeginDisabled(!showVertices);
            auto vertexColor = profile.getVertexColor();
            if (ImGui::ColorEdit4("Vertex Color", glm::value_ptr(vertexColor)))
                profile.setVertexColor(vertexColor);
            auto vertexRadius = profile.getVertexRadius();
            if (ImGui::DragFloat("Vertex Radius", &vertexRadius, 0.1, 0.5, 4, "%.1f"))
                profile.setVertexRadius(vertexRadius);
            ImGui::EndDisabled();
        }
        if (ImGui::CollapsingHeader("Selection", ImGuiTreeNodeFlags_DefaultOpen)) {
            bool highlightSelection = profile.isHighlightSelection();
            if (ImGui::Checkbox("Selection Highlight", &highlightSelection))
                profile.setHighlightSelection(highlightSelection);
            ImGui::BeginDisabled(!highlightSelection);
            bool selectionDrawDepth = profile.isSelectionDrawDepth();
            if (ImGui::Checkbox("Selection Depth Respect", &selectionDrawDepth))
                profile.setSelectionDrawDepth(selectionDrawDepth);
            auto selectionTint = profile.getSelectionTint();
            if (ImGui::ColorEdit4("Selection tint", glm::value_ptr(selectionTint)))
                profile.setSelectionTint(selectionTint);
            ImGui::EndDisabled();
        }
        if (ImGui::CollapsingHeader("Gizmos", ImGuiTreeNodeFlags_DefaultOpen)) {
            bool showGrid = profile.isShowGridGizmo();
            if (ImGui::Checkbox("Show grid", &showGrid))
                profile.setShowGridGizmo(showGrid);
            // TODO: Griz y placement
            bool showLights = profile.isShowLightsGizmo();
            if (ImGui::Checkbox("Show lights", &showLights))
                profile.setShowLightsGizmo(showLights);
        }
        if (ImGui::CollapsingHeader("PBR", ImGuiTreeNodeFlags_DefaultOpen))
        {
            bool usePbr = profile.isUsePbr();
            if (ImGui::Checkbox("Use PBR", &usePbr))
            {
                profile.setUsePbr(usePbr);
            }
        }
        if (ImGui::CollapsingHeader("Other", ImGuiTreeNodeFlags_DefaultOpen)) {
            bool antialiasing = profile.isAntialiasing();
            if (ImGui::Checkbox("Antialiasing", &antialiasing))
                profile.setAntialiasing(antialiasing);
        }
    }

    RenderProcessWindow::RenderProcessWindow(std::string title, std::shared_ptr<ContextManager> contextManager):
        ContextWindow(std::move(title), std::move(contextManager)) {

    }

} // hs