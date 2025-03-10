//
// Created by Alberto Elorza Rubio on 30/11/2023.
//

#include "TreeViewWindow.h"
#include "constants.h"
#include "../components.h"
#include "../../command/basic/UpdateDescriptionCommand.h"
#include "../../command/basic/UpdateVisibilityCommand.h"
#include "../../command/basic/MoveObjectCommand.h"

#include <imgui.h>

namespace hs {
    TreeViewWindow::TreeViewWindow(std::string name, std::shared_ptr<ContextManager> contextManager):
        ContextWindow(std::move(name), std::move(contextManager)) {

    }

    void TreeViewWindow::renderBody(const Context& context) {
        doObjectTree(context, context.getScene().getRoot());
    }

    void TreeViewWindow::doObjectTree(const Context& context, SceneNode& object) {
        auto& state = object.getState();
        bool selected = &context.getScene().getSelectedObject() == &object;

        bool open = ImGui::TreeNodeEx("treenode",
            DefaultTreeBranchFlags | (object.nodeDefaultOpen() * ImGuiTreeNodeFlags_DefaultOpen) |
                (selected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None),
            "%s %s", object.getIcon(), state.getDescriptionOrDefault().c_str()
        );
        if (ImGui::IsItemClicked()) context.getSelector().select(object);
        if (ImGui::BeginPopupContextItem("state_context")) {
            std::string description = state.getDescription();
            if (InputTextWithHint("Description", state.getDefaultDescription().c_str(), &description))
                context.getCommandHistory().execute<UpdateDescriptionCommand>(description, state);

            bool visible = state.isVisible();
            if (ImGui::Checkbox("Show Object", &visible))
                context.getCommandHistory().execute<UpdateVisibilityCommand>(visible, state);
            ImGui::EndPopup();
        }

        // Prevent cross context movements
        // TODO: update in the future to support node copy (not referencing) between contexts
        auto getPayload = [&context]() { return "TREE_MOVE_ITEM_CTX:" + std::to_string(context.getContextId()); };

        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
            auto ptr = &object;
            ImGui::SetDragDropPayload(getPayload().c_str(), &ptr, sizeof(SceneNode*));
            ImGui::Text("%s %s", object.getIcon(), state.getDescriptionOrDefault().c_str());
            ImGui::EndDragDropSource();
        }
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(getPayload().c_str())) {
                IM_ASSERT(payload->DataSize == sizeof(SceneNode*));
                auto& payloadObject = **(SceneNode**)payload->Data;
                context.getCommandHistory().execute<MoveObjectCommand>(payloadObject, object);
            }
            ImGui::EndDragDropTarget();
        }
        bool visible = state.isVisible();
        if (visibilityBadge(visible)) context.getCommandHistory().execute<UpdateVisibilityCommand>(visible, state);

        if (open) {
            for (int idx = 0; idx < object.childCount(); idx++)
                if (auto child = object.getChild(idx)) {
                    ImGui::PushID(idx);
                    doObjectTree(context, child.value());
                    ImGui::PopID();
                }
            ImGui::TreePop();
        }
    }
} // hs