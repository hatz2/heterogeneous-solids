//
// Created by Alberto Elorza Rubio on 27/12/2023.
//

#include "EventManager.h"

namespace hs {
    EventManager::EventManager(Scene& scene, Selector& selector, CommandHistory& commandHistory) :
        scene(scene),
        selector(selector),

        cameraEventHandler(std::make_unique<CameraEventHandler>(scene.getCamera())),
        navigationEventHandler(std::make_unique<NavigationEventHandler>(selector, commandHistory))
    {

    }

    void EventManager::handle(const MouseEvent& event) {
        cameraEventHandler->handle(event);
    }

    void EventManager::handle(const KeyEvent& event) {
        cameraEventHandler->handle(event);
        navigationEventHandler->handle(event);
    }

    void EventManager::handle(const SelectionEvent& event) {
        switch (event.selected.index()) {
            case 0:
                selector.select(std::get<0>(event.selected));
                break;
        }
    }
} // hs