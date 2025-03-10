//
// Created by Alberto Elorza Rubio on 04/04/2024.
//

#include "SetCoefContinuityCommand.h"

namespace hs {
    SetCoefContinuityCommand::SetCoefContinuityCommand(MaterialCoef& materialCoef, bool continuity) :
        materialCoef(materialCoef), oldContinuity(materialCoef.isKeepContinuity()), newContinuity(continuity) {

    }

    void SetCoefContinuityCommand::execute() {
        materialCoef.setKeepContinuity(newContinuity);
    }

    void SetCoefContinuityCommand::undo() {
        materialCoef.setKeepContinuity(oldContinuity);
    }

    const std::string& SetCoefContinuityCommand::getDescription() {
        return description;
    }

    bool SetCoefContinuityCommand::doDiscard() {
        return newContinuity == oldContinuity;
    }

    bool SetCoefContinuityCommand::merge(SetCoefContinuityCommand& other) {
        if (&materialCoef == &other.materialCoef) {
            newContinuity = other.newContinuity;
            return true;
        }
        return false;
    }

    const std::string SetCoefContinuityCommand::description = "Update cell coefficient keep continuity";
} // hs