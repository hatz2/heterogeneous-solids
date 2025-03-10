//
// Created by Alberto Elorza Rubio on 22/02/2024.
//

#include "SceneTools.h"

namespace hs {
    SceneTools::SceneTools() : transformGizmo(TransformGizmo::Translation) {

    }

    TransformGizmo SceneTools::getTransformGizmo() const {
        return transformGizmo;
    }

    void SceneTools::setTransformGizmo(TransformGizmo transformGizmo) {
        SceneTools::transformGizmo = transformGizmo;
    }
} // hs