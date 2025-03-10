//
// Created by Alberto Elorza Rubio on 01/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_VERTEX_H
#define HETEROGENEOUS_SOLIDS_VERTEX_H

#include "Drawable.h"

namespace hs {

    class Vertex: public Drawable {
    public:
        explicit Vertex(glm::vec3 position = { 0, 0, 0 });
        Vertex(const Vertex&);

        ~Vertex();

        void setVertex(glm::vec3 position);

        void render(RenderContext& renderContext) override;

        static Vertex& getVertexInstance();
    private:
        glm::vec3 position;

        GLuint idVAO;
        GLuint idVBO;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_VERTEX_H
