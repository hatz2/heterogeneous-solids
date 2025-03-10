//
// Created by Alberto Elorza Rubio on 13/03/2024.
//

#include "SetCoefA0Command.h"

namespace hs {
    SetCoefA0Command::SetCoefA0Command(MaterialCoef& materialCoef, float a0) :
        materialCoef(materialCoef), oldA0(materialCoef.getA0()), newA0(a0)
    {

    }

    void SetCoefA0Command::execute() {
        materialCoef.setA0(newA0);
    }

    void SetCoefA0Command::undo() {
        materialCoef.setA0(oldA0);
    }

    const std::string& SetCoefA0Command::getDescription() {
        return description;
    }

    bool SetCoefA0Command::doDiscard() {
        return glm::epsilonEqual(newA0, oldA0, glm::epsilon<float>());
    }

    bool SetCoefA0Command::merge(SetCoefA0Command& other) {
        if (&materialCoef == &other.materialCoef) {
            newA0 = other.newA0;
            return true;
        }
        return false;
    }

    const std::string SetCoefA0Command::description = "Update cell coefficient A0";
} // hs