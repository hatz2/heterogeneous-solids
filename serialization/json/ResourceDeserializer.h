//
// Created by Alberto Elorza Rubio on 29/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_RESOURCEDESERIALIZER_H
#define HETEROGENEOUS_SOLIDS_RESOURCEDESERIALIZER_H

#include <nlohmann/json.hpp>
#include <optional>
#include "../../heterogeneous_solids/trimmed_cells/TrimmingNode.h"
#include "../../heterogeneous_solids/HeterogeneousMaterial.h"

namespace hs::json {

    class ResourceDeserializer {
    public:
        ResourceDeserializer(
            MacroSet& macroSet, ItemSet<Material>& materialSet,
            ItemSet<HeterogeneousMaterial>& heterogeneousMaterialSet
        );

        void deserializeResources(nlohmann::json& json);

        std::optional<std::shared_ptr<TrimmingNode>> findMacro(size_t index);
        std::optional<std::shared_ptr<Material>> findMaterial(size_t index);
        std::optional<std::shared_ptr<HeterogeneousMaterial>> findHeterogeneousMaterial(size_t index);
    private:
        MacroSet& macroSet;
        ItemSet<Material>& materialSet;
        ItemSet<HeterogeneousMaterial>& heterogeneousMaterialSet;

        std::map<size_t, std::shared_ptr<TrimmingNode>> assocMacro;
        std::map<size_t, std::shared_ptr<Material>> assocMaterial;
        std::map<size_t, std::shared_ptr<HeterogeneousMaterial>> assocHeterogeneousMaterial;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_RESOURCEDESERIALIZER_H
