//
// Created by Alberto Elorza Rubio on 23/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SELECTIONEVENTHANDLER_H
#define HETEROGENEOUS_SOLIDS_SELECTIONEVENTHANDLER_H

#include "EventHandler.h"
#include "../../scene/SelectionController.h"

namespace hs {

    struct SelectionEvent {
        SelectionController::Selectable selected;
    };

    class SelectionEventHandler: public EventHandler<const SelectionEvent&> {

    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SELECTIONEVENTHANDLER_H
