//
// Created by alext on 27/05/2025.
//

#include "BuilderImp.h"
#include <stb_image.h>
#include <stb_image_write.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <spdlog/spdlog.h>

#include "../RenderContext.h"

hs::ibl::BuilderImp::BuilderImp(const std::string& hdrPath, ShaderManager& shaderManager)
    : Builder(hdrPath, shaderManager)
{
    initBuffers();
    initMatrices();
    initCube();
    loadHdrTexture();
}

hs::ibl::BuilderImp::~BuilderImp()
{
    glDeleteFramebuffers(1, &frameBuffer);
    glDeleteFramebuffers(1, &renderBuffer);
}

hs::ibl::Builder& hs::ibl::BuilderImp::generateEnvironmentMap(const int size)
{
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);

    result.environmentMap = createEmptyCubeTexture(size, true);

    RenderContext renderContext(*shaderManager.get().requireShaderProgram("cubemap"));
    renderContext.setProjectionMatrix(projectionMatrix);
    renderContext.getUniform("equirectangularMap").set(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hdrTexture);

    glViewport(0, 0, size, size);

    for (auto i = 0; i < viewMatrices.size(); ++i)
    {
        renderContext.setViewMatrix(viewMatrices[i]);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, result.environmentMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube.render(renderContext);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, result.environmentMap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    return *this;
}

hs::ibl::Builder& hs::ibl::BuilderImp::generateIrradianceMap(const int size)
{
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);

    result.irradianceMap = createEmptyCubeTexture(size);

    RenderContext renderContext(*shaderManager.get().requireShaderProgram("irradiance"));
    renderContext.setProjectionMatrix(projectionMatrix);
    renderContext.getUniform("environmentMap").set(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, result.environmentMap);

    glViewport(0, 0, size, size);

    for (unsigned int i = 0; i < viewMatrices.size(); ++i)
    {
        renderContext.setViewMatrix(viewMatrices[i]);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, result.irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube.render(renderContext);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    return *this;
}

hs::ibl::Builder& hs::ibl::BuilderImp::generatePrefilteredMap(const int size)
{
    result.prefilteredMap = createEmptyCubeTexture(size, true);

    int environmentMapResolution;
    glBindTexture(GL_TEXTURE_CUBE_MAP, result.environmentMap);
    glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_TEXTURE_WIDTH, &environmentMapResolution);

    RenderContext renderContext(*shaderManager.get().requireShaderProgram("prefilter"));
    renderContext.setProjectionMatrix(projectionMatrix);
    renderContext.getUniform("environmentMap").set(0);
    renderContext.getUniform("environmentMapResolution").set(environmentMapResolution);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, result.environmentMap);

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    int maxMipLevels = 5;

    for (int mipLevel = 0; mipLevel < maxMipLevels; ++mipLevel)
    {
        const int mipSize = std::lround(size * std::pow(0.5, mipLevel));
        glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipSize, mipSize);
        glViewport(0, 0, mipSize, mipSize);

        float roughness = (float)mipLevel / (float)(maxMipLevels - 1);
        renderContext.getUniform("roughness").set(roughness);

        for (unsigned int i = 0; i < viewMatrices.size(); ++i)
        {
            renderContext.setViewMatrix(viewMatrices[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                   result.prefilteredMap, mipLevel);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            cube.render(renderContext);
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    return *this;
}

hs::ibl::Builder& hs::ibl::BuilderImp::generateBrdfLUT(const int size)
{
    glGenTextures(1, &result.brdfLUT);

    glBindTexture(GL_TEXTURE_2D, result.brdfLUT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, size, size, 0, GL_RG, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, result.brdfLUT, 0);
    glViewport(0, 0, size, size);

    RenderContext renderContext(*shaderManager.get().requireShaderProgram("brdf"));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render quad
    std::vector<glm::vec3> vertices = {
        {-1.0f,  1.0f, 0.0f}, // 0
        {-1.0f, -1.0f, 0.0f}, // 1
        { 1.0f,  1.0f, 0.0f}, // 2
        { 1.0f, -1.0f,  1.0f}, // 3
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        1, 2, 3,
    };

    std::vector<glm::vec3> texCoords = {
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 0.0f}
    };

    Mesh quad;
    quad.setVertices(vertices);
    quad.setIndices(indices);
    quad.setUVW(texCoords);

    quad.render(renderContext);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    return *this;
}

void hs::ibl::BuilderImp::initBuffers()
{
    glGenFramebuffers(1, &frameBuffer);
    glGenRenderbuffers(1, &renderBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void hs::ibl::BuilderImp::initMatrices()
{
    projectionMatrix = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    viewMatrices = {
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
    };
}

void hs::ibl::BuilderImp::initCube()
{
    std::vector<glm::vec3> vertices = {
        {-1.0f,  1.0f, -1.0f}, // 0
        {-1.0f, -1.0f, -1.0f}, // 1
        { 1.0f, -1.0f, -1.0f}, // 2
        { 1.0f,  1.0f, -1.0f}, // 3
        {-1.0f, -1.0f,  1.0f}, // 4
        {-1.0f,  1.0f,  1.0f}, // 5
        { 1.0f, -1.0f,  1.0f}, // 6
        { 1.0f,  1.0f,  1.0f}  // 7
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0,

        4, 1, 0,
        0, 5, 4,

        2, 6, 7,
        7, 3, 2,

        4, 5, 7,
        7, 6, 4,

        0, 3, 7,
        7, 5, 0,

        1, 4, 2,
        2, 4, 6
    };

    cube.setVertices(vertices);
    cube.setIndices(indices);
}

void hs::ibl::BuilderImp::loadHdrTexture()
{
    if (hdrTexturePath.empty())
    {
        spdlog::error("[hs::ibl::BuilderImp::loadHdrTexture]: Empty texture path");
        return;
    }

    int width;
    int height;
    int numChannels;

    stbi_set_flip_vertically_on_load(true);
    float* imageData = stbi_loadf(hdrTexturePath.c_str(), &width, &height, &numChannels, 0);

    if (imageData)
    {
        glGenTextures(1, &hdrTexture);
        glBindTexture(GL_TEXTURE_2D, hdrTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, imageData);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(imageData);
    }
    else
    {
        spdlog::error("[hs::ibl::BuilderImp::loadHdrTexture] HDR texture load failed on file: {}", hdrTexturePath);
    }
}

GLuint hs::ibl::BuilderImp::createEmptyCubeTexture(const int size, bool lod) const
{
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, size, size, 0,
            GL_RGB, GL_FLOAT, nullptr);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (lod)
    {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    return textureId;
}
