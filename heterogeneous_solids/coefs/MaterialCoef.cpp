//
// Created by Alberto Elorza Rubio on 01/04/2024.
//

#include "MaterialCoef.h"

namespace hs {
    MaterialCoef::MaterialCoef(float& a0, bool keepContinuity) :
        materialCoefSync(std::make_shared<Subject<float>>()), a0(a0), keepContinuity(keepContinuity)
    {
        materialCoefSync->attachObserver(this);
    }

    MaterialCoef::~MaterialCoef() {
        materialCoefSync->detachObserver(this);
    }

    std::shared_ptr<Subject<float>> MaterialCoef::getMaterialCoefSync() {
        return materialCoefSync;
    }

    void MaterialCoef::setMaterialCoefSync(std::shared_ptr<Subject<float>> materialCoefSync) {
        MaterialCoef::materialCoefSync->detachObserver(this);
        MaterialCoef::materialCoefSync = std::move(materialCoefSync);
        MaterialCoef::materialCoefSync->attachObserver(this);
    }

    float MaterialCoef::getA0() const {
        return a0;
    }

    void MaterialCoef::setA0(float a0) {
        if (keepContinuity) materialCoefSync->updateSubject(a0);
        else MaterialCoef::a0 = a0;
    }

    bool MaterialCoef::isKeepContinuity() const {
        return keepContinuity;
    }

    void MaterialCoef::setKeepContinuity(bool keepContinuity) {
        MaterialCoef::keepContinuity = keepContinuity;
    }

    void MaterialCoef::updateObserver(float a0) {
        if (keepContinuity) MaterialCoef::a0 = a0;
    }
} // hs