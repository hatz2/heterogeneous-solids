//
// Created by Alberto Elorza Rubio on 06/01/2024.
//

#include "MachiningParamBoundsError.h"

#include <sstream>

namespace hs {
    MachiningParamBoundsError::MachiningParamBoundsError(int value, int min, int max):std::runtime_error("") {
        std::stringstream msg;
        msg << "Machining param value outside boundaries: " << value << " must be in [" << min << ", " << max << "]";
        message = msg.str();
    }

    MachiningParamBoundsError::MachiningParamBoundsError(float value, float min, float max):std::runtime_error("") {
        std::stringstream msg;
        msg << "Machining param value outside boundaries: " << value << " must be in [" << min << ", " << max << "]";
        message = msg.str();
    }

    const char* MachiningParamBoundsError::what() const noexcept {
        return message.c_str();
    }
} // hs