//
// Created by Alberto Elorza Rubio on 12/02/2024.
//

#include "Resources.h"
#include <iostream>

namespace hs {
    Resources::Resources(const std::filesystem::path& executablePath) :
// BEWARE: in the debug mode the resources (a directory) are not in the executable directory
// IN RELEASE: the executable is in the same directory as the resources
// IN DEBUG: the executable is in a subdirectory in the same directory as the resources
#if NDEBUG
        resourcesPath(executablePath.parent_path().append("resources"))
#else
        resourcesPath(executablePath.parent_path().parent_path().append("resources"))
#endif
    {

    }

    std::filesystem::path Resources::getFont(const std::string& fontName) const {
        auto path = resourcesPath;
        return path.append("fonts").append(fontName);
    }

    std::filesystem::path Resources::getShader(const std::string& shaderName) const {
        auto path = resourcesPath;
        return path.append("shaders").append(shaderName);
    }

    std::filesystem::path Resources::getModel(const std::string& modelName) const {
        auto path = resourcesPath;
        return path.append("models").append(modelName);
    }
} // hs