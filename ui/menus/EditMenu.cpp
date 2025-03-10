//
// Created by Alberto Elorza Rubio on 01/02/2024.
//

#include "EditMenu.h"
#include "../../bindings/IconsMaterialDesign.h"

namespace hs {
    EditMenu::EditMenu(std::shared_ptr<ContextManager> manager) : ContextMenuNode(manager) {

    }

    void EditMenu::renderMenuNode(const Context& context) {
        if (ImGui::BeginMenu("Edit")) {
            auto& commandHistory = context.getCommandHistory();
            ImGui::BeginDisabled(!commandHistory.canUndo());
            if (ImGui::MenuItem(ICON_MD_UNDO " Undo"))
                commandHistory.undo();
            ImGui::EndDisabled();
            ImGui::BeginDisabled(!commandHistory.canRedo());
            if (ImGui::MenuItem(ICON_MD_REDO " Redo"))
                commandHistory.redo();
            ImGui::EndDisabled();
            ImGui::Separator();
            ImGui::BeginDisabled(commandHistory.empty());
            if (ImGui::MenuItem(ICON_MD_CLEAR " Clear History"))
                commandHistory.clear();
            ImGui::EndDisabled();
            ImGui::EndMenu();
        }
    }
} // hs