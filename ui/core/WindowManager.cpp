//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#include "WindowManager.h"

namespace hs {
    void WindowManager::render() {
        for (auto& window : staticWindows) {
            if (window->isOpen()) window->render();
        }
        for (auto it = dynamicWindows.begin(); it != dynamicWindows.end(); ) {
            if (!(*it)->isOpen()) {
                it = dynamicWindows.erase(it);
                continue;
            }
            (*it)->render();
            ++it;
        }
    }

    void WindowManager::addStaticWindow(const std::shared_ptr<Window>& window) {
        staticWindows.push_back(window);
    }

    const std::vector<std::shared_ptr<Window>>& WindowManager::getStaticWindows() const {
        return staticWindows;
    }

    void WindowManager::addDynamicWindow(const std::shared_ptr<Window>& window) {
        dynamicWindows.push_back(window);
    }

    const std::list<std::shared_ptr<Window>>& WindowManager::getDynamicWindows() const {
        return dynamicWindows;
    }
} // hs