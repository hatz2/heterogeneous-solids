//
// Created by Alberto Elorza Rubio on 25/01/2024.
//

#include "ShaderError.h"

namespace hs {
    ShaderError::ShaderError(const char* const message) : std::runtime_error(message) {

    }

    ShaderError::ShaderError(const std::string& message) : std::runtime_error(message.c_str()) {

    }

    ShaderError ShaderError::ShaderCompileError(const std::string& shader, const std::string& message) {
        return ShaderError(std::string("Error compiling shader (") + shader + "): " + message);
    }

    ShaderError ShaderError::ShaderLinkError(const std::string& program, const std::string& message) {
        return ShaderError(std::string("Error linking shader (") + program + "): " + message);
    }

    ShaderError ShaderError::SubroutineError(const std::string& program, const std::string& message) {
        return ShaderError(std::string("Subroutine error (") + program + "): " + message);
    }

    ShaderError ShaderError::UniformError(
        const std::string& program, const std::string& uniform, const std::string& message
    ) {
        return ShaderError(std::string("Uniform error (") + program + ":" + uniform + "): " + message);
    }
} // hs