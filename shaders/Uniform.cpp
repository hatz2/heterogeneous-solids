//
// Created by Alberto Elorza Rubio on 22/11/2023.
//

#include "Uniform.h"
#include "ShaderError.h"

namespace hs {

    Uniform::Uniform(GLint location, ShaderProgram& shaderProgram) : location(location), shaderProgram(shaderProgram) {

    }

    Uniform::Uniform(const std::string& name, ShaderProgram& shaderProgram) : shaderProgram(shaderProgram), location(0) {
        location = glGetUniformLocation(shaderProgram.getId(), name.c_str());
        if (location < 0)
            throw ShaderError::UniformError(shaderProgram.getName(), name, "Not found");
    }

    Uniform& Uniform::operator=(const Uniform& other) {
        if (this != &other) {
            this->shaderProgram = other.shaderProgram;
            this->location = other.location;
        }
        return *this;
    }

    void Uniform::set(glm::mat4 data) {
        glProgramUniformMatrix4fv(shaderProgram.get().getId(), location, 1, false, glm::value_ptr(data));
    }

    void Uniform::set(glm::vec3 data) {
        glProgramUniform3fv(shaderProgram.get().getId(), location, 1, glm::value_ptr(data));
    }

    void Uniform::set(glm::ivec3 data) {
        glProgramUniform3iv(shaderProgram.get().getId(), location, 1, glm::value_ptr(data));
    }

    void Uniform::set(glm::vec4 data) {
        glProgramUniform4fv(shaderProgram.get().getId(), location, 1, glm::value_ptr(data));
    }

    void Uniform::set(float data) {
        glProgramUniform1f(shaderProgram.get().getId(), location, data);
    }

    void Uniform::set(int data) {
        glProgramUniform1i(shaderProgram.get().getId(), location, data);
    }

    void Uniform::set(float* data, size_t size) {
        glProgramUniform1fv(shaderProgram.get().getId(), location, (int)size, data);
    }

    void Uniform::set(glm::vec3* data, size_t size) {
        glProgramUniform3fv(shaderProgram.get().getId(), location, (int)size, &data[0].x);
    }

} // hs