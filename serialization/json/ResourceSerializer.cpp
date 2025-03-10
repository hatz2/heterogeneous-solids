//
// Created by Alberto Elorza Rubio on 29/01/2024.
//

#include <spdlog/spdlog.h>
#include "ResourceSerializer.h"
#include "JSONUtils.h"

namespace hs::json {
    ResourceSerializer::ResourceSerializer(nlohmann::json& json) : json(json) {

    }

    void ResourceSerializer::serializeMacroSet(MacroSet& macroSet) {
        for (auto& macro : macroSet) {
            nlohmann::json data;
            serialize(data, *macro);
            assocMacro.insert({ macro, json["macros"].size() });
            json["macros"].push_back(data);
        }
    }

    void ResourceSerializer::serializeMaterialSet(ItemSet<Material>& materialSet) {
        for (auto& material : materialSet) {
            nlohmann::json data;
            serialize(data, *material);
            assocMaterial.insert({ material, json["materials"].size() });
            json["materials"].push_back(data);
        }
    }

    void ResourceSerializer::serializeHeterogeneousMaterialSet(ItemSet<HeterogeneousMaterial>& heterogeneousMaterialSet) {
        for (auto& material : heterogeneousMaterialSet) {
            nlohmann::json data;
            serialize(data, *material);
            if (auto indexA = findMaterialIndex(material->getPrimaryMaterial())) {
                data["primary"] = indexA.value();
            } else spdlog::warn("Unable to fetch primary material resource");
            if (auto indexB = findMaterialIndex(material->getSecondaryMaterial())) {
                data["secondary"] = indexB.value();
            } else spdlog::warn("Unable to fetch secondary material resource");
            assocHeterogeneousMaterial.insert({ material, json["heterogeneous_materials"].size() });
            json["heterogeneous_materials"].push_back(data);
        }
    }

    std::optional<size_t> ResourceSerializer::findMacroIndex(const std::shared_ptr<TrimmingNode>& macro) {
        auto found = assocMacro.find(macro);
        if (found == assocMacro.end()) return std::nullopt;
        return found->second;
    }

    std::optional<size_t> ResourceSerializer::findMaterialIndex(const std::shared_ptr<Material>& material) {
        auto found = assocMaterial.find(material);
        if (found == assocMaterial.end()) return std::nullopt;
        return found->second;
    }

    std::optional<size_t>
    ResourceSerializer::findHeterogeneousMaterialIndex(const std::shared_ptr<HeterogeneousMaterial>& material) {
        auto found = assocHeterogeneousMaterial.find(material);
        if (found == assocHeterogeneousMaterial.end()) return std::nullopt;
        return found->second;
    }
} // hs