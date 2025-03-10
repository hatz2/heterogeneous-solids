//
// Created by Alberto Elorza Rubio on 29/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MATERIAL_H
#define HETEROGENEOUS_SOLIDS_MATERIAL_H

#include <glm/glm.hpp>
#include "RenderContext.h"
#include "../utils/props.h"

namespace hs {

    class Material {
    public:
        Material();
        Material(glm::vec3 kA, glm::vec3 kD, glm::vec3 kS, float shininess);

        [[nodiscard]] const glm::vec3& getKA() const;
        void setKA(glm::vec3 kA);

        [[nodiscard]] const glm::vec3& getKD() const;
        void setKD(glm::vec3 kD);

        [[nodiscard]] const glm::vec3& getKS() const;
        void setKS(glm::vec3 kS);

        [[nodiscard]] const float& getShininess() const;
        void setShininess(float shininess);

        [[nodiscard]] DescriptionProp& getDescriptionProp() const;
    private:
        glm::vec3 kA;
        glm::vec3 kD;
        glm::vec3 kS;
        float shininess;
        std::unique_ptr<DescriptionProp> description;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MATERIAL_H
