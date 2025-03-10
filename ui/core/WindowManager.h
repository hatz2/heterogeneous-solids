//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_WINDOWMANAGER_H
#define HETEROGENEOUS_SOLIDS_WINDOWMANAGER_H

#include <vector>
#include <memory>
#include <list>
#include "Window.h"

namespace hs {

    class WindowManager {
    public:
        WindowManager() = default;

        void render();

        void addStaticWindow(const std::shared_ptr<Window>& window);
        [[nodiscard]] const std::vector<std::shared_ptr<Window>>& getStaticWindows() const;

        void addDynamicWindow(const std::shared_ptr<Window>& window);
        [[nodiscard]] const std::list<std::shared_ptr<Window>>& getDynamicWindows() const;
    private:
        std::vector<std::shared_ptr<Window>> staticWindows;
        std::list<std::shared_ptr<Window>> dynamicWindows;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_WINDOWMANAGER_H
