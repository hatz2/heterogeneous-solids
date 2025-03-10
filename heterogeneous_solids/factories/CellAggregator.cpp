//
// Created by Alberto Elorza Rubio on 05/12/2023.
//

#include "CellAggregator.h"
#include "../../command/basic/CommandGroup.h"
#include "../../command/basic/AddObjectCommand.h"

#include <utility>

namespace hs {
    CellAggregator::CellAggregator(HeterogeneousSolid &heterogeneousSolid) :
        heterogeneousSolid(heterogeneousSolid), history(std::nullopt)
    {

    }

    CellAggregator::CellAggregator(HeterogeneousSolid& heterogeneousSolid, CommandHistory& commandHistory) :
        heterogeneousSolid(heterogeneousSolid), history(std::ref(commandHistory))
    {

    }

    void CellAggregator::addNewCell(std::array<glm::vec3, 64> coefPositions) {
        auto newCell = std::make_unique<Cell>(coefPositions);
        commands.push_back(std::make_unique<AddObjectCommand>(std::move(newCell), heterogeneousSolid));
    }

    void CellAggregator::flush() {
        if (CellAggregator::history.has_value()) {
            CellAggregator::history->get().execute<CommandGroup>("Add Cells", std::move(commands));
        } else {
            for (auto& command : commands) command->execute();
            commands.clear();
        }
    }

    CellAggregator::~CellAggregator() {
        flush();
    }
} // hs