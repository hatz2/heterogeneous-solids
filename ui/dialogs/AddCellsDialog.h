//
// Created by Alberto Elorza Rubio on 21/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_ADDCELLSDIALOG_H
#define HETEROGENEOUS_SOLIDS_ADDCELLSDIALOG_H

#include "../../heterogeneous_solids/HeterogeneousSolid.h"
#include "../core/StatefulDialog.h"
#include "../../command/CommandHistory.h"

namespace hs {

    class AddCellsDialog: public StatefulDialog<HeterogeneousSolid, CommandHistory> {
    public:
        explicit AddCellsDialog(std::string title);
    protected:
        DoClose renderBody(HeterogeneousSolid&, CommandHistory&) override;
    private:
        int ring;

        int ringCells, maxRingCells;
        glm::ivec2 subRingCells;
        float innerRingRadius;
        glm::vec2 ringSize;
        glm::vec3 ringDisp;

        glm::ivec3 gridCells;
        glm::vec3 gridSize, gridDisp;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_ADDCELLSDIALOG_H
