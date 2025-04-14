//
// Created by alext on 14/04/2025.
//

#include "Cubemap.h"
#include <stb_image.h>
#include <GL/glew.h>
#include <spdlog/spdlog.h>

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
        }
        else
        {
            spdlog::error("Cubemap texture load failed on file: {}", faces[i]);
        }

        stbi_image_free(imageData);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void hs::Cubemap::apply(RenderContext& renderContext) const
{
    renderContext.getUniform("cubemap").set(id);
}

int hs::Cubemap::getId() const
{
    return id;
}
