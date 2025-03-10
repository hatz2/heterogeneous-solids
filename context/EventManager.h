//
// Created by Alberto Elorza Rubio on 27/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_EVENTMANAGER_H
#define HETEROGENEOUS_SOLIDS_EVENTMANAGER_H

#include "events/MouseEventHandler.h"
#include "events/KeyboardEventHandler.h"
#include "events/CameraEventHandler.h"
#include "events/SelectionEventHandler.h"
#include "../scene/Scene.h"
#include "events/NavigationEventHandler.h"

namespace hs {

    class EventManager: public MouseEventHandler, public KeyboardEventHandler, public SelectionEventHandler {
    public:
        EventManager() = delete;
        EventManager(Scene& scene, Selector& selector, CommandHistory& commandHistory);
        EventManager(const EventManager&) = delete;

        void handle(const MouseEvent& event) override;
        void handle(const KeyEvent& event) override;
        void handle(const SelectionEvent& event) override;
    private:
        Scene& scene;
        Selector& selector;
        std::unique_ptr<CameraEventHandler> cameraEventHandler;
        std::unique_ptr<NavigationEventHandler> navigationEventHandler;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_EVENTMANAGER_H
