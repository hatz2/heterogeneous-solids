//
// Created by Alberto Elorza Rubio on 25/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SHADERERROR_H
#define HETEROGENEOUS_SOLIDS_SHADERERROR_H

#include <stdexcept>
#include <string>

namespace hs {

    class ShaderError : public std::runtime_error {
    public:
        explicit ShaderError(char const* message);
        explicit ShaderError(const std::string& message);
        ShaderError() = default;

        static ShaderError ShaderCompileError(const std::string& shader, const std::string& message);
        static ShaderError ShaderLinkError(const std::string& program, const std::string& message);
        static ShaderError SubroutineError(const std::string& program, const std::string& message);
        static ShaderError UniformError(
            const std::string& program, const std::string& uniform, const std::string& message
        );
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SHADERERROR_H
