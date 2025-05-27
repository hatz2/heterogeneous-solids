//
// Created by Alberto Elorza Rubio on 18/11/2023.
//

#include "Scene.h"

#include <utility>
#include <set>

namespace hs {
    Scene::Scene():
        camera(std::make_unique<Camera>()),
        root(std::make_unique<GroupNode>()),
        lights(std::make_unique<LightSet>()),
        skybox(std::make_unique<Mesh>()),
        selectedObject(*root)
    {
        initSkybox();
    }

    Camera& Scene::getCamera() const {
        return *camera;
    }

    GroupNode& Scene::getRoot() const {
        return *root;
    }

    LightSet& Scene::getLights() const {
        return *lights;
    }

    Mesh& Scene::getSkybox() const
    {
        return *skybox;
    }

    void Scene::setSelectedObject(SceneNode& object) {
        selectedObject = std::ref(object);
    }

    void Scene::unsetSelectedObject() {
        selectedObject = *root;
    }

    SceneNode& Scene::getSelectedObject() const {
        return selectedObject;
    }

    void Scene::initSkybox()
    {
        std::vector<glm::vec3> vertices = {
            {-1.0f,  1.0f, -1.0f}, // 0
            {-1.0f, -1.0f, -1.0f}, // 1
            { 1.0f, -1.0f, -1.0f}, // 2
            { 1.0f,  1.0f, -1.0f}, // 3
            {-1.0f, -1.0f,  1.0f}, // 4
            {-1.0f,  1.0f,  1.0f}, // 5
            { 1.0f, -1.0f,  1.0f}, // 6
            { 1.0f,  1.0f,  1.0f}  // 7
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,
            2, 3, 0,

            4, 1, 0,
            0, 5, 4,

            2, 6, 7,
            7, 3, 2,

            4, 5, 7,
            7, 6, 4,

            0, 3, 7,
            7, 5, 0,

            1, 4, 2,
            2, 4, 6
        };

        skybox->setVertices(vertices);
        skybox->setIndices(indices);
    }
} // hs