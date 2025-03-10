//
// Created by Alberto Elorza Rubio on 06/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_MACHININGPARAMBOUNDSERROR_H
#define HETEROGENEOUS_SOLIDS_MACHININGPARAMBOUNDSERROR_H

#include <stdexcept>

namespace hs {

    class MachiningParamBoundsError: public std::runtime_error {
    public:
        MachiningParamBoundsError(int value, int min, int max);
        MachiningParamBoundsError(float value, float min, float max);

        [[nodiscard]] const char* what() const noexcept override;
    private:
        std::string message;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MACHININGPARAMBOUNDSERROR_H
