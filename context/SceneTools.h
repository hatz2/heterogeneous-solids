//
// Created by Alberto Elorza Rubio on 22/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SCENETOOLS_H
#define HETEROGENEOUS_SOLIDS_SCENETOOLS_H

namespace hs {

    enum class TransformGizmo {
        Translation,
        Rotation,
        Scale
    };

    class SceneTools {
    public:
        SceneTools();

        [[nodiscard]] TransformGizmo getTransformGizmo() const;
        void setTransformGizmo(TransformGizmo transformGizmo);

    private:
        TransformGizmo transformGizmo;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SCENETOOLS_H
