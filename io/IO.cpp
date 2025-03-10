//
// Created by Alberto Elorza Rubio on 03/02/2024.
//

#include "IO.h"
#include "dialogs/PFDDialogs.h"
#include "../shaders/ShaderIOJSON.h"

namespace hs {
    IO::IO(Resources resources) :
        resources(std::move(resources)),
        dialogsFacade(std::make_unique<PFDDialogs>()),
        shaderIO(std::make_unique<ShaderIOJSON>(IO::resources)),
        shaderManager(std::make_unique<ShaderManager>(*IO::shaderIO)),
        modelLoader(std::make_unique<ModelLoader>(IO::resources))
    {

    }

    const Resources& IO::getResources() const {
        return resources;
    }

    DialogsFacade& IO::getDialogsFacade() const {
        return *dialogsFacade;
    }

    ShaderIO& IO::getShaderIO() const {
        return *shaderIO;
    }

    ShaderManager& IO::getShaderManager() const {
        return *shaderManager;
    }

    ModelLoader& IO::getModelLoader() const {
        return *modelLoader;
    }
} // hs