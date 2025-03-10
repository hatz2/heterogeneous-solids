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

        selectedObject(*root)
    {

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

    void Scene::setSelectedObject(SceneNode& object) {
        selectedObject = std::ref(object);
    }

    void Scene::unsetSelectedObject() {
        selectedObject = *root;
    }

    SceneNode& Scene::getSelectedObject() const {
        return selectedObject;
    }
} // hs