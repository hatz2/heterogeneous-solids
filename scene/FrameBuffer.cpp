//
// Created by Alberto Elorza Rubio on 13/11/2023.
//

#include "FrameBuffer.h"

#include <GL/glew.h>
//#include <exception>
#include <stdexcept>

namespace hs {
    FrameBuffer::FrameBuffer(GLint width, GLint height, bool multisampled) :
        frameBufferId(0), textureId(0), renderBufferId(0), width(width), height(height)
    {

        glGenFramebuffers(1, &frameBufferId);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);

        glGenTextures(1, &textureId);
        auto target = GL_TEXTURE_2D;
        if (multisampled) {
            target = GL_TEXTURE_2D_MULTISAMPLE;
            glBindTexture(target, textureId);
            glTexImage2DMultisample(target, 4, GL_RGBA, width, height, GL_TRUE);
        } else {
            glBindTexture(target, textureId);
            glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        }
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(target, GL_GENERATE_MIPMAP, GL_TRUE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, target, textureId, 0);

        glGenRenderbuffers(1, &renderBufferId);
        glBindRenderbuffer(GL_RENDERBUFFER, renderBufferId);
        if (multisampled) glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);
        else glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferId);

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        if (status != GL_FRAMEBUFFER_COMPLETE) {
            throw std::runtime_error("FrameBuffer is not completed");
        }
    }

    FrameBuffer::~FrameBuffer() {
        glDeleteFramebuffers(1, &frameBufferId);
        glDeleteTextures(1, &textureId);
        glDeleteRenderbuffers(1, &renderBufferId);
    }

    GLuint FrameBuffer::getId() const {
        return frameBufferId;
    }

    GLuint FrameBuffer::getTextureId() const {
        return textureId;
    }

    GLint FrameBuffer::getHeight() const {
        return height;
    }

    GLint FrameBuffer::getWidth() const {
        return width;
    }

    void FrameBuffer::begin() const {
        glViewport(0, 0, width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
    }

    void FrameBuffer::end() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::copyTo(const FrameBuffer& target) const {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBufferId);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target.frameBufferId);
        glDrawBuffer(GL_BACK);
        glBlitFramebuffer(0, 0, width, height, 0, 0, target.width, target.height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    std::shared_ptr<FrameBuffer> FrameBuffer::getSharedFrameBuffer(GLint width, GLint height, bool multisampled) {
        auto initialization = std::make_tuple(width, height, multisampled);
        return sharedFrameBuffers.load_or(initialization, [initialization]() {
            return std::make_shared<FrameBuffer>(
                std::get<0>(initialization),
                std::get<1>(initialization),
                std::get<2>(initialization)
            );
        });
    }

    float FrameBuffer::getAspect() const {
        return (float)width/(float)height;
    }

    MapCache<std::shared_ptr<FrameBuffer>, std::tuple<unsigned int, unsigned int, bool>> FrameBuffer::sharedFrameBuffers;
} // hs