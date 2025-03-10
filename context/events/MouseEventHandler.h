//
// Created by Alberto Elorza Rubio on 01/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MOUSEEVENTHANDLER_H
#define HETEROGENEOUS_SOLIDS_MOUSEEVENTHANDLER_H

#include <variant>
#include "EventHandler.h"

namespace hs {

    enum class MouseButton {
        Left,
        Middle,
        Right
    };

    struct ClickMouseEvent {
        float x;
        float y;
        MouseButton button;
        bool shift;
    };

    struct DragMouseEvent {
        float relativeX;
        float relativeY;
        MouseButton button;
        bool shift;
    };

    struct ScrollMouseEvent {
        float delta;
        bool shift;
    };

    using MouseEvent = std::variant<ClickMouseEvent, DragMouseEvent, ScrollMouseEvent>;

    class MouseEventHandler: public EventHandler<const MouseEvent&> {

    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MOUSEEVENTHANDLER_H
