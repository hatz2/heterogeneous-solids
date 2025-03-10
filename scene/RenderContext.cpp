//
// Created by Alberto Elorza Rubio on 22/11/2023.
//

#include "RenderContext.h"

#include <utility>
#include <stdexcept>

namespace hs {
    RenderContext::RenderContext(ShaderProgram& shaderProgram):
        shaderProgram(shaderProgram),
        fragmentSubroutineManager(RenderContext::shaderProgram, GL_FRAGMENT_SHADER),
        selectionController(nullptr),
        modelMatrix(1),
        viewMatrix(1),
        projectionMatrix(1),
        renderMode(RenderMode::Surfaces),
        detailedRendering(true),
        selection(nullptr)
    {
        shaderProgram.use();
    }

    glm::mat4 RenderContext::getModelMatrix() const {
        return modelMatrix;
    }

    void RenderContext::setModelMatrix(glm::mat4 modelMatrix) {
        getUniform("modelMatrix").set(modelMatrix);
        RenderContext::modelMatrix = modelMatrix;
    }

    void RenderContext::setModelMatrix(Transform& transform) {
        setModelMatrix(transform.matrix());
    }

    glm::mat4 RenderContext::getViewMatrix() const {
        return viewMatrix;
    }

    void RenderContext::setViewMatrix(glm::mat4 viewMatrix) {
        getUniform("viewMatrix").set(viewMatrix);
        RenderContext::viewMatrix = viewMatrix;
    }

    glm::mat4 RenderContext::getProjectionMatrix() const {
        return projectionMatrix;
    }

    void RenderContext::setProjectionMatrix(glm::mat4 projectionMatrix) {
        getUniform("projectionMatrix").set(projectionMatrix);
        RenderContext::projectionMatrix = projectionMatrix;
    }

    RenderMode RenderContext::getRenderMode() const {
        return renderMode;
    }

    void RenderContext::setRenderMode(RenderMode renderMode) {
        RenderContext::renderMode = renderMode;
    }

    bool RenderContext::IsDetailedRendering() const {
        return detailedRendering;
    }

    void RenderContext::setDetailedRendering(bool detailedRendering) {
        RenderContext::detailedRendering = detailedRendering;
    }

    Uniform RenderContext::getUniform(const std::string& name) {
        return { name, shaderProgram };
    }

    SubroutineManager& RenderContext::getFragmentSubroutines() {
        return fragmentSubroutineManager;
    }

    SelectionController& RenderContext::getSelectionController() {
        if (selectionController == nullptr) throw std::runtime_error("Not using a selection controller");
        return *selectionController;
    }

    void RenderContext::setSelectionController(SelectionController* selectionController) {
        RenderContext::selectionController = selectionController;
    }

    SceneNode* RenderContext::getSelection() const {
        return selection;
    }

    void RenderContext::setSelection(SceneNode* sceneNode) {
        selection = sceneNode;
    }
} // hs