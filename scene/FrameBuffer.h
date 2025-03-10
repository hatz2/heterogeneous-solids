//
// Created by Alberto Elorza Rubio on 13/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_FRAMEBUFFER_H
#define HETEROGENEOUS_SOLIDS_FRAMEBUFFER_H

#include <GL/glew.h>
#include <memory>
#include <tuple>
#include "../utils/MapCache.h"

namespace hs {

    class FrameBuffer {
    public:
        FrameBuffer(GLint width, GLint height, bool multisampled = false);
        ~FrameBuffer();

        [[nodiscard]] GLuint getId() const;
        [[nodiscard]] GLuint getTextureId() const;
        [[nodiscard]] GLint getHeight() const;
        [[nodiscard]] GLint getWidth() const;
        [[nodiscard]] float getAspect() const;

        void begin() const;
        void end() const;

        void copyTo(const FrameBuffer& target) const;

        static std::shared_ptr<FrameBuffer> getSharedFrameBuffer(GLint width, GLint height, bool multisampled = false);
    private:
        GLuint frameBufferId;
        GLuint textureId;
        GLuint renderBufferId;

        GLint width;
        GLint height;

        static MapCache<std::shared_ptr<FrameBuffer>, std::tuple<unsigned int, unsigned int, bool>> sharedFrameBuffers;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_FRAMEBUFFER_H
