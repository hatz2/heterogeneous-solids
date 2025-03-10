//
// Created by Alberto Elorza Rubio on 29/01/2024.
//

#include <spdlog/spdlog.h>
#include "ResourceDeserializer.h"
#include "JSONUtils.h"

namespace hs::json {
    ResourceDeserializer::ResourceDeserializer(
        MacroSet& macroSet, ItemSet<Material>& materialSet,
        ItemSet<HeterogeneousMaterial>& heterogeneousMaterialSet
    ) : macroSet(macroSet), materialSet(materialSet), heterogeneousMaterialSet(heterogeneousMaterialSet) {

    }

    void ResourceDeserializer::deserializeResources(nlohmann::json& json) {
        int idx = 0; // TODO: Maybe change it for a more direct correlation inside the json dump
        for (auto& data : json["macros"].items()) {
            auto macro = std::make_shared<TrimmingNode>();
            deserialize(data.value(), *macro);
            macroSet.insert(macro);
            assocMacro.insert({idx++, macro });
        }
        idx = 0;
        for (auto& data : json["materials"].items()) {
            auto material = std::make_shared<Material>();
            deserialize(data.value(), *material);
            materialSet.insert(material);
            assocMaterial.insert({idx++, material });
        }
        idx = 0;
        for (auto& data : json["heterogeneous_materials"].items()) {
            auto heterogeneousMaterial = std::make_shared<HeterogeneousMaterial>();
            if (auto materialA = findMaterial(data.value()["primary"])) {
                heterogeneousMaterial->setPrimaryMaterial(materialA.value());
            } else spdlog::warn("Unable to fetch primary material resource");
            if (auto materialB = findMaterial(data.value()["secondary"])) {
                heterogeneousMaterial->setSecondaryMaterial(materialB.value());
            } else spdlog::warn("Unable to fetch primary material resource");
            deserialize(data.value(), *heterogeneousMaterial);
            heterogeneousMaterialSet.insert(heterogeneousMaterial);
            assocHeterogeneousMaterial.insert({idx++, heterogeneousMaterial });
        }
    }

    std::optional<std::shared_ptr<TrimmingNode>> ResourceDeserializer::findMacro(size_t index) {
        auto found = assocMacro.find(index);
        if (found == assocMacro.end()) return std::nullopt;
        return found->second;
    }

    std::optional<std::shared_ptr<Material>> ResourceDeserializer::findMaterial(size_t index) {
        auto found = assocMaterial.find(index);
        if (found == assocMaterial.end()) return std::nullopt;
        return found->second;
    }

    std::optional<std::shared_ptr<HeterogeneousMaterial>>
    ResourceDeserializer::findHeterogeneousMaterial(size_t index) {
        auto found = assocHeterogeneousMaterial.find(index);
        if (found == assocHeterogeneousMaterial.end()) return std::nullopt;
        return found->second;
    }
} // hs