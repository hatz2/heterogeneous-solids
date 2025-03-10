//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#include "NormalField.h"

namespace hs {
    NormalField::NormalField() : idVAO(0), idIBO(0), indexCount(0), idVBO(0) {
        glGenVertexArrays(1, &idVAO);
    }

    NormalField::NormalField(std::vector<glm::vec3> origins, std::vector<glm::vec3> directions) :
        idVAO(0), idIBO(0), indexCount(0), idVBO(0)
    {
        glGenVertexArrays(1, &idVAO);

        setNormalField(std::move(origins), std::move(directions));
    }

    NormalField::~NormalField() {
        if (idVAO) glDeleteVertexArrays(1, &idVAO);
        if (idIBO) glDeleteBuffers(1, &idIBO);
        if (idVBO) glDeleteBuffers(1, &idVBO);
    }

    void NormalField::setNormalField(std::vector<glm::vec3> origins, std::vector<glm::vec3> directions) {
        if (origins.size() != directions.size())
            throw std::runtime_error("[NormalField] origins and directions with different size");

        glBindVertexArray(idVAO);

        for (int i = 0; i < origins.size(); i++)
            directions[i] = origins[i] + directions[i];

        size_t size = origins.size() * sizeof(glm::vec3);

        if (!idVBO) glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, size * 2, nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, origins.data());
        glBufferSubData(GL_ARRAY_BUFFER, size, size, directions.data());
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        std::vector<GLuint> indices;
        for (int i = 0; i < origins.size(); i++) {
            indices.push_back(i);
            indices.push_back(i + origins.size());
        }
        indexCount = indices.size();

        if (!idIBO) glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    void NormalField::drawLines() {
        glBindVertexArray(idVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void NormalField::render(RenderContext &renderContext) {
        if (renderContext.getRenderMode() != RenderMode::Normals) return;
        drawLines();
    }
} // hs