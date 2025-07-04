//
// Created by Alberto Elorza Rubio on 25/11/2023.
//

#include "Light.h"

#include <sstream>
#include <utility>
#include "ShadowMap.h"

namespace hs {
    Light::Light(
        std::string name, LightType lightType, glm::vec3 iA, glm::vec3 iD, glm::vec3 iS,
        glm::vec3 position, glm::vec3 lookAt, float gamma, bool shadow
    ) :
        name(std::move(name)), lightType(lightType), lightProps(iA, iD, iS, position, lookAt, gamma, shadow), enabled(true)
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

    const ShadowMap& Light::getShadowMap() const
    {
        return shadowMap;
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

        std::stringstream shadowProperty;
        shadowProperty << "lights[" << index << "].shadow";
        renderContext.getUniform(shadowProperty.str()).set(getLightProps().isShadow());

        std::stringstream shadowMapProperty;
        shadowMapProperty << "shadowMaps[" << index << "]";
        glActiveTexture(GL_TEXTURE3 + index);
        glBindTexture(GL_TEXTURE_2D, shadowMap.getId());
        renderContext.getUniform(shadowMapProperty.str()).set(3 + index);

        std::stringstream lightSpaceMatrixProperty;
        lightSpaceMatrixProperty << "lightSpaceMatrices[" << index << "]";
        renderContext.getUniform(lightSpaceMatrixProperty.str()).set(getLightSpaceMatrix());
    }

    void Light::renderToShadowMap(const Scene& scene, ShaderManager& shaderManager)
    {
        shadowMap.render(scene, shaderManager, *this);
    }

    glm::mat4 Light::getLightSpaceMatrix() const
    {
        float nearPlane = 0.01f, farPlane = 150.0f;
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);


        glm::vec3 lightDir = glm::normalize(lightProps.getLookAt() - lightProps.getPosition());
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        if (fabs(glm::dot(lightDir, up)) > 0.995f)
        {
            up = glm::vec3(0.0f, 0.0f, 1.0f);
        }

        glm::mat4 lightView = glm::lookAt(
            lightProps.getPosition(),
            lightProps.getLookAt(),
            up
        );

        return lightProjection * lightView;
    }
} // hs