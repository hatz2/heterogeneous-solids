//
// Created by Alberto Elorza Rubio on 08/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_KEYBOARDEVENTHANDLER_H
#define HETEROGENEOUS_SOLIDS_KEYBOARDEVENTHANDLER_H

#include "EventHandler.h"

#include <imgui.h>

namespace hs {

    struct KeyEvent {
        using KeyIdType = ImGuiKey;

        ImGuiKey key;
        const char* keyName;
        bool shift;
        bool ctrl;
        bool alt;
    };

    class KeyboardEventHandler: public EventHandler<const KeyEvent&> {

    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_KEYBOARDEVENTHANDLER_H
