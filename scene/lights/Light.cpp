//
// Created by Alberto Elorza Rubio on 25/11/2023.
//

#include "Light.h"

#include <sstream>
#include <utility>

namespace hs {
    Light::Light(
        std::string name, LightType lightType, glm::vec3 iA, glm::vec3 iD, glm::vec3 iS,
        glm::vec3 position, glm::vec3 lookAt, float gamma
    ) :
        name(std::move(name)), lightType(lightType), lightProps(iA, iD, iS, position, lookAt, gamma), enabled(true)
    {

    }

    Light::Light(std::string name, LightType lightType): name(std::move(name)),
        lightType(lightType), lightProps(), enabled(true) {

    }

    Light::Light(): Light("New Light", LightType::Point) {

    }

    void Light::setEnabled(bool enabled) {
        Light::enabled = enabled;
    }

    bool Light::isEnabled() const {
        return enabled;
    }

    void Light::setName(std::string name) {
        Light::name = std::move(name);
    }

    std::string Light::getName() const {
        return name;
    }

    void Light::setLightType(LightType lightType) {
        Light::lightType = lightType;
    }

    LightType Light::getLightType() const {
        return lightType;
    }

    void Light::setLightProps(LightProps lightProps) {
        Light::lightProps = lightProps;
    }

    LightProps& Light::getLightProps() {
        return lightProps;
    }

    void Light::apply(RenderContext& renderContext, const unsigned int index) {
        std::stringstream typeProperty;
        typeProperty << "lights[" << index << "].type";
        renderContext.getUniform(typeProperty.str()).set(static_cast<int>(lightType));


        std::stringstream iAProperty;
        iAProperty << "lights[" << index << "].iA";
        renderContext.getUniform(iAProperty.str()).set(lightProps.getIA());

        std::stringstream iDProperty;
        iDProperty << "lights[" << index << "].iD";
        renderContext.getUniform(iDProperty.str()).set(lightProps.getID());

        std::stringstream iSProperty;
        iSProperty << "lights[" << index << "].iS";
        renderContext.getUniform(iSProperty.str()).set(lightProps.getIS());

        std::stringstream positionProperty;
        positionProperty << "lights[" << index << "].position";
        renderContext.getUniform(positionProperty.str()).set(
            static_cast<glm::vec3>(renderContext.getViewMatrix() * glm::vec4(lightProps.getPosition(), 1))
        );

        std::stringstream directionProperty;
        directionProperty << "lights[" << index << "].direction";
        renderContext.getUniform(directionProperty.str()).set(
            static_cast<glm::vec3>(renderContext.getViewMatrix() * glm::vec4(lightProps.getLookAt() - lightProps.getPosition(), 0))
        );

        std::stringstream spotAngleProperty;
        spotAngleProperty << "lights[" << index << "].spotAngle";
        renderContext.getUniform(spotAngleProperty.str()).set(lightProps.getGamma());



        // switch (lightType) {
        //     case LightType::Ambient:
        //         renderContext.getUniform("light[.iA").set(lightProps.getIA());
        //         renderContext.getFragmentSubroutines().setSubroutine("lightMethod", "ambientLight");
        //         break;
        //     case LightType::Point:
        //         renderContext.getUniform("light.position").set(
        //             (glm::vec3)(renderContext.getViewMatrix() * glm::vec4(lightProps.getPosition(), 1))
        //         );
        //         renderContext.getUniform("light.iD").set(lightProps.getID());
        //         renderContext.getUniform("light.iS").set(lightProps.getIS());
        //         renderContext.getFragmentSubroutines().setSubroutine("lightMethod", "pointLight");
        //         break;
        //     case LightType::Directional:
        //         renderContext.getUniform("light.direction").set(
        //             (glm::vec3)(renderContext.getViewMatrix() * glm::vec4(lightProps.getLookAt() - lightProps.getPosition(), 0))
        //         );
        //         renderContext.getUniform("light.iD").set(lightProps.getID());
        //         renderContext.getUniform("light.iS").set(lightProps.getIS());
        //         renderContext.getFragmentSubroutines().setSubroutine("lightMethod", "directionalLight");
        //         break;
        //     case LightType::SpotLight:
        //         renderContext.getUniform("light.direction").set(
        //             (glm::vec3)(renderContext.getViewMatrix() * glm::vec4(lightProps.getLookAt() - lightProps.getPosition(), 0))
        //         );
        //         renderContext.getUniform("light.position").set(
        //             (glm::vec3)(renderContext.getViewMatrix() * glm::vec4(lightProps.getPosition(), 1))
        //         );
        //         renderContext.getUniform("light.iD").set(lightProps.getID());
        //         renderContext.getUniform("light.iS").set(lightProps.getIS());
        //         renderContext.getUniform("light.spotAngle").set(lightProps.getGamma());
        //         renderContext.getFragmentSubroutines().setSubroutine("lightMethod", "spotLight");
        //         break;
        // }
    }
} // hs