//
// Created by Alberto Elorza Rubio on 28/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_RENDERER_H
#define HETEROGENEOUS_SOLIDS_RENDERER_H

#include <memory>
#include <glm/vec4.hpp>
#include "../shaders/ShaderProgram.h"
#include "Scene.h"
#include "../shaders/ShaderManager.h"
#include "gizmos/Grid.h"
#include "RenderProfile.h"
#include "Cubemap.h"

namespace hs {

    class Renderer {
    public:
        explicit Renderer(ShaderManager& shaderManager);

        std::unique_ptr<SelectionController> renderColorSelection(const RenderProfile& profile, const Scene& scene);
        void render(const RenderProfile& profile, const Scene& scene);
    private:
        // GIZMOS
        Grid grid;

        // CUBEMAP
        std::unique_ptr<Cubemap> cubemap;

        // RESOURCES
        ShaderManager& shaderManager;

        void renderObjects(const RenderProfile& profile, const Scene& scene);
        void renderGizmos(const RenderProfile& profile, const Scene& scene);
        void renderSkybox(const RenderProfile& profile, const Scene& scene);

        void renderSurfaces(const RenderProfile& profile, const Scene& scene);
        void renderLines(const RenderProfile& profile, const Scene& scene, bool selection = false);
        void renderVertices(const RenderProfile& profile, const Scene& scene, bool selection = false);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_RENDERER_H
