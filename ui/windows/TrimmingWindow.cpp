//
// Created by Alberto Elorza Rubio on 29/01/2024.
//

#include "TrimmingWindow.h"
#include "../../command/basic/ChangeMachiningParamCommand.h"
#include "../../command/basic/ChangeMachiningProcessCommand.h"
#include "../../command/basic/SetTrimmingNodeCommand.h"
#include "../components.h"
#include "../../command/basic/CommandGroup.h"
#include "../../command/basic/InsertItemCommand.h"
#include "../../command/basic/SwapTrimmingNodeContentCommand.h"
#include "../../command/basic/UpdateDescriptionCommand.h"
#include "../../command/basic/UpdateVisibilityCommand.h"

#include <utility>

namespace hs {
    TrimmingWindow::TrimmingWindow(std::string title, std::shared_ptr<ContextManager> contextManager) :
        ContextWindow(std::move(title), std::move(contextManager))
    {
        setFlags(ImGuiWindowFlags_MenuBar);
    }

    void TrimmingWindow::renderBody(const Context& context) {
        auto& selector = context.getSelector();
        if (auto trimmedCell = selector.getTrimmedCell())
            renderTrimmedCell(context, trimmedCell.value());
    }

    void TrimmingWindow::renderMenu(const Context& context, TrimmedCell& trimmedCell) {
        if (!ImGui::BeginMenuBar()) return;
        if (ImGui::BeginMenu("Node")) {
            if (ImGui::MenuItem(ICON_MD_MOVE_UP " Move into macro")) {
                std::vector<std::unique_ptr<Command>> steps;
                auto activeNode = trimmedCell.getActiveNode();
                auto macro = std::make_shared<TrimmingNode>(*activeNode);
                steps.push_back(std::make_unique<InsertItemCommand<TrimmingNode>>(macro, context.getMacroSet()));
                steps.push_back(std::make_unique<SwapTrimmingNodeContentCommand>(
                    activeNode, std::make_shared<TrimmingNode>())
                );
                steps.push_back(std::make_unique<SetTrimmingNodeCommand>(trimmedCell, macro));
                context.getCommandHistory().execute<CommandGroup>("Create Macro (Moving)", std::move(steps));
            }
            ImGui::SetItemTooltip("The current node will be moved into a new macro, leaving it empty");
            if (ImGui::MenuItem(ICON_MD_FORK_LEFT " Fork into macro")) {
                std::vector<std::unique_ptr<Command>> steps;
                auto macro = std::make_shared<TrimmingNode>(*trimmedCell.getActiveNode());
                steps.push_back(std::make_unique<InsertItemCommand<TrimmingNode>>(macro, context.getMacroSet()));
                steps.push_back(std::make_unique<SetTrimmingNodeCommand>(trimmedCell, macro));
                context.getCommandHistory().execute<CommandGroup>("Create Macro (Forking)", std::move(steps));
            }
            ImGui::SetItemTooltip("The current node will be copied into a new macro");
            if (!trimmedCell.usingCanonicalNode()) {
                ImGui::Separator();
                if (ImGui::MenuItem(ICON_MD_EXPAND " Unwrap")) {
                    std::vector<std::unique_ptr<Command>> steps;
                    auto activeNode = trimmedCell.getActiveNode();
                    auto macro = std::make_shared<TrimmingNode>(*activeNode);
                    steps.push_back(std::make_unique<SwapTrimmingNodeContentCommand>(
                        trimmedCell.getCanonicalNode(), macro)
                    );
                    steps.push_back(std::make_unique<SetTrimmingNodeCommand>(trimmedCell, trimmedCell.getCanonicalNode()));
                    context.getCommandHistory().execute<CommandGroup>("Unwrap Macro", std::move(steps));
                }
                ImGui::SetItemTooltip("Copy the macro into the canonical node");
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    void TrimmingWindow::renderTrimmedCell(const Context& context, TrimmedCell& trimmedCell) {
        renderMenu(context, trimmedCell);
        const char* noMacro = "[Canonical Node]";
        ImGui::SetNextItemWidth(-FLT_MIN);
        if (ImGui::BeginCombo(
            "##node",
            trimmedCell.usingCanonicalNode()
            ? noMacro : ("[MACRO] " + trimmedCell.getActiveNode()->getState().getDescription()).c_str()
        )) {
            int idx = 0;
            ImGui::PushID(idx++);
            if (ImGui::Selectable(noMacro, trimmedCell.usingCanonicalNode()))
                context.getCommandHistory().execute<SetTrimmingNodeCommand>(
                    trimmedCell, trimmedCell.getCanonicalNode()
                );
            ImGui::PopID();
            if (trimmedCell.usingCanonicalNode()) ImGui::SetItemDefaultFocus();
            for (const auto& macro : context.getMacroSet()) {
                ImGui::PushID(idx++);
                const bool isSelected = trimmedCell.getActiveNode() == macro;
                if (ImGui::Selectable(("[MACRO] " + macro->getState().getDescription()).c_str(), isSelected))
                    context.getCommandHistory().execute<SetTrimmingNodeCommand>(
                        trimmedCell, macro
                    );
                if (isSelected) ImGui::SetItemDefaultFocus();
                ImGui::PopID();
            }
            ImGui::EndCombo();
        }

        auto& state = trimmedCell.getState();
        std::string description = state.getDescription();
        if (InputTextWithHint("Description", state.getDefaultDescription().c_str(), &description))
            context.getCommandHistory().execute<UpdateDescriptionCommand>(description, state);

        bool visible = state.isVisible();
        if (ImGui::Checkbox("Show Object", &visible))
            context.getCommandHistory().execute<UpdateVisibilityCommand>(visible, state);

        ImGui::Spacing();
        ImGui::SeparatorText("Machining Operation");
        auto node = trimmedCell.getActiveNode();
        auto& machiningProcess = node->getOperation().getMachiningProcess();
        if (ImGui::BeginCombo("Machining Process", machiningProcess.name())) {
            for (auto& process : MachiningOperation::processes) {
                const bool isSelected = process->name() == machiningProcess.name();
                if (ImGui::Selectable(process->name(), isSelected)) {
                    context.getCommandHistory().execute<ChangeMachiningProcessCommand>(node, *process);
                }
                if (isSelected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        for (const auto& [key, _] : machiningProcess.defaultParams()) {
            auto& param = node->getOperation().getMachiningParams().at(key);
            switch (param.index()) {
                case 0: {
                    auto& floatParam = std::get<0>(param);
                    float value = param;
                    if (ImGui::DragFloat(
                        key.c_str(),
                        &value,
                        floatParam.step,
                        floatParam.min,
                        floatParam.max,
                        "%.3f",
                        ImGuiSliderFlags_AlwaysClamp
                    )) context.getCommandHistory().execute<ChangeMachiningParamCommand>(node, key, value);
                    break;
                }
                case 1: {
                    auto& intParam = std::get<1>(param);
                    int value = param;
                    if (ImGui::DragInt(
                        key.c_str(),
                        &value,
                        (float)intParam.step,
                        intParam.min,
                        intParam.max,
                        "%d",
                        ImGuiSliderFlags_AlwaysClamp
                    )) context.getCommandHistory().execute<ChangeMachiningParamCommand>(node, key, (float)value);
                    break;
                }
                case 2: {
                    auto& enumParam = std::get<2>(param);
                    int value = param;
                    if (
                        ImGui::Combo(key.c_str(), &value, &enumParam.options[0], enumParam.options.size())
                        ) context.getCommandHistory().execute<ChangeMachiningParamCommand>(node, key, (float)value);
                    break;
                }
            }
        }
        ImGui::SeparatorText("Tree");
        if (auto parent = trimmedCell.getParent()) {
            if (ImGui::Button("Select Parent"))
                context.getSelector().select(parent.value());
        }
        auto childCount = trimmedCell.childCount();
        auto size = ImGui::GetContentRegionAvail();
        auto minHeight = 10 * ImGui::GetTextLineHeight();
        if (size.y < minHeight) size.y = minHeight;
        if (childCount > 0 && ImGui::BeginListBox("##children", size)) {
            for (int i = 0; i < childCount; i++) {
                auto child = trimmedCell.getChild(i);
                ImGui::PushID(i);
                if (ImGui::Selectable(child->get().getState().getDescriptionOrDefault().c_str()))
                    context.getSelector().select(child.value());
                ImGui::PopID();
            }
            ImGui::EndListBox();
        }
    }
} // hs