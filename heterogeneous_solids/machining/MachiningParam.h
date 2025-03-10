//
// Created by Alberto Elorza Rubio on 16/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MACHININGPARAM_H
#define HETEROGENEOUS_SOLIDS_MACHININGPARAM_H

#include <variant>
#include <string>
#include <vector>

namespace hs {

    struct MachiningParamFloat {
        const float min;
        const float max;
        const float step;
    };

    struct MachiningParamInt {
        const int min;
        const int max;
        const int step;
    };

    struct MachiningParamEnum {
        const std::vector<const char*> options;
    } const uAxes{ { "U", "V", "W" } },
        machiningEdgeName{ { "E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "E10", "E11" } },
        isoCrvName{ { "C0", "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "C11" } };

    class MachiningParam: public std::variant<MachiningParamFloat, MachiningParamInt, MachiningParamEnum> {
    public:
        MachiningParam() = delete;
        MachiningParam(float value, const MachiningParamFloat&);
        MachiningParam(int value, const MachiningParamInt&);
        MachiningParam(int value, const MachiningParamEnum&);

        [[nodiscard]] float getValue() const;
        void set(float value);

        operator float() const;
        operator int() const;

        MachiningParam(const MachiningParam&) = default;
    private:
        float value;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MACHININGPARAM_H
