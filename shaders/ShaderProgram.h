//
// Created by Alberto Elorza Rubio on 21/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SHADERPROGRAM_H
#define HETEROGENEOUS_SOLIDS_SHADERPROGRAM_H

#include <GL/glew.h>
#include <memory>
#include "Shader.h"

namespace hs {
    class ShaderProgram {
    private:
        std::string name;
        GLuint id;
        std::shared_ptr<Shader> vertexShader;
        std::shared_ptr<Shader> fragmentShader;
        std::shared_ptr<Shader> geometryShader;
        bool linked;

        void replaceShader(std::shared_ptr<Shader>& shader, std::shared_ptr<Shader> nShader);
    public:
        ShaderProgram();
        ShaderProgram(const ShaderProgram&) = default;
        ~ShaderProgram();

        void setName(const std::string& name);
        [[nodiscard]] const std::string& getName();

        void setVertexShader(std::shared_ptr<Shader> shader);
        [[nodiscard]] std::shared_ptr<Shader> getVertexShader() const;

        void setFragmentShader(std::shared_ptr<Shader> shader);
        [[nodiscard]] std::shared_ptr<Shader> getFragmentShader() const;

        void setGeometryShader(std::shared_ptr<Shader> shader);
        [[nodiscard]] std::shared_ptr<Shader> getGeometryShader() const;

        void link();
        void requireLink();
        [[nodiscard]] GLuint getId() const;
        void use();
    };
} // hs

#endif //HETEROGENEOUS_SOLIDS_SHADERPROGRAM_H
