//
// Created by Alberto Elorza Rubio on 05/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_CELLAGGREGATOR_H
#define HETEROGENEOUS_SOLIDS_CELLAGGREGATOR_H

#include "../HeterogeneousSolid.h"
#include "../../command/CommandHistory.h"

namespace hs {

    class CellAggregator final {
    public:
        explicit CellAggregator(HeterogeneousSolid& heterogeneousSolid);
        CellAggregator(HeterogeneousSolid& heterogeneousSolid, CommandHistory& commandHistory);

        void addNewCell(std::array<glm::vec3, 64> coefPositions);

        void flush();
        ~CellAggregator();
    private:
        HeterogeneousSolid& heterogeneousSolid;
        std::optional<std::reference_wrapper<CommandHistory>> history;
        std::vector<std::unique_ptr<Command>> commands;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CELLAGGREGATOR_H
