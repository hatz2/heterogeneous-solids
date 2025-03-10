//
// Created by Alberto Elorza Rubio on 01/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_CAMERAEVENTHANDLER_H
#define HETEROGENEOUS_SOLIDS_CAMERAEVENTHANDLER_H

#include "MouseEventHandler.h"
#include "../../scene/Camera.h"
#include "KeyboardEventHandler.h"

namespace hs {

    class CameraEventHandler: public MouseEventHandler, public KeyboardEventHandler {
    public:
        explicit CameraEventHandler(Camera& camera);
        void handle(const MouseEvent& event) override;
        void handle(const KeyEvent& event) override;
    private:
        Camera& camera;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CAMERAEVENTHANDLER_H
