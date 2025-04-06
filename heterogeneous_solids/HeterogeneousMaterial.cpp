//
// Created by Alberto Elorza Rubio on 16/01/2024.
//

#include "HeterogeneousMaterial.h"

#include <utility>
#include <spdlog/spdlog.h>

namespace hs {
    HeterogeneousMaterial::HeterogeneousMaterial(MaterialType type) :
        type(type), axis(MaterialAxis::U), coefs({ 1, 0, 0, 0 }), range({0, 1}), featurePoints({
           {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0},
           {0, 0, 1}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1},
        }),
        usingCorrectedPerlin(true),
        materialA(std::make_shared<Material>(glm::vec3{0.35}, glm::vec3{0.55}, glm::vec3{0.3}, 16.f)),
        materialB(std::make_shared<Material>(glm::vec3{0.35}, glm::vec3{0.9}, glm::vec3{0.3}, 16.f)),
        description(std::make_unique<DescriptionPropImpl>("Heterogeneous Material"))
    {

    }

    MaterialType HeterogeneousMaterial::getType() const {
        return type;
    }

    void HeterogeneousMaterial::setType(MaterialType type) {
        HeterogeneousMaterial::type = type;
    }

    void HeterogeneousMaterial::apply(RenderContext& renderContext) {
        if (renderContext.getRenderMode() != RenderMode::Surfaces) return;
        renderContext.getFragmentSubroutines()
            .setSubroutine("perlinNoise", usingCorrectedPerlin ? "correctedPNoise" : "pNoise");
        switch (type) {
            case MaterialType::Primary:
                renderContext.getFragmentSubroutines()
                    .setSubroutine("selectMaterial", "selectPrimaryMaterial");
                applyPrimary(renderContext, *materialA);
                break;
            case MaterialType::Secondary:
                renderContext.getFragmentSubroutines()
                    .setSubroutine("selectMaterial", "selectPrimaryMaterial");
                applyPrimary(renderContext, *materialB);
                break;
            case MaterialType::Continuous:
                renderContext.getFragmentSubroutines()
                    .setSubroutine("selectMaterial", "selectContinuousMaterial");
                applyPrimary(renderContext, *materialA);
                applySecondary(renderContext, *materialB);
                break;
            case MaterialType::FunctionallyGraded:
                renderContext.getFragmentSubroutines()
                    .setSubroutine("selectMaterial", "selectFunctionallyGradedMaterial");
                applyPrimary(renderContext, *materialA);
                applySecondary(renderContext, *materialB);
                break;
            case MaterialType::Composite:
                renderContext.getFragmentSubroutines()
                    .setSubroutine("selectMaterial", "selectCompositeMaterial");
                applyCompositeMaterialProps(renderContext);
                applyPrimary(renderContext, *materialA);
                applySecondary(renderContext, *materialB);
                break;
        }
        renderContext.getFragmentSubroutines().applySubroutines();
    }

    MaterialAxis HeterogeneousMaterial::getAxis() const {
        return axis;
    }

    void HeterogeneousMaterial::setAxis(MaterialAxis axis) {
        HeterogeneousMaterial::axis = axis;
    }

    glm::vec4 HeterogeneousMaterial::getCoefs() const {
        return coefs;
    }

    void HeterogeneousMaterial::setCoefs(glm::vec4 coefs) {
        HeterogeneousMaterial::coefs = coefs;
    }

    glm::vec2 HeterogeneousMaterial::getValueRange() const {
        return range;
    }

    void HeterogeneousMaterial::setValueRange(glm::vec2 range) {
        HeterogeneousMaterial::range = range;
    }

    [[nodiscard]] std::vector<glm::vec3>& HeterogeneousMaterial::getFeaturePoints() {
        return featurePoints;
    }

    bool HeterogeneousMaterial::isUsingCorrectedPerlin() {
        return usingCorrectedPerlin;
    }

    void HeterogeneousMaterial::setUsingCorrectedPerlin(bool usingCorrectedPerlin) {
        HeterogeneousMaterial::usingCorrectedPerlin = usingCorrectedPerlin;
    }

    std::shared_ptr<Material> HeterogeneousMaterial::getPrimaryMaterial() {
        return materialA;
    }

    void HeterogeneousMaterial::setPrimaryMaterial(std::shared_ptr<Material> material) {
        materialA = std::move(material);
    }

    std::shared_ptr<Material> HeterogeneousMaterial::getSecondaryMaterial() {
        return materialB;
    }

    void HeterogeneousMaterial::setSecondaryMaterial(std::shared_ptr<Material> material) {
        materialB = std::move(material);
    }

    DescriptionProp& HeterogeneousMaterial::getDescriptionProp() const {
        return *description;
    }

    void HeterogeneousMaterial::applyCompositeMaterialProps(RenderContext& renderContext) {
        renderContext.getUniform("compositeMaterial.minValue").set(range.x);
        renderContext.getUniform("compositeMaterial.maxValue").set(range.y);
        renderContext.getUniform("compositeMaterial.pointCount").set((int)featurePoints.size());
        renderContext.getUniform("compositeMaterial.coefs").set(coefs);
        for (int i = 0; i < featurePoints.size(); i++)
            renderContext.getUniform(
                "compositeMaterial.points[" + std::to_string(i) + "]"
            ).set(featurePoints[i]);
    }

    void HeterogeneousMaterial::applyPrimary(RenderContext& renderContext, const Material& material) {
        renderContext.getUniform("materials[0].kA").set(material.getKA());
        renderContext.getUniform("materials[0].kD").set(material.getKD());
        renderContext.getUniform("materials[0].kS").set(material.getKS());
        renderContext.getUniform("materials[0].shininess").set(material.getShininess());
        renderContext.getUniform("materials[0].roughness").set(material.getRoughness());
        renderContext.getUniform("materials[0].metallic").set(material.getMetallic());
    }

    void HeterogeneousMaterial::applySecondary(RenderContext& renderContext, const Material& material) {
        renderContext.getUniform("materials[1].kA").set(material.getKA());
        renderContext.getUniform("materials[1].kD").set(material.getKD());
        renderContext.getUniform("materials[1].kS").set(material.getKS());
        renderContext.getUniform("materials[1].shininess").set(material.getShininess());
        renderContext.getUniform("materials[1].roughness").set(material.getRoughness());
        renderContext.getUniform("materials[1].metallic").set(material.getMetallic());
    }
} // hs