//
// Created by Alberto Elorza Rubio on 11/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MACHININGOPERATION_H
#define HETEROGENEOUS_SOLIDS_MACHININGOPERATION_H

#include <vector>
#include <memory>
#include <array>
#include <map>
#include <string>
#include <glm/vec3.hpp>
#include "processes/MachiningProcess.h"

namespace hs {

    using MachiningProcessCollection = const std::array<std::unique_ptr<MachiningProcess>, 14>;

    class MachiningOperation {
    public:
        const static MachiningProcessCollection processes;

        MachiningOperation();
        MachiningOperation(const MachiningOperation&) = default;
        ~MachiningOperation() = default;

        [[nodiscard]] MachiningProcess::Params& getMachiningParams();
        [[nodiscard]] MachiningProcess& getMachiningProcess() const;
        void setMachiningProcess(MachiningProcess& machiningProcess);
        void setMachiningProcess(std::string machiningProcessName);

        std::vector<std::array<glm::vec3, 64>> subTrimmedCell();

    private:
        std::reference_wrapper<MachiningProcess> machiningProcess;
        MachiningProcess::Params machiningParams;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MACHININGOPERATION_H
