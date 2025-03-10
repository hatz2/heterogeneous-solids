//
// Created by Alberto Elorza Rubio on 28/12/2023.
//

#include "SnapshotWindow.h"

#include <imgui.h>
#include <filesystem>

#ifdef _WIN32
#define SEPARATOR "\\"
#else
#define SEPARATOR "/"
#endif

namespace hs {
    SnapshotWindow::SnapshotWindow(std::string title, std::shared_ptr<ContextManager> contextManager) :
        ContextWindow(std::move(title), std::move(contextManager))
    {

    }

    void SnapshotWindow::renderBody(const Context& context) {
        auto& snapshot = context.getSnapshot();

        if (ImGui::BeginCombo("Resolution", snapshot.getResolution().name.c_str())) {
            for (const auto& resolution : defaultResolutions) {
                const bool isSelected = context.getSnapshot().getResolution().name == resolution.name;
                if (ImGui::Selectable(resolution.name.c_str(), isSelected))
                    snapshot.setResolution(resolution);
                ImGui::SetItemTooltip("%d x %d", resolution.width, resolution.height);
                if (isSelected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        auto resolution = snapshot.getResolution();
        ImGui::SetItemTooltip("%d x %d", resolution.width, resolution.height);

        ImGui::Spacing();

        if (ImGui::RadioButton("Store at directory", snapshot.getMode() == SnapshotMode::Folder))
            snapshot.setSnapshotMode(SnapshotMode::Folder);
        ImGui::SameLine();
        if (ImGui::RadioButton("Request output file", snapshot.getMode() == SnapshotMode::AskFile))
            snapshot.setSnapshotMode(SnapshotMode::AskFile);

        ImGui::Spacing();

        ImGui::BeginDisabled(snapshot.getMode() != SnapshotMode::Folder);
        if (ImGui::Button("Select Directory"))
            snapshot.requestOutputFolder();
        ImGui::SameLine();
        auto counter = (int)snapshot.getCounter();
        std::string output = snapshot.getOutputFolder().empty()
            ? FOLDER_SNAPSHOT_FILE_PREFIX "%d.png"
            : snapshot.getOutputFolder() + SEPARATOR FOLDER_SNAPSHOT_FILE_PREFIX "%d.png";
        ImGui::SetNextItemWidth(-FLT_MIN);
        if (ImGui::DragInt(
            "##counter", &counter, 0.5f, 0, INT_MAX, output.c_str(), ImGuiSliderFlags_AlwaysClamp
        ))
            snapshot.setCounter(counter);
        ImGui::EndDisabled();

        ImGui::Spacing();

        if (ImGui::Button("Save Snapshot"))
            snapshot.takeSnapshot(context.getRenderProfile(), context.getScene());
    }
} // hs