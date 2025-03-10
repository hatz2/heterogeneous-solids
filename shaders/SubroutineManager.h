//
// Created by Alberto Elorza Rubio on 23/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SUBROUTINEMANAGER_H
#define HETEROGENEOUS_SOLIDS_SUBROUTINEMANAGER_H

#include <memory>
#include "ShaderProgram.h"

namespace hs {

    class SubroutineManager {
    private:
        ShaderProgram& shaderProgram;
        std::unique_ptr<GLuint[]> subroutines;
        GLenum shader;
        GLint subroutineCount;

    public:
        SubroutineManager(ShaderProgram& shaderProgram, GLenum shader);
        SubroutineManager(const SubroutineManager&) = delete;

        void setSubroutine(const std::string& subroutine, const std::string& function);

        void applySubroutines();
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SUBROUTINEMANAGER_H
