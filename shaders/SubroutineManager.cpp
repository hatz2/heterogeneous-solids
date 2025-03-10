//
// Created by Alberto Elorza Rubio on 23/11/2023.
//

#include "SubroutineManager.h"
#include "ShaderError.h"

namespace hs {
    SubroutineManager::SubroutineManager(ShaderProgram& shaderProgram, GLenum shader):
        shaderProgram(shaderProgram), shader(shader), subroutineCount(0) {

        SubroutineManager::shaderProgram.use(); // Prevent from not being compiled
        GLuint programId = SubroutineManager::shaderProgram.getId();

        glGetProgramStageiv(programId, shader, GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, &subroutineCount);
        subroutines = std::make_unique<GLuint[]>(subroutineCount);
    }

    void SubroutineManager::setSubroutine(const std::string& subroutine, const std::string& function) {
        GLuint programId = SubroutineManager::shaderProgram.getId();

        GLuint idx = glGetSubroutineIndex(programId, shader, function.c_str());
        if (idx == GL_INVALID_INDEX)
            throw ShaderError::SubroutineError(shaderProgram.getName(), "subroutine function not found");

        GLint location = glGetSubroutineUniformLocation(programId, shader, subroutine.c_str());
        if (location < 0)
            throw ShaderError::SubroutineError(shaderProgram.getName(), "subroutine uniform not found");

        subroutines[location] = idx;
    }

    void SubroutineManager::applySubroutines() {
        glUniformSubroutinesuiv(shader, subroutineCount, subroutines.get());
    }
} // hs