//
// Created by Alberto Elorza Rubio on 21/12/2023.
//

#include "AddCellsDialog.h"

#include "../../heterogeneous_solids/factories/HeterogeneousSolidFactory.h"

namespace hs {
    AddCellsDialog::AddCellsDialog(std::string title) :
        StatefulDialog<HeterogeneousSolid, CommandHistory>(std::move(title)),
        ring(0),

        ringCells(4),
        maxRingCells(4),
        subRingCells(1),
        innerRingRadius(1),
        ringSize(1),
        ringDisp(0),

        gridCells(1),
        gridSize(1),
        gridDisp(0)
    {

    }

    Dialog::DoClose AddCellsDialog::renderBody(HeterogeneousSolid& heterogeneousSolid, CommandHistory& commands) {
        bool close = false;

        ImGui::Combo("Mode", &ring, "Grid\0Ring\0");

        if (ring) {
            ImGui::DragInt("Cells", &ringCells, 1, 1, 15, "%d", ImGuiSliderFlags_AlwaysClamp);
            ImGui::DragInt("Max Cells", &maxRingCells, 1, 1, 15, "%d", ImGuiSliderFlags_AlwaysClamp);
            ImGui::DragFloat("Inner Radius", &innerRingRadius, 0.1);
            ImGui::DragInt2("Sub Cells", glm::value_ptr(subRingCells), 1, 1, 3, "%d", ImGuiSliderFlags_AlwaysClamp);
            ImGui::DragFloat2("Size", glm::value_ptr(ringSize), 0.1);
            ImGui::DragFloat3("Offset", glm::value_ptr(ringDisp), 0.1);
        } else {
            ImGui::DragInt3("Cells", glm::value_ptr(gridCells), 1, 1, 5, "%d", ImGuiSliderFlags_AlwaysClamp);
            ImGui::DragFloat3("Size", glm::value_ptr(gridSize), 0.1);
            ImGui::DragFloat3("Offset", glm::value_ptr(gridDisp), 0.1);
        }

        if (ImGui::Button("Add")) {
            close = true;
            CellAggregator aggregator(heterogeneousSolid, commands);
            if (ring)
                HeterogeneousSolidFactory::addRingOfCells(
                    aggregator, ringCells, maxRingCells, innerRingRadius, subRingCells.x, subRingCells.y,
                    ringSize.x, ringSize.y, ringDisp.x, ringDisp.y, ringDisp.z
                );
            else
                HeterogeneousSolidFactory::addGridOfCells(
                    aggregator, gridCells.x, gridCells.y, gridCells.z,
                    gridSize.x, gridSize.y, gridSize.z, gridDisp.x, gridDisp.y, gridDisp.z
                );
        }
        return close;
    }
} // hs