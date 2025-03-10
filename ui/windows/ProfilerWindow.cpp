//
// Created by Alberto Elorza Rubio on 11/01/2024.
//

#include "ProfilerWindow.h"

#include <utility>

namespace hs {
    ProfilerWindow::ProfilerWindow(std::string name) : Window(std::move(name)), frameRateHistory(), history_offset() {

    }

    void ProfilerWindow::render() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        Window::render();
        ImGui::PopStyleVar();
    }

    void ProfilerWindow::renderBody() {
        auto framerate = ImGui::GetIO().Framerate;
        std::string overlay = "Framerate: " + std::to_string((int)framerate);
        frameRateHistory[history_offset] = framerate;
        history_offset = (history_offset + 1) % (int)frameRateHistory.size();
        ImGui::PlotLines(
            "##framerate",
            frameRateHistory.data(),
            (int)frameRateHistory.size(),
            history_offset,
            overlay.c_str(),
            FLT_MIN,
            FLT_MAX,
            ImVec2(-FLT_MIN, ImGui::GetContentRegionAvail().y)
        );
    }
} // hs