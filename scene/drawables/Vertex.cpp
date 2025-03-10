//
// Created by Alberto Elorza Rubio on 01/01/2024.
//

#include "Vertex.h"

namespace hs {
    Vertex::Vertex(glm::vec3 position) : position(position), idVAO(0), idVBO(0) {
        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);

        setVertex(position);
    }

    Vertex::Vertex(const Vertex& other) : Vertex(other.position) {
        if (idVAO) glDeleteVertexArrays(1, &idVAO);
        if (idVBO) glDeleteBuffers(1, &idVBO);
    }

    Vertex::~Vertex() {

    }

    void Vertex::setVertex(glm::vec3 position) {
        glBindVertexArray(idVAO);

        if (!idVBO) glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), glm::value_ptr(position), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);
    }

    void Vertex::render(RenderContext& renderContext) {
        if (
            renderContext.getRenderMode() != RenderMode::Vertices &&
            renderContext.getRenderMode() != RenderMode::VertexSelectColor
        ) return;
        glBindVertexArray(idVAO);
        glDrawArrays(GL_POINTS, 0, 1);
    }

    Vertex& Vertex::getVertexInstance() {
        static Vertex vertex;
        return vertex;
    }
} // hs