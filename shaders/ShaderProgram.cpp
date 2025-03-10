//
// Created by Alberto Elorza Rubio on 21/11/2023.
//

#include "ShaderProgram.h"
#include "ShaderError.h"

namespace hs {
    ShaderProgram::ShaderProgram() :
        name("Unknown Shader Program"),
        id(glCreateProgram()),
        vertexShader(nullptr), fragmentShader(nullptr), geometryShader(nullptr),
        linked(false)
    {

    }

    ShaderProgram::~ShaderProgram() {
        if (id) glDeleteProgram(id);
    }

    void ShaderProgram::replaceShader(std::shared_ptr<Shader>& shader, std::shared_ptr<Shader> nShader) {
        if (shader) glDetachShader(id, shader->getId());
        if (nShader) {
            shader = std::move(nShader);
            glAttachShader(id, shader->getId());
        }
        linked = false;
    }

    void ShaderProgram::setName(const std::string& name) {
        ShaderProgram::name = name;
    }

    const std::string& ShaderProgram::getName() {
        return name;
    }

    void ShaderProgram::setVertexShader(std::shared_ptr<Shader> shader) {
        replaceShader(vertexShader, std::move(shader));
    }

    std::shared_ptr<Shader> ShaderProgram::getVertexShader() const {
        return vertexShader;
    }

    void ShaderProgram::setFragmentShader(std::shared_ptr<Shader> shader) {
        replaceShader(fragmentShader, std::move(shader));
    }

    std::shared_ptr<Shader> ShaderProgram::getFragmentShader() const {
        return fragmentShader;
    }

    void ShaderProgram::setGeometryShader(std::shared_ptr<Shader> shader) {
        replaceShader(geometryShader, std::move(shader));
    }

    std::shared_ptr<Shader> ShaderProgram::getGeometryShader() const {
        return geometryShader;
    }

    void ShaderProgram::link() {
        if (linked) return;

        if (vertexShader) vertexShader->compile();
        if (fragmentShader) fragmentShader->compile();
        if (geometryShader) geometryShader->compile();

        glLinkProgram(id);
        GLint linkSuccess = 0;
        glGetProgramiv(id, GL_LINK_STATUS, &linkSuccess);
        if (linkSuccess == GL_FALSE) {
            GLint logLen = 0;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLen);
            std::string linkError = "Unknown";
            if (logLen > 0) {
                auto cLog = std::make_unique<char[]>(logLen);
                glGetProgramInfoLog(id, logLen, nullptr, cLog.get());
                linkError = cLog.get();
            }
            throw ShaderError::ShaderLinkError(name, linkError);
        }
        linked = true;
    }

    void ShaderProgram::requireLink() {
        linked = false;
    }

    GLuint ShaderProgram::getId() const {
        return id;
    }

    void ShaderProgram::use() {
        link();
        glUseProgram(getId());
    }
} // hs