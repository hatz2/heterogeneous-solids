//
// Created by Alberto Elorza Rubio on 29/11/2023.
//

#include "Material.h"

#include <utility>

namespace hs {
    Material::Material() :
        Material(glm::vec3(0.2), glm::vec3(0.5), glm::vec3(0.5), 16, 0, 0)
    {

    }

    Material::Material(glm::vec3 kA, glm::vec3 kD, glm::vec3 kS, float shininess) :
        Material(kA, kD, kS, shininess, 0.0f, 0.0f)
    {

    }

    Material::Material(glm::vec3 kA, glm::vec3 kD, glm::vec3 kS, float shininess, float roughness, float metallic) :
            kA(kA), kD(kD), kS(kS), shininess(shininess), roughness(roughness), metallic(metallic), description(std::make_unique<DescriptionPropImpl>("Material"))
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

    const float Material::getRoughness() const {
        return roughness;
    }

    void Material::setRoughness(float roughness) {
        Material::roughness = roughness;
    }

    const float Material::getMetallic() const {
        return metallic;
    }

    void Material::setMetallic(float metallic) {
        Material::metallic = metallic;
    }

    DescriptionProp& Material::getDescriptionProp() const {
        return *description;
    }
} // hs