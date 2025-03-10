//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_NORMALFIELD_H
#define HETEROGENEOUS_SOLIDS_NORMALFIELD_H

#include <vector>
#include <glm/glm.hpp>
#include "../objects/SceneNode.h"
#include "Drawable.h"

namespace hs {

    class NormalField: public Drawable {
    public:
        NormalField();
        NormalField(std::vector<glm::vec3> origins, std::vector<glm::vec3> directions);
        ~NormalField();

        NormalField(const NormalField&) = delete;

        void setNormalField(std::vector<glm::vec3> origins, std::vector<glm::vec3> directions);

        void drawLines();
        void render(RenderContext &renderContext) override;
    private:
        GLuint idVAO;

        GLuint idIBO;
        size_t indexCount;

        GLuint idVBO;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_NORMALFIELD_H
