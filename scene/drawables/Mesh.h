//
// Created by Alberto Elorza Rubio on 21/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MESH_H
#define HETEROGENEOUS_SOLIDS_MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../objects/SceneNode.h"
#include "Drawable.h"

namespace hs {

    class Mesh: public Drawable {
    public:
        Mesh();
        Mesh(
            const std::vector<GLuint>& indices,
            const std::vector<glm::vec3>& vertices
        );
        Mesh(
            const std::vector<GLuint>& indices,
            const std::vector<glm::vec3>& vertices,
            const std::vector<glm::vec3>& normals
        );
        Mesh(
            const std::vector<GLuint>& indices,
            const std::vector<glm::vec3>& vertices,
            const std::vector<glm::vec3>& normals,
            const std::vector<glm::vec3>& uvw
        );
        ~Mesh();

        Mesh(const Mesh&) = delete;

        void setIndices(const std::vector<GLuint>& indices);
        void setVertices(const std::vector<glm::vec3>& vertices);
        void setNormals(const std::vector<glm::vec3>& normals);
        void setUVW(const std::vector<glm::vec3>& uvw);

        void drawTriangles() const;
        void render(RenderContext& renderContext) override;
    private:
        GLuint idVAO;

        GLuint idIBO;
        size_t indexCount;

        GLuint idVBOVertex;
        GLuint idVBONormal;
        GLuint idVBOUVW;

        static const GLuint VBO_VERTEX_ATTRIB_INDEX;
        static const GLuint VBO_NORMAL_ATTRIB_INDEX;
        static const GLuint VBO_UVW_ATTRIB_INDEX;

        void setVBO(GLuint& idVBO, GLuint index, const std::vector<glm::vec3>& data);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MESH_H
