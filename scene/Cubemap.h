//
// Created by alext on 14/04/2025.
//

#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <vector>
#include <string>
#include "RenderContext.h"
#include "../shaders/ShaderManager.h"

namespace hs {
    class Cubemap {
    public:
        /**
         * Order of faces:
         *
         * 1. right
         * 2. left
         * 3. top
         * 4. bottom
         * 5. front
         * 6. back
         *
         * @param faces
         */
        explicit Cubemap(const std::vector<std::string>& faces);
        explicit Cubemap(const std::string& hdrImgPath, ShaderManager& shaderManager);

        void apply(RenderContext& renderContext) const;

        [[nodiscard]] int getId() const;
        [[nodiscard]] int getConvolutedId() const;

    private:
        void initFrameBuffers();
        [[nodiscard]] unsigned int createEmptyCubeTexture(const int width, const int height);
        [[nodiscard]] unsigned int loadHdrTexture(const std::string& hdrImgPath);
        void mapHdrTextureToCubeTexture(unsigned int hdrTexture, ShaderManager& shaderManager);
        void convolute(ShaderManager& shaderManager);

        unsigned int id;
        unsigned int convolutedId;
        unsigned int frameBuffer;
        unsigned int renderBuffer;
    };
}




#endif //CUBEMAP_H
