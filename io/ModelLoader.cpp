//
// Created by Alberto Elorza Rubio on 12/02/2024.
//

#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace hs {
    ModelLoader::ModelLoader(Resources& resources) : resources(resources) {

    }

    std::optional<std::unique_ptr<Mesh>> ModelLoader::loadModel(const std::string& name) {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(
            "./resources/models/" + name,
            aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices
        );

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            spdlog::error("Error loading .obj file: {}", importer.GetErrorString());
            return std::nullopt;
        }

        std::vector<GLuint> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;

        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            const aiMesh* mesh = scene->mMeshes[i];
            for (unsigned int vi = 0; vi < mesh->mNumVertices; vi++) {
                vertices.emplace_back(mesh->mVertices[vi].x, mesh->mVertices[vi].y, mesh->mVertices[vi].z);
                normals.emplace_back(mesh->mNormals[vi].x, mesh->mNormals[vi].y, mesh->mNormals[vi].z);
            }
            for (unsigned int fi = 0; fi < mesh->mNumFaces; fi++) {
                for (unsigned int fii = 0; fii < mesh->mFaces[fi].mNumIndices; fii++) {
                    indices.push_back(mesh->mFaces[fi].mIndices[fii]);
                }
            }
        }

        auto output = std::make_unique<Mesh>(indices, vertices, normals);

        importer.FreeScene();

        return output;
    }
} // hs