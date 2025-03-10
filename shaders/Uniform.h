//
// Created by Alberto Elorza Rubio on 22/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_UNIFORM_H
#define HETEROGENEOUS_SOLIDS_UNIFORM_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <array>

#include "ShaderProgram.h"

namespace hs {

    class Uniform {
    public:
        Uniform(GLint location, ShaderProgram& shaderProgram);
        Uniform(const std::string& name, ShaderProgram& shaderProgram);
        ~Uniform() = default;
        Uniform(const Uniform&) = default;

        Uniform& operator=(const Uniform& other);

        void set(glm::mat4);
        void set(glm::vec3);
        void set(glm::ivec3);
        void set(glm::vec4);
        void set(float);
        void set(int);

        void set(float* data, size_t size);
        void set(glm::vec3* data, size_t size);
    private:
        std::reference_wrapper<ShaderProgram> shaderProgram;
        GLint location;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_UNIFORM_H
