//
// Created by alext on 27/05/2025.
//

#ifndef BUILDERIMP_H
#define BUILDERIMP_H

#include "Builder.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "../drawables/Mesh.h"

namespace hs::ibl
{
    class BuilderImp : public Builder {
    public:
        explicit BuilderImp(const std::string& hdrPath, ShaderManager& shaderManager);
        virtual ~BuilderImp();

        Builder& generateEnvironmentMap(const int size= 2048) override;
        Builder& generateIrradianceMap(const int size = 32) override;
        Builder& generatePrefilteredMap(const int size = 2048) override;
        Builder& generateBrdfLUT(const int size = 512) override;

    private:
        void initBuffers();
        void initMatrices();
        void initCube();
        void loadHdrTexture();
        GLuint createEmptyCubeTexture(const int size, bool lod = false) const;

        GLuint frameBuffer = 0;
        GLuint renderBuffer = 0;
        GLuint hdrTexture = 0;
        glm::mat4 projectionMatrix;
        std::vector<glm::mat4> viewMatrices;
        Mesh cube;

    };
}





#endif //BUILDERIMP_H
