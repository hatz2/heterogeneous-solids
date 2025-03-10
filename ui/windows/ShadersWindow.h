//
// Created by Alberto Elorza Rubio on 24/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SHADERSWINDOW_H
#define HETEROGENEOUS_SOLIDS_SHADERSWINDOW_H

#include <memory>
#include "../core/Window.h"
#include "../../shaders/ShaderManager.h"

namespace hs {

    class ShadersWindow: public Window {
    public:
        ShadersWindow(std::string name, ShaderManager& shaderManager);
    protected:
        void renderBody() override;
    private:
        ShaderManager& shaderManager;
        std::optional<ShaderProgramSources> sources;
        std::optional<std::string> selected;

        // Window height calculus
        float height;
        float remain;
        int count;

        void renderShaderType(std::vector<ShaderSource>& sources);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SHADERSWINDOW_H
