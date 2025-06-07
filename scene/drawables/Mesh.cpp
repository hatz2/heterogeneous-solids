//
// Created by Alberto Elorza Rubio on 21/11/2023.
//

#include "Mesh.h"

#include <GL/glew.h>

namespace hs {
    Mesh::Mesh() : idVAO(0), idIBO(0), indexCount(0), idVBOVertex(0), idVBONormal(0), idVBOUVW(0) {
        glGenVertexArrays(1, &idVAO);
    }

    Mesh::Mesh(
        const std::vector<GLuint>& indices,
        const std::vector<glm::vec3>& vertices
    ) : Mesh() {
        setIndices(indices);
        setVertices(vertices);
    }

    Mesh::Mesh(
        const std::vector<GLuint>& indices,
        const std::vector<glm::vec3>& vertices,
        const std::vector<glm::vec3>& normals
    ) : Mesh() {
        setIndices(indices);
        setVertices(vertices);
        setNormals(normals);
    }

    Mesh::Mesh(
        const std::vector<GLuint>& indices,
        const std::vector<glm::vec3>& vertices,
        const std::vector<glm::vec3>& normals,
        const std::vector<glm::vec3>& uvw
    ) : Mesh() {
        setIndices(indices);
        setVertices(vertices);
        setNormals(normals);
        setUVW(uvw);
    }

    Mesh::~Mesh() {
        if (idVAO) glDeleteVertexArrays(1, &idVAO);
        if (idVBOVertex) glDeleteBuffers(1, &idVBOVertex);
        if (idVBONormal) glDeleteBuffers(1, &idVBONormal);
        if (idVBOUVW) glDeleteBuffers(1, &idVBOUVW);
        if (idIBO) glDeleteBuffers(1, &idIBO);
    }

    void Mesh::setIndices(const std::vector<GLuint>& indices) {
        glBindVertexArray(idVAO);

        indexCount = indices.size();

        if (!idIBO) glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    void Mesh::setVertices(const std::vector<glm::vec3>& vertices) {
        setVBO(idVBOVertex, VBO_VERTEX_ATTRIB_INDEX, vertices);
    }

    void Mesh::setNormals(const std::vector<glm::vec3>& normals) {
        setVBO(idVBONormal, VBO_NORMAL_ATTRIB_INDEX, normals);
    }

    void Mesh::setUVW(const std::vector<glm::vec3>& uvw) {
        setVBO(idVBOUVW, VBO_UVW_ATTRIB_INDEX, uvw);
    }

    void Mesh::drawTriangles() const {
        glBindVertexArray(idVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void Mesh::render(RenderContext& renderContext) {
        if (
            renderContext.getRenderMode() != RenderMode::Surfaces &&
            renderContext.getRenderMode() != RenderMode::SurfaceSelectColor &&
            renderContext.getRenderMode() != RenderMode::SurfaceWithoutMaterial
        )
            return;
        drawTriangles();
    }

    const GLuint Mesh::VBO_VERTEX_ATTRIB_INDEX = 0;
    const GLuint Mesh::VBO_NORMAL_ATTRIB_INDEX = 1;
    const GLuint Mesh::VBO_UVW_ATTRIB_INDEX = 2;

    void Mesh::setVBO(GLuint &idVBO, GLuint index, const std::vector<glm::vec3>& data) {
        glBindVertexArray(idVAO);
        if (!idVBO) glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(index);
    }
} // hs