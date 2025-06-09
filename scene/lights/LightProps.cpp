//
// Created by Alberto Elorza Rubio on 29/11/2023.
//

#include <glm/ext/scalar_constants.hpp>
#include "LightProps.h"

namespace hs {
    LightProps::LightProps() : iA(1), iD(1), iS(1), position(0), lookAt(0), gamma(glm::pi<float>()/3), shadow(false) {

    }

    LightProps::LightProps(
        glm::vec3 iA, glm::vec3 iD, glm::vec3 iS, glm::vec3 position, glm::vec3 lookAt, float gamma, bool shadow
    ) : iA(iA), iD(iD), iS(iS), position(position), lookAt(lookAt), gamma(gamma), shadow(shadow) {

    }

    glm::vec3 LightProps::getIA() const {
        return iA;
    }

    void LightProps::setIA(glm::vec3 iA) {
        LightProps::iA = iA;
    }

    glm::vec3 LightProps::getID() const {
        return iD;
    }

    void LightProps::setID(glm::vec3 iD) {
        LightProps::iD = iD;
    }

    glm::vec3 LightProps::getIS() const {
        return iS;
    }

    void LightProps::setIS(glm::vec3 iS) {
        LightProps::iS = iS;
    }

    glm::vec3 LightProps::getPosition() const {
        return position;
    }

    void LightProps::setPosition(glm::vec3 p) {
        LightProps::position = p;
    }

    glm::vec3 LightProps::getLookAt() const {
        return lookAt;
    }

    void LightProps::setLookAt(glm::vec3 d) {
        LightProps::lookAt = d;
    }

    float LightProps::getGamma() const {
        return gamma;
    }

    void LightProps::setGamma(float gamma) {
        LightProps::gamma = gamma;
    }

    bool LightProps::isShadow() const
    {
        return shadow;
    }

    void LightProps::setShadow(bool shadow)
    {
        this->shadow = shadow;
    }
} // hs