//
// Created by Alberto Elorza Rubio on 16/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_HETEROGENEOUSMATERIAL_H
#define HETEROGENEOUS_SOLIDS_HETEROGENEOUSMATERIAL_H

#include "../scene/Material.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <array>

namespace hs {

    enum class MaterialType {
        Primary = 0,
        Secondary = 1,
        Continuous = 2,
        FunctionallyGraded = 3,
        Composite = 4
    };

    enum class MaterialAxis {
        U,
        V,
        W
    };

    class HeterogeneousMaterial {
    public:
        explicit HeterogeneousMaterial(MaterialType type = MaterialType::Primary);

        [[nodiscard]] MaterialType getType() const;
        void setType(MaterialType type);

        [[nodiscard]] MaterialAxis getAxis() const;
        void setAxis(MaterialAxis axis);

        [[nodiscard]] glm::vec4 getCoefs() const;
        void setCoefs(glm::vec4 coefs);

        [[nodiscard]] glm::vec2 getValueRange() const;
        void setValueRange(glm::vec2 range);

        [[nodiscard]] std::vector<glm::vec3>& getFeaturePoints();

        [[nodiscard]] bool isUsingCorrectedPerlin();
        void setUsingCorrectedPerlin(bool usingCorrectedPerlin);

        [[nodiscard]] std::shared_ptr<Material> getPrimaryMaterial();
        void setPrimaryMaterial(std::shared_ptr<Material> material);

        [[nodiscard]] std::shared_ptr<Material> getSecondaryMaterial();
        void setSecondaryMaterial(std::shared_ptr<Material> material);

        [[nodiscard]] DescriptionProp& getDescriptionProp() const;

        void apply(RenderContext& renderContext);
    private:
        MaterialType type;
        MaterialAxis axis;
        glm::vec4 coefs;
        glm::vec2 range;
        std::vector<glm::vec3> featurePoints;
        bool usingCorrectedPerlin;

        std::shared_ptr<Material> materialA;
        std::shared_ptr<Material> materialB;

        std::unique_ptr<DescriptionProp> description;

        void applyCompositeMaterialProps(RenderContext& renderContext);
        static void applyPrimary(RenderContext& renderContext, const Material& material);
        static void applySecondary(RenderContext& renderContext, const Material& material);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_HETEROGENEOUSMATERIAL_H
