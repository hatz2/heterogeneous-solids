//
// Created by Alberto Elorza Rubio on 28/11/2023.
//

#include <filesystem>
#include "Renderer.h"
#include "gizmos/LightGizmo.h"

#include <iostream>

#include "ibl/BuilderImp.h"

namespace hs {
    Renderer::Renderer(ShaderManager& shaderManager) : shaderManager(shaderManager) {
        iblData = ibl::BuilderImp("C:\\Users\\alext\\Documents\\TFM\\newport_loft.hdr", shaderManager)
                    .generateEnvironmentMap()
                    .generateIrradianceMap()
                    .getResult();
    }

    std::unique_ptr<SelectionController> Renderer::renderColorSelection(const RenderProfile& profile, const Scene& scene) {
        glDisable(GL_MULTISAMPLE);
        glDisable(GL_BLEND);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        auto view = scene.getCamera().view();
        auto projection = scene.getCamera().projection();

        std::unique_ptr<SelectionController> selectionController;
        {
            RenderContext renderContext(*shaderManager.requireShaderProgram("surface_select"));
            renderContext.setSelection(&scene.getSelectedObject());
            renderContext.setViewMatrix(view);
            renderContext.setProjectionMatrix(projection);
            renderContext.setRenderMode(RenderMode::SurfaceSelectColor);

            selectionController = std::make_unique<SelectionController>(renderContext.getUniform("solidColor"));
            renderContext.setSelectionController(selectionController.get());

            auto color = selectionController->getLast();

            glClearColor(color.x, color.y, color.z, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            scene.getRoot().getRenderer()(renderContext);
        }
        {
            RenderContext renderContext(*shaderManager.requireShaderProgram("vertex_select"));
            renderContext.setSelection(&scene.getSelectedObject());
            renderContext.setViewMatrix(view);
            renderContext.setProjectionMatrix(projection);
            renderContext.setRenderMode(RenderMode::VertexSelectColor);
            renderContext.getUniform("vertexRadius").set(profile.getVertexRadius());
            renderContext.getUniform("cameraPosition").set(scene.getCamera().getPosition());

            selectionController->setSelectionUniform(renderContext.getUniform("solidColor"));
            renderContext.setSelectionController(selectionController.get());

            glDepthMask(false);
            glDepthFunc(GL_ALWAYS);
            scene.getRoot().getRenderer()(renderContext);
            glDepthFunc(GL_LEQUAL);
            glDepthMask(true);
        }

        return selectionController;
    }

    void Renderer::render(const RenderProfile& profile, const Scene& scene) {
        auto& backgroundColor = profile.getBackgroundColor();
        glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

        if (profile.isAntialiasing()) glEnable(GL_MULTISAMPLE);
        else glDisable(GL_MULTISAMPLE);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glEnable(GL_PROGRAM_POINT_SIZE);

        auto& modelingLight = scene.getLights().getModelingLight();
        modelingLight.getLightProps().setPosition(scene.getCamera().getPosition());
        modelingLight.getLightProps().setLookAt(scene.getCamera().getLookAt());

        renderObjects(profile, scene);

        renderGizmos(profile, scene);

        renderSkybox(profile, scene);

        glDisable(GL_BLEND);
    }

    void Renderer::renderObjects(const RenderProfile& profile, const Scene& scene) {
        // SURFACES
        renderSurfaces(profile, scene);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        auto isInvisible = [](std::reference_wrapper<SceneNode> object) -> bool {
            if (!object.get().getState().isVisible()) return true;
            while (auto parent = object.get().getParent()) {
                object = parent->get();
                if (!object.get().getState().isVisible()) return true;
            }
            return false;
        };

        if (!profile.isHighlightSelection() || isInvisible(scene.getSelectedObject())) {
            // LINES
            renderLines(profile, scene);

            // VERTICES
            renderVertices(profile, scene);

            return;
        }

        auto hide = [](const std::function<void(RenderContext&)>&, RenderContext&) { };

        // LINES
        scene.getSelectedObject().getRenderer().decorate(hide);
        renderLines(profile, scene);
        scene.getSelectedObject().getRenderer().pop();

        if (!profile.isSelectionDrawDepth()) {
            glDepthMask(false);
            glDepthFunc(GL_ALWAYS);
        }
        renderLines(profile, scene, true);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(true);

        // VERTICES
        scene.getSelectedObject().getRenderer().decorate(hide);
        renderVertices(profile, scene);
        scene.getSelectedObject().getRenderer().pop();

        renderVertices(profile, scene, true);
    }

    void Renderer::renderGizmos(const RenderProfile& profile, const Scene& scene) {
        auto view = scene.getCamera().view();
        auto projection = scene.getCamera().projection();

        // GRID
        if (profile.isShowGridGizmo()) {
            RenderContext renderContext(*shaderManager.requireShaderProgram("grid_gizmo"));
            renderContext.setSelection(&scene.getSelectedObject());
            renderContext.setViewMatrix(view);
            renderContext.setProjectionMatrix(projection);
            renderContext.getUniform("cameraPosition").set(scene.getCamera().getPosition());
            glLineWidth(2);
            grid.render(renderContext);
        }

        // LIGHTS
        if (profile.isShowLightsGizmo()) {
            RenderContext renderContext(*shaderManager.requireShaderProgram("line"));
            renderContext.setSelection(&scene.getSelectedObject());
            renderContext.setViewMatrix(view);
            renderContext.setProjectionMatrix(projection);
            renderContext.setRenderMode(RenderMode::Lines);

            renderContext.getUniform("solidColor").set(glm::vec4(0.7, 0.5, 0, 1));
            glLineWidth(10);
            for (auto& light : scene.getLights())
                if (light.get().getLightType() == LightType::Directional)
                    LightGizmo(light).render(renderContext);
        }
    }

    void Renderer::renderSkybox(const RenderProfile& profile, const Scene& scene)
    {
        if (!profile.isShowSkybox())
            return;

        GLboolean depthMask;
        glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);
        glDepthMask(GL_FALSE);

        RenderContext renderContext(*shaderManager.requireShaderProgram("skybox"));
        renderContext.setViewMatrix(scene.getCamera().view());
        renderContext.setProjectionMatrix(scene.getCamera().projection());

        renderContext.getUniform("environmentMap").set(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, iblData.environmentMap);

        scene.getSkybox().render(renderContext);

        glDepthMask(depthMask);
    }

    void Renderer::renderSurfaces(const RenderProfile& profile, const Scene &scene) {
        if (!profile.isShowSurfaces()) return;

        RenderContext renderContext(*shaderManager.requireShaderProgram("surface"));
        renderContext.setSelection(&scene.getSelectedObject());
        renderContext.setViewMatrix(scene.getCamera().view());
        renderContext.setProjectionMatrix(scene.getCamera().projection());

        renderContext.setRenderMode(RenderMode::Surfaces);
        renderContext.setDetailedRendering(profile.isDetailedSurfaces());
        renderContext.getUniform("usePbr").set(profile.isUsePbr());
        renderContext.getUniform("irradianceMap").set(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, iblData.irradianceMap);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        auto lights = scene.getLights().getCompiledLights();

        renderContext.getUniform("numLights").set(static_cast<unsigned int>(lights.size()));

        for (size_t i = 0; i < lights.size(); ++i)
        {
            lights[i].get().apply(renderContext, i);
        }

        scene.getRoot().getRenderer()(renderContext);
    }

    void Renderer::renderLines(const RenderProfile& profile, const Scene& scene, bool selection) {
        auto tint = glm::vec4(0);
        std::reference_wrapper<SceneNode> target = scene.getRoot();
        if (selection) {
            target = scene.getSelectedObject();
            tint = profile.getSelectionTint();
        }

        RenderContext renderContext(*shaderManager.requireShaderProgram("line"));
        renderContext.setSelection(&scene.getSelectedObject());
        renderContext.setViewMatrix(scene.getCamera().view());
        renderContext.setProjectionMatrix(scene.getCamera().projection());
        renderContext.setRenderMode(RenderMode::Lines);
        if (auto transform = target.get().getImmediateTransform())
            renderContext.setModelMatrix(transform.value());

        if (profile.isShowDetailedLines()) {
            renderContext.setDetailedRendering(true);
            renderContext.getUniform("solidColor").set(profile.getDetailedLinesColor() + tint);
            glLineWidth(profile.getDetailedLinesThickness());
            target.get().getRenderer()(renderContext);
        }
        if (profile.isShowMainLines()) {
            renderContext.setDetailedRendering(false);
            renderContext.getUniform("solidColor").set(profile.getMainLinesColor() + tint);
            glLineWidth(profile.getMainLinesThickness());
            target.get().getRenderer()(renderContext);
        }
        if (profile.isShowNormalField()) {
            renderContext.setRenderMode(RenderMode::Normals);
            renderContext.setDetailedRendering(true);
            renderContext.getUniform("solidColor").set(profile.getNormalFieldColor() + tint);
            glLineWidth(profile.getNormalFieldThickness());
            target.get().getRenderer()(renderContext);
        }
    }

    void Renderer::renderVertices(const RenderProfile& profile, const Scene& scene, bool selection) {
        if (!profile.isShowVertices()) return;

        glm::vec4 vertexColor = profile.getVertexColor();
        std::reference_wrapper<SceneNode> target = scene.getRoot();
        if (selection) {
            target = scene.getSelectedObject();
            vertexColor = vertexColor + profile.getSelectionTint();
        }

        RenderContext renderContext(*shaderManager.requireShaderProgram("vertex"));
        renderContext.setSelection(&scene.getSelectedObject());
        renderContext.getUniform("solidColor").set(vertexColor);
        renderContext.getUniform("vertexRadius").set(profile.getVertexRadius());
        renderContext.getUniform("cameraPosition").set(scene.getCamera().getPosition());
        renderContext.setViewMatrix(scene.getCamera().view());
        renderContext.setProjectionMatrix(scene.getCamera().projection());

        renderContext.setRenderMode(RenderMode::Vertices);

        if (auto transform = target.get().getImmediateTransform())
            renderContext.setModelMatrix(transform.value());

        glDepthMask(false);
        glDepthFunc(GL_ALWAYS);
        target.get().getRenderer()(renderContext);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(true);
    }
} // hs