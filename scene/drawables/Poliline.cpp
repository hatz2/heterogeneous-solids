//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#include "Poliline.h"

#include <utility>

namespace hs {
    Poliline::Poliline() : idVAO(0), idIBO(0), indexCount(0), idVBO(0) {
        glGenVertexArrays(1, &idVAO);
    }

    Poliline::Poliline(std::vector<glm::vec3> vertices, bool closed) :
        idVAO(0), idIBO(0), indexCount(0), idVBO(0)
    {
        glGenVertexArrays(1, &idVAO);

        setPoliline(std::move(vertices), closed);
    }

    Poliline::~Poliline() {
        if (idVAO) glDeleteVertexArrays(1, &idVAO);
        if (idIBO) glDeleteBuffers(1, &idIBO);
        if (idVBO) glDeleteBuffers(1, &idVBO);
    }

    void Poliline::setPoliline(std::vector<glm::vec3> vertices, bool closed) {
        glBindVertexArray(idVAO);

        if (!idVBO) glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        // TODO: Consider not always generate IBO

        std::vector<GLuint> indices;
        for (int i = 0; i < vertices.size() - 1; i++) {
            indices.push_back(i);
            indices.push_back(i + 1);
        }
        if (closed) {
            indices.push_back(vertices.size() - 1);
            indices.push_back(0);
        }
        indexCount = indices.size();

        if (!idIBO) glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    void Poliline::drawLines() {
        glBindVertexArray(idVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glDrawElements(GL_LINE_STRIP, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void Poliline::render(RenderContext& renderContext) {
        if (renderContext.getRenderMode() != RenderMode::Lines) return;
        drawLines();
    }
} // hs