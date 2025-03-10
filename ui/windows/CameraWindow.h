//
// Created by Alberto Elorza Rubio on 23/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_CAMERAWINDOW_H
#define HETEROGENEOUS_SOLIDS_CAMERAWINDOW_H

#include "../core/ContextWindow.h"

namespace hs {

    class CameraWindow: public ContextWindow {
    protected:
        void renderBody(const hs::Context &) override;
    public:
        CameraWindow(std::string title, const std::shared_ptr<ContextManager>& contextManager);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CAMERAWINDOW_H
