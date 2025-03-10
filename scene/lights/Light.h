//
// Created by Alberto Elorza Rubio on 25/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_LIGHT_H
#define HETEROGENEOUS_SOLIDS_LIGHT_H

#include <functional>
#include <glm/glm.hpp>
#include "../RenderContext.h"
#include "LightProps.h"

namespace hs {

    enum class LightType {
        Ambient,
        Point,
        Directional,
        SpotLight
    };

    class Light {
    private:
        std::string name;
        LightType lightType;
        LightProps lightProps;
        bool enabled;
    public:
        Light(
            std::string name, LightType lightType, glm::vec3 iA, glm::vec3 iD, glm::vec3 iS,
            glm::vec3 position, glm::vec3 lookAt, float gamma
        );
        Light(std::string name, LightType lightType);
        Light();
        Light(const Light&) = default;

        void setEnabled(bool enabled);
        [[nodiscard]] bool isEnabled() const;

        void setName(std::string name);
        [[nodiscard]] std::string getName() const;

        void setLightType(LightType lightType);
        [[nodiscard]] LightType getLightType() const;

        void setLightProps(LightProps lightData);
        LightProps& getLightProps();

        void apply(RenderContext& renderContext);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_LIGHT_H
