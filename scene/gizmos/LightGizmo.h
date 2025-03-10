//
// Created by Alberto Elorza Rubio on 09/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_LIGHTGIZMO_H
#define HETEROGENEOUS_SOLIDS_LIGHTGIZMO_H

#include "../lights/Light.h"
#include "../objects/SceneNode.h"

namespace hs {

    class LightGizmoResource {
    private:
        GLuint idVBO;
        GLuint idVAO;
        GLuint count;
        friend class LightGizmo;
    public:
        explicit LightGizmoResource();
        ~LightGizmoResource();

        LightGizmoResource(const LightGizmoResource&) = delete;
        LightGizmoResource& operator=(const LightGizmoResource&) = default;
    };

    class LightGizmo {
    private:
        static std::unique_ptr<LightGizmoResource> lightResource;
        Light& light;
    public:
        explicit LightGizmo(Light& light);

        void render(hs::RenderContext& renderContext);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_LIGHTGIZMO_H
