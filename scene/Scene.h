//
// Created by Alberto Elorza Rubio on 18/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SCENE_H
#define HETEROGENEOUS_SOLIDS_SCENE_H

#include <memory>
#include "Camera.h"
#include "objects/GroupNode.h"
#include "../shaders/ShaderProgram.h"
#include "drawables/Mesh.h"
#include "lights/LightSet.h"

namespace hs {

    class Scene {
    public:
        Scene();

        [[nodiscard]] Camera& getCamera() const;
        [[nodiscard]] GroupNode& getRoot() const;
        [[nodiscard]] LightSet& getLights() const;
        [[nodiscard]] Mesh& getSkybox() const;

        void setSelectedObject(SceneNode& object);
        void unsetSelectedObject();
        [[nodiscard]] SceneNode& getSelectedObject() const;
    private:
        // OBJECTS
        std::unique_ptr<Camera> camera;
        std::unique_ptr<GroupNode> root;
        std::unique_ptr<LightSet> lights;
        std::unique_ptr<Mesh> skybox;

        // BEHAVIOUR
        std::reference_wrapper<SceneNode> selectedObject;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SCENE_H
