//
// Created by Alberto Elorza Rubio on 24/01/2024.
//

#include "ShadersWindow.h"
#include "../components.h"

#include <spdlog/spdlog.h>

namespace hs {
    ShadersWindow::ShadersWindow(std::string name, ShaderManager& shaderManager) :
        Window(std::move(name)), shaderManager(shaderManager), height(100), count(0), remain(0)
    {
        setFlags(ImGuiWindowFlags_MenuBar);
    }

    void ShadersWindow::renderBody() {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu(("Select Shader (" + selected.value_or("None Selected") + ")##select").c_str())) {
                for (auto const& item : shaderManager.getShaderPrograms()) {
                    if (ImGui::MenuItem(item.c_str())) {
                        selected = item;
                        sources = shaderManager.getShaderSources(item);
                    }
                }
                ImGui::EndMenu();
            }
            if (selected) {
                ImGui::Separator();
                if (sources && ImGui::MenuItem("Update Changes")) {
                    shaderManager.updateProgramSources(selected.value(), sources.value());
                }
                if (ImGui::MenuItem("Discard Changes")) {
                    sources = shaderManager.getShaderSources(selected.value());
                }
            }
            ImGui::EndMenuBar();
        }

        if (!sources) return;

        if (std::abs(remain) > 1. + count)
            height += (remain / (float)(count == 0 ? 1 : count));
        count = 0;

        if (ImGui::CollapsingHeader("Vertex")) {
            ImGui::PushID("vertex");
            renderShaderType(sources->vertexSources);
            ImGui::PopID();
        }

        if (ImGui::CollapsingHeader("Fragment")) {
            ImGui::PushID("fragment");
            renderShaderType(sources->fragmentSources);
            ImGui::PopID();
        }

        if (ImGui::CollapsingHeader("Geometry")) {
            ImGui::PushID("geometry");
            renderShaderType(sources->geometrySources);
            ImGui::PopID();
        }

        remain = ImGui::GetContentRegionAvail().y;
    }

    void ShadersWindow::renderShaderType(std::vector<ShaderSource>& sources) {
        if (!sources.empty() && ImGui::BeginTabBar("sources")) {
            count++;
            for (auto& source : sources) {
                if (ImGui::BeginTabItem(source.origin.c_str())) {
                    InputTextMultiline("##source", &source.content, ImVec2(-FLT_MIN, height));
                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }
    }
} // hs