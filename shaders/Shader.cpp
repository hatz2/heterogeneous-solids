//
// Created by Alberto Elorza Rubio on 21/11/2023.
//

#include "Shader.h"
#include "ShaderError.h"

#include <memory>

namespace hs {
    Shader::Shader() : Shader(GL_VERTEX_SHADER) {

    }

    Shader::Shader(GLenum type) : Shader(type, std::string()) {

    }

    Shader::Shader(GLenum type, std::string source) :
        name("Unknown Shader"),
        id(glCreateShader(type)), type(type), source(std::move(source)), compiled(false)
    {

    }

    Shader::~Shader() {
        if (id) glDeleteShader(id);
    }

    void Shader::setName(const std::string& name) {
        Shader::name = name;
    }

    const std::string& Shader::getName() {
        return name;
    }

    GLenum Shader::getType() const {
        return type;
    }

    void Shader::setSource(std::string source) {
        if (Shader::source == source) return;

        Shader::source = std::move(source);

        compiled = false;
    }

    std::string Shader::getSource() const {
        return source;
    }

    bool Shader::isCompiled() const {
        return compiled;
    }

    void Shader::compile() {
        if (compiled) return;

        const GLchar* sourceCStr = Shader::source.c_str();
        glShaderSource(id, 1, &sourceCStr, nullptr);
        glCompileShader(id);
        GLint compileResult = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &compileResult);
        if (compileResult == GL_FALSE) {
            GLint logLen = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
            std::string compileError = "Unknown";
            if (logLen > 0) {
                auto cLog = std::make_unique<char[]>(logLen);
                glGetShaderInfoLog(id, logLen, nullptr, cLog.get());
                compileError = cLog.get();
            }
            throw ShaderError::ShaderCompileError(name, compileError);
        }
        compiled = true;
    }

    void Shader::requireCompile() {
        compiled = false;
    }

    GLuint Shader::getId() const {
        return id;
    }
} // hs