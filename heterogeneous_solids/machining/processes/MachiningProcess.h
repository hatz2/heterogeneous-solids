//
// Created by Alberto Elorza Rubio on 11/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MACHININGPROCESS_H
#define HETEROGENEOUS_SOLIDS_MACHININGPROCESS_H

#include <array>
#include <map>
#include <string>
#include <glm/glm.hpp>
#include "../MachiningParam.h"

namespace hs {

    class MachiningProcess {
    public:
        using Params = std::map<std::string, MachiningParam>;
        using Outcome = std::vector<std::array<glm::vec3, 64>>;

        [[nodiscard]] virtual Outcome subTrimmedCell(const Params& params) const = 0;
        [[nodiscard]] virtual const Params& defaultParams() const = 0;
        [[nodiscard]] virtual const char* name() const = 0;

        MachiningProcess() = default;
        MachiningProcess(const MachiningProcess&) = delete;
        MachiningProcess& operator=(MachiningProcess&) = delete;

        virtual ~MachiningProcess() = default;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MACHININGPROCESS_H
