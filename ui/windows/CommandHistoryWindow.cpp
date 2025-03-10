//
// Created by Alberto Elorza Rubio on 25/12/2023.
//

#include "CommandHistoryWindow.h"
#include "../../command/examples/SampleCommandProp.h"
#include "../../bindings/IconsMaterialDesign.h"

#include <imgui.h>

namespace hs {
    CommandHistoryWindow::CommandHistoryWindow(std::string title, std::shared_ptr<ContextManager> contextManager) :
        ContextWindow(std::move(title), std::move(contextManager))
    {
        setFlags(ImGuiWindowFlags_MenuBar);
    }

    void CommandHistoryWindow::render() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        Window::render();
        ImGui::PopStyleVar();
    }

    void CommandHistoryWindow::renderBody(const Context& context) {
        auto& commandHistory = context.getCommandHistory();
        if (ImGui::BeginMenuBar()) {
            ImGui::BeginDisabled(!commandHistory.canUndo());
            if (ImGui::MenuItem(ICON_MD_UNDO)) {
                commandHistory.undo();
            }
            ImGui::SetItemTooltip("Undo one command");
            ImGui::EndDisabled();
            ImGui::BeginDisabled(!commandHistory.canRedo());
            if (ImGui::MenuItem(ICON_MD_REDO)) {
                commandHistory.redo();
            }
            ImGui::SetItemTooltip("Redo one command");
            ImGui::EndDisabled();
            ImGui::BeginDisabled(commandHistory.empty());
            if (ImGui::MenuItem(ICON_MD_CLEAR)) {
                commandHistory.clear();
            }
            ImGui::SetItemTooltip("Clear command history");
            ImGui::EndDisabled();
            ImGui::EndMenuBar();
        }
        if (ImGui::BeginListBox(
            "##Commands", ImVec2(-1, -1)
        )) {
            auto rBegin = std::reverse_iterator(commandHistory.end());
            auto rDone = std::reverse_iterator(commandHistory.done());
            auto rEnd = std::reverse_iterator(commandHistory.begin());
            ImGui::BeginDisabled();
            for (; rBegin != rDone; rBegin++) {
                ImGui::Text("%s", rBegin->get()->getDescription().c_str());
                ImGui::Spacing();
            }
            ImGui::EndDisabled();
            for (; rBegin != rEnd; rBegin++) {
                ImGui::Text("%s", rBegin->get()->getDescription().c_str());
                ImGui::Spacing();
            }
            ImGui::EndListBox();
        }
    }
} // hs