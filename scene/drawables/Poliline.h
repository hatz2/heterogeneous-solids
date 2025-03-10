//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_POLILINE_H
#define HETEROGENEOUS_SOLIDS_POLILINE_H

#include <vector>
#include <glm/glm.hpp>
#include "../objects/SceneNode.h"
#include "Drawable.h"

namespace hs {

    class Poliline: public Drawable {
    public:
        Poliline();
        Poliline(std::vector<glm::vec3> vertices, bool closed);
        ~Poliline();

        Poliline(const Poliline&) = delete;

        void setPoliline(std::vector<glm::vec3> vertices, bool closed);

        void drawLines();
        void render(RenderContext& renderContext) override;
    private:
        GLuint idVAO;

        GLuint idIBO;
        size_t indexCount;

        GLuint idVBO;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_POLILINE_H
