//
// Created by Alberto Elorza Rubio on 12/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_MODELLOADER_H
#define HETEROGENEOUS_SOLIDS_MODELLOADER_H

#include <memory>
#include "../scene/drawables/Mesh.h"
#include "Resources.h"

namespace hs {

    class ModelLoader {
    public:
        explicit ModelLoader(Resources& resources);

        std::optional<std::unique_ptr<Mesh>> loadModel(const std::string& name);
    private:
        Resources& resources;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MODELLOADER_H
