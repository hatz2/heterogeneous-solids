//
// Created by Alberto Elorza Rubio on 22/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_RENDERCONTEXT_H
#define HETEROGENEOUS_SOLIDS_RENDERCONTEXT_H

#include <glm/glm.hpp>
#include "../shaders/ShaderProgram.h"
#include "../shaders/Uniform.h"
#include "../shaders/SubroutineManager.h"
#include "SelectionController.h"
#include "objects/Transform.h"

namespace hs {

    enum class RenderMode {
        Lines,
        Normals,
        Surfaces,
        Vertices,
        SurfaceSelectColor,
        VertexSelectColor
    };

    class RenderContext {
    public:
        RenderContext() = delete;
        explicit RenderContext(ShaderProgram& shaderProgram);
        RenderContext(const RenderContext&) = delete;

        [[nodiscard]] glm::mat4 getModelMatrix() const;
        void setModelMatrix(glm::mat4 modelMatrix);
        void setModelMatrix(Transform& transform);

        [[nodiscard]] glm::mat4 getViewMatrix() const;
        void setViewMatrix(glm::mat4 viewMatrix);

        [[nodiscard]] glm::mat4 getProjectionMatrix() const;
        void setProjectionMatrix(glm::mat4 projectionMatrix);

        [[nodiscard]] RenderMode getRenderMode() const;
        void setRenderMode(RenderMode renderMode);

        [[nodiscard]] bool IsDetailedRendering() const;
        void setDetailedRendering(bool detailedRendering);

        Uniform getUniform(const std::string& name);
        SubroutineManager& getFragmentSubroutines();

        [[nodiscard]] SelectionController& getSelectionController();
        void setSelectionController(SelectionController* selectionController);

        [[nodiscard]] SceneNode* getSelection() const;
        void setSelection(SceneNode* sceneNode);
    private:
        ShaderProgram& shaderProgram;
        SubroutineManager fragmentSubroutineManager;
        SelectionController* selectionController;
        glm::mat4 modelMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        RenderMode renderMode;
        bool detailedRendering;

        SceneNode* selection;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_RENDERCONTEXT_H
