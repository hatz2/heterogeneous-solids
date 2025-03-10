//
// Created by Alberto Elorza Rubio on 18/12/2023.
//

#include "SelectionMenu.h"
#include "../core/SelectMenuNode.h"
#include "../../command/basic/AddObjectCommand.h"
#include "../../command/basic/RemoveObjectCommand.h"
#include "../../command/basic/SetTrimmingNodeCommand.h"
#include "../../command/basic/CommandGroup.h"
#include "../../command/basic/InsertItemCommand.h"

#include <utility>

namespace hs {
    SelectionMenu::SelectionMenu(std::shared_ptr<ContextManager> contextManager, UI& ui) :
        ContextMenuNode(std::move(contextManager)),
        addCellsDialog(std::make_unique<AddCellsDialog>("Add Cells"))
    {
        ui.getDialogManager().addDialog(addCellsDialog);
    }

    void SelectionMenu::renderMenuNode(const Context& context) {
        if (ImGui::BeginMenu("Selection")) {
            SceneNode& activeObject = context.getScene().getSelectedObject();
            if (ImGui::MenuItem("Visible", nullptr, activeObject.getState().isVisible())) {
                activeObject.getState().setVisible(!activeObject.getState().isVisible());
            }
            ImGui::Separator();
            SelectionVisitor visitor(context, this);
            activeObject.visitNode(visitor);
            ImGui::EndMenu();
        }
    }

    SelectionMenu::SelectionVisitor::SelectionVisitor(const Context& context, SelectionMenu* selectionMenu) :
        context(context), selectionMenu(selectionMenu)
    {

    }

    void SelectionMenu::SelectionVisitor::doGroupNode(GroupNode& group3D) {
        if (ImGui::MenuItem("Add Heterogeneous Solid")) {
            auto hs = std::make_unique<HeterogeneousSolid>();
            auto hsMaterial = hs->getMaterial();
            std::vector<std::unique_ptr<Command>> steps;
            steps.push_back(std::make_unique<InsertItemCommand<Material>>(
                hsMaterial->getPrimaryMaterial(), context.getMaterialEditor().getMaterials()
            ));
            steps.push_back(std::make_unique<InsertItemCommand<Material>>(
                hsMaterial->getSecondaryMaterial(), context.getMaterialEditor().getMaterials()
            ));
            steps.push_back(std::make_unique<InsertItemCommand<HeterogeneousMaterial>>(
                hsMaterial, context.getMaterialEditor().getHeterogeneousMaterials()
            ));
            steps.push_back(std::make_unique<AddObjectCommand>(std::move(hs), group3D));
            context.getCommandHistory().execute<CommandGroup>("Add Heterogeneous Solid", std::move(steps));
        }
        if (ImGui::MenuItem("Add Group")) {
            context.getCommandHistory().execute<AddObjectCommand>(
                std::make_unique<GroupNode>(),
                group3D
            );
        }
        if (auto parent = group3D.getParent()) {
            if (ImGui::MenuItem("Remove")) {
                context.getCommandHistory().execute<RemoveObjectCommand>(
                    group3D.getIndexInParent(),
                    parent.value()
                );
            }
        }
    }

    void SelectionMenu::SelectionVisitor::doHeterogeneousSolid(HeterogeneousSolid& heterogeneousSolid) {
        if (ImGui::MenuItem("Add Cells")) {
            selectionMenu->addCellsDialog->show(heterogeneousSolid, context.getCommandHistory());
        }
        if (auto parent = heterogeneousSolid.getParent()) {
            if (ImGui::MenuItem("Remove")) {
                context.getCommandHistory().execute<RemoveObjectCommand>(
                    heterogeneousSolid.getIndexInParent(),
                    parent.value()
                );
            }
        }
    }

    void SelectionMenu::SelectionVisitor::doCell(Cell& cell) {
        if (auto parent = cell.getParent()) {
            if (ImGui::MenuItem("Remove")) {
                context.getCommandHistory().execute<RemoveObjectCommand>(
                    cell.getIndexInParent(),
                    parent.value()
                );
            }
        }
    }
} // hs