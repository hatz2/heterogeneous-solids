//
// Created by Alberto Elorza Rubio on 03/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_IO_H
#define HETEROGENEOUS_SOLIDS_IO_H

#include <memory>
#include "dialogs/DialogsFacade.h"
#include "ModelLoader.h"
#include "Resources.h"
#include "../shaders/ShaderManager.h"

namespace hs {

    class IO {
    public:
        explicit IO(Resources resources);
        IO(const IO&) = delete;

        [[nodiscard]] const Resources& getResources() const;
        [[nodiscard]] DialogsFacade& getDialogsFacade() const;
        [[nodiscard]] ShaderIO& getShaderIO() const;
        [[nodiscard]] ShaderManager& getShaderManager() const;
        [[nodiscard]] ModelLoader& getModelLoader() const;
    private:
        Resources resources;
        std::unique_ptr<DialogsFacade> dialogsFacade;
        std::unique_ptr<ShaderIO> shaderIO;
        std::unique_ptr<ShaderManager> shaderManager;
        std::unique_ptr<ModelLoader> modelLoader;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_IO_H
