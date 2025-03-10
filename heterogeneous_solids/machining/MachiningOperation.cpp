//
// Created by Alberto Elorza Rubio on 11/12/2023.
//

#include "MachiningOperation.h"
#include "processes/MachiningProcessNone.h"
#include "processes/MachiningProcessCut.h"
#include "processes/MachiningProcess3ZoneSplit.h"
#include "processes/MachiningProcessSplit.h"
#include "processes/MachiningProcessHole.h"
#include "processes/MachiningProcessTaper.h"
#include "processes/MachiningProcessSmoothStep.h"
#include "processes/MachiningProcessHoleRing.h"
#include "processes/MachiningProcessQuarterTube.h"
#include "processes/MachiningProcessGearTeeth.h"
#include "processes/MachiningProcessRoundedEdge.h"
#include "processes/MachiningProcessRoundedEdgeRing.h"
#include "processes/MachiningProcessRotation.h"
#include "processes/MachiningProcessChild.h"

namespace hs {
    MachiningProcessCollection MachiningOperation::processes = {
        std::make_unique<MachiningProcessNone>(),
        std::make_unique<MachiningProcessCut>(),
        std::make_unique<MachiningProcess3ZoneSplit>(),
        std::make_unique<MachiningProcessSplit>(),
        std::make_unique<MachiningProcessHole>(),
        std::make_unique<MachiningProcessHoleRing>(),
        std::make_unique<MachiningProcessTaper>(),
        std::make_unique<MachiningProcessSmoothStep>(),
        std::make_unique<MachiningProcessQuarterTube>(),
        std::make_unique<MachiningProcessGearTeeth>(),
        std::make_unique<MachiningProcessRoundedEdge>(),
        std::make_unique<MachiningProcessRoundedEdgeRing>(),
        std::make_unique<MachiningProcessRotation>(),
        std::make_unique<MachiningProcessChild>(),
    };

    MachiningOperation::MachiningOperation() :
        machiningProcess(*processes[0]), machiningParams()
    {
        for (const auto& process : processes) {
            auto& defaultParams = process->defaultParams();
            machiningParams.insert(defaultParams.begin(), defaultParams.end());
        }
    }

    MachiningProcess::Params& MachiningOperation::getMachiningParams() {
        return machiningParams;
    }

    MachiningProcess& MachiningOperation::getMachiningProcess() const {
        return machiningProcess;
    }

    void MachiningOperation::setMachiningProcess(MachiningProcess& machiningProcess) {
        MachiningOperation::machiningProcess = std::ref(machiningProcess);
    }

    void MachiningOperation::setMachiningProcess(std::string machiningProcessName) {
        for (const auto& process : processes) {
            if (machiningProcessName == process->name()) {
                MachiningOperation::machiningProcess = *process;
            }
        }
    }

    std::vector<std::array<glm::vec3, 64>> MachiningOperation::subTrimmedCell() {
        return machiningProcess.get().subTrimmedCell(machiningParams);
    }
} // hs