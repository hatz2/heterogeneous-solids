//
// Created by Alberto Elorza Rubio on 01/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_CELLWINDOW_H
#define HETEROGENEOUS_SOLIDS_CELLWINDOW_H

#include "../core/ContextWindow.h"

namespace hs {

    class CellWindow: public ContextWindow {
    public:
        CellWindow(std::string title, std::shared_ptr<ContextManager> contextManager);
    protected:
        void renderBody(const Context&) override;
        static void renderCell(const Context&, Cell&);
        static void renderCoef(const Context&, CellCoef&);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CELLWINDOW_H
