//
// Created by Alberto Elorza Rubio on 11/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_PROFILERWINDOW_H
#define HETEROGENEOUS_SOLIDS_PROFILERWINDOW_H

#include <array>
#include "../core/Window.h"

namespace hs {

    class ProfilerWindow: public Window {
    public:
        explicit ProfilerWindow(std::string name);

        void render() override;
    protected:
        void renderBody() override;
    private:
        std::array<float, 256> frameRateHistory;
        int history_offset;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_PROFILERWINDOW_H
