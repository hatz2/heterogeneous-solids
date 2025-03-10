//
// Created by Alberto Elorza Rubio on 29/11/2023.
//

#include "Material.h"

#include <utility>

namespace hs {
    Material::Material() :
        kA(0.2), kD(0.5), kS(0.5), shininess(16), description(std::make_unique<DescriptionPropImpl>("Material"))
    {

    }

    Material::Material(glm::vec3 kA, glm::vec3 kD, glm::vec3 kS, float shininess) :
            kA(kA), kD(kD), kS(kS), shininess(shininess), description(std::make_unique<DescriptionPropImpl>("Material"))
    {

    }

    const glm::vec3& Material::getKA() const {
        return kA;
    }

    void Material::setKA(glm::vec3 kA) {
        Material::kA = kA;
    }

    const glm::vec3& Material::getKD() const {
        return kD;
    }

    void Material::setKD(glm::vec3 kD) {
        Material::kD = kD;
    }

    const glm::vec3& Material::getKS() const {
        return kS;
    }

    void Material::setKS(glm::vec3 kS) {
        Material::kS = kS;
    }

    const float& Material::getShininess() const {
        return shininess;
    }

    void Material::setShininess(float shininess) {
        Material::shininess = shininess;
    }

    DescriptionProp& Material::getDescriptionProp() const {
        return *description;
    }
} // hs