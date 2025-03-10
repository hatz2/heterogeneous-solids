//
// Created by Alberto Elorza Rubio on 27/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_NAVIGATIONEVENTHANDLER_H
#define HETEROGENEOUS_SOLIDS_NAVIGATIONEVENTHANDLER_H

#include "KeyboardEventHandler.h"
#include "../../scene/Scene.h"
#include "../Selector.h"

namespace hs {

    class NavigationEventHandler: public KeyboardEventHandler {
    public:
        explicit NavigationEventHandler(Selector& selector, CommandHistory& commandHistory);

        void handle(const hs::KeyEvent &event) override;
    private:
        Selector& selector;
        CommandHistory& commandHistory;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_NAVIGATIONEVENTHANDLER_H
