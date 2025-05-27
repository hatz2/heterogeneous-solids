//
// Created by alext on 27/05/2025.
//

#ifndef BUILDER_H
#define BUILDER_H

#include <functional>
#include "Data.h"
#include "../../shaders/ShaderManager.h"

namespace hs::ibl
{
    class Builder
    {
    public:
        [[nodiscard]] Data getResult() const { return result; };

        virtual Builder& generateEnvironmentMap(const int size = 2048) = 0;
        virtual Builder& generateIrradianceMap(const int size = 32) = 0;
        virtual Builder& generatePrefilteredMap(const int size) = 0;
        virtual Builder& generateBrdfLUT(const int size) = 0;

    protected:
        explicit Builder(const std::string& path, ShaderManager& shaderManager)
            : hdrTexturePath(path), shaderManager(shaderManager) {};

        Data result;
        const std::string& hdrTexturePath;
        std::reference_wrapper<ShaderManager> shaderManager;


    };
}

#endif //BUILDER_H
