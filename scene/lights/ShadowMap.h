//
// Created by alext on 05/06/2025.
//

#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include <GL/glew.h>

namespace hs {

class ShadowMap {
public:
    ShadowMap(const int width = 2048, const int height = 2048);

    [[nodiscard]] GLuint getId() const { return id; }
    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }

    void render(const class Scene& scene, class ShaderManager& shaderManager, class Light& light) const;

private:
    GLuint createEmptyTexture2D(const int width, const int height);

    int width;
    int height;
    GLuint id;
    GLuint framebuffer;
};

} // hs

#endif //SHADOWMAP_H
