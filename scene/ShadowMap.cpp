//
// Created by alext on 05/06/2025.
//

#include "ShadowMap.h"
#include <stb_image_write.h>

namespace hs {
    ShadowMap::ShadowMap(const int width, const int height)
        : width(width)
        , height(height)
    {
        id = createEmptyTexture2D(width, height);

        GLint currentFBO;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFBO);
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, id, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, currentFBO);
    }

    ShadowMap::~ShadowMap()
    {
        glDeleteFramebuffers(1, &framebuffer);
        glDeleteTextures(1, &id);
    }

    void ShadowMap::render(const Scene& scene, ShaderManager& shaderManager, Light& light)
    {
        GLint currentFBO;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFBO);
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        glViewport(0, 0, width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glClear(GL_DEPTH_BUFFER_BIT);

        // configure shader and matrices
        float nearPlane = 0.01f, farPlane = 150.0f;
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
        glm::mat4 lightView = glm::lookAt(
            light.getLightProps().getPosition(),
            light.getLightProps().getLookAt(),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        RenderContext renderContext(*shaderManager.requireShaderProgram("shadow_map"));
        renderContext.setProjectionMatrix(lightProjection);
        renderContext.setViewMatrix(lightView);
        renderContext.setRenderMode(RenderMode::SurfaceWithoutMaterial);

        // render scene
        scene.getRoot().getRenderer()(renderContext);

        glBindFramebuffer(GL_FRAMEBUFFER, currentFBO);
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
    }

    GLuint ShadowMap::createEmptyTexture2D(const int width, const int height)
    {
        GLuint textureId;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0,
            GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        return textureId;
    }
} // hs