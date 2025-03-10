//
// Created by Alberto Elorza Rubio on 21/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SHADER_H
#define HETEROGENEOUS_SOLIDS_SHADER_H

#include <GL/glew.h>
#include <string>
#include <memory>
#include <vector>

namespace hs {

    class Shader {
    private:
        std::string name;
        GLuint id;
        GLenum type;
        std::string source;
        bool compiled;
    public:
        Shader();
        explicit Shader(GLenum type);
        Shader(GLenum type, std::string source);
        Shader(const Shader&) = delete;
        ~Shader();

        void setName(const std::string& name);
        [[nodiscard]] const std::string& getName();

        [[nodiscard]] GLenum getType() const;

        void setSource(std::string source);
        [[nodiscard]] std::string getSource() const;

        [[nodiscard]] bool isCompiled() const;

        void compile();
        void requireCompile();
        [[nodiscard]] GLuint getId() const;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SHADER_H
