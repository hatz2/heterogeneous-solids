//
// Created by alext on 14/04/2025.
//

#include "Cubemap.h"
#include <stb_image.h>
#include <stb_image_write.h>
#include <GL/glew.h>
#include <spdlog/spdlog.h>
#include <iostream>

#include "drawables/Mesh.h"

void renderCube();

hs::Cubemap::Cubemap(const std::vector<std::string>& faces) : id(0)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    int width;
    int height;
    int numChannels;

    for (size_t i = 0; i < faces.size(); ++i)
    {
        unsigned char* imageData = stbi_load(faces[i].c_str(), &width, &height, &numChannels, 0);

        if (imageData)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
            stbi_image_free(imageData);
        }
        else
        {
            spdlog::error("[hs::Cubemap::Cubemap] Cubemap texture load failed on file: {}", faces[i]);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

hs::Cubemap::Cubemap(const std::string& hdrImgPath, ShaderManager& shaderManager)
{
    initFrameBuffers();
    unsigned int hdrTexture = loadHdrTexture(hdrImgPath);
    mapHdrTextureToCubeTexture(hdrTexture, shaderManager);
    convolute(shaderManager);
}

void hs::Cubemap::apply(RenderContext& renderContext) const
{
    renderContext.getUniform("cubemap").set(id);
}

int hs::Cubemap::getId() const
{
    return id;
}

int hs::Cubemap::getConvolutedId() const
{
    return convolutedId;
}

void hs::Cubemap::initFrameBuffers()
{
    glGenFramebuffers(1, &frameBuffer);
    glGenRenderbuffers(1, &renderBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

unsigned int hs::Cubemap::createEmptyCubeTexture(const int width, const int height)
{
    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, width, height, 0,
            GL_RGB, GL_FLOAT, nullptr);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureId;
}

unsigned int hs::Cubemap::loadHdrTexture(const std::string& hdrImgPath)
{
    int width;
    int height;
    int numChannels;
    unsigned int hdrTexture;

    stbi_set_flip_vertically_on_load(true);
    float* imageData = stbi_loadf(hdrImgPath.c_str(), &width, &height, &numChannels, 0);

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
        spdlog::error("[hs::Cubemap::loadHdrTexture] HDR texture load failed on file: {}", hdrImgPath);
    }

    return hdrTexture;
}

void hs::Cubemap::mapHdrTextureToCubeTexture(unsigned int hdrTexture, ShaderManager& shaderManager)
{
    constexpr int width = 2048;
    constexpr int height = 2048;

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

    this->id = createEmptyCubeTexture(width, height);

    // Render the cube 6 times, one for each face and save the result in a texture for the cubemap
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 viewMatrices[] = {
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
    };

    RenderContext renderContext(*shaderManager.requireShaderProgram("cubemap"));
    renderContext.setProjectionMatrix(projectionMatrix);
    renderContext.getUniform("equirectangularMap").set(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hdrTexture);

    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

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

    Mesh cube;
    cube.setVertices(vertices);
    cube.setIndices(indices);

    for (unsigned int i = 0; i < 6; ++i)
    {
        renderContext.setViewMatrix(viewMatrices[i]);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, id, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube.render(renderContext);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void hs::Cubemap::convolute(ShaderManager& shaderManager)
{
    constexpr int width = 32;
    constexpr int height = 32;

    convolutedId = createEmptyCubeTexture(width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 viewMatrices[] = {
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
    };

    RenderContext renderContext(*shaderManager.requireShaderProgram("irradiance"));
    renderContext.setProjectionMatrix(projectionMatrix);
    renderContext.getUniform("cubeMap").set(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

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

    Mesh cube;
    cube.setVertices(vertices);
    cube.setIndices(indices);

    for (unsigned int i = 0; i < 6; ++i)
    {
        renderContext.setViewMatrix(viewMatrices[i]);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, convolutedId, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube.render(renderContext);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
