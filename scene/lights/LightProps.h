//
// Created by Alberto Elorza Rubio on 29/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_LIGHTPROPS_H
#define HETEROGENEOUS_SOLIDS_LIGHTPROPS_H

#include <glm/glm.hpp>

namespace hs {

    class LightProps {
    private:
        glm::vec3 iA;
        glm::vec3 iD;
        glm::vec3 iS;
        glm::vec3 position;
        glm::vec3 lookAt;
        float gamma;
        bool shadow;
    public:
        LightProps();
        LightProps(
            glm::vec3 iA, glm::vec3 iD, glm::vec3 iS,
            glm::vec3 position, glm::vec3 lookAt, float gamma,
            bool shadow
        );
        LightProps(const LightProps&) = default;
        LightProps& operator=(const LightProps&) = default;

        [[nodiscard]] glm::vec3 getIA() const;
        void setIA(glm::vec3 iA);

        [[nodiscard]] glm::vec3 getID() const;
        void setID(glm::vec3 iD);

        [[nodiscard]] glm::vec3 getIS() const;
        void setIS(glm::vec3 iS);

        [[nodiscard]] glm::vec3 getPosition() const;
        void setPosition(glm::vec3 p);

        [[nodiscard]] glm::vec3 getLookAt() const;
        void setLookAt(glm::vec3 d);

        [[nodiscard]] float getGamma() const;
        void setGamma(float gamma);

        [[nodiscard]] bool isShadow() const;
        void setShadow(bool shadow);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_LIGHTPROPS_H
