//
// Created by Alberto Elorza Rubio on 29/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_RESOURCESERIALIZER_H
#define HETEROGENEOUS_SOLIDS_RESOURCESERIALIZER_H

#include <optional>
#include <nlohmann/json.hpp>

#include "../../heterogeneous_solids/trimmed_cells/TrimmingNode.h"
#include "../../heterogeneous_solids/HeterogeneousMaterial.h"

namespace hs::json {

    class ResourceSerializer {
    public:
        explicit ResourceSerializer(nlohmann::json& json);

        void serializeMacroSet(MacroSet& macroSet);
        void serializeMaterialSet(ItemSet<Material>& materialSet);
        void serializeHeterogeneousMaterialSet(ItemSet<HeterogeneousMaterial>& heterogeneousMaterialSet);

        std::optional<size_t> findMacroIndex(const std::shared_ptr<TrimmingNode>& macro);
        std::optional<size_t> findMaterialIndex(const std::shared_ptr<Material>& material);
        std::optional<size_t> findHeterogeneousMaterialIndex(const std::shared_ptr<HeterogeneousMaterial>& material);
    private:
        nlohmann::json& json;
        std::map<std::shared_ptr<TrimmingNode>, size_t> assocMacro;
        std::map<std::shared_ptr<Material>, size_t> assocMaterial;
        std::map<std::shared_ptr<HeterogeneousMaterial>, size_t> assocHeterogeneousMaterial;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_RESOURCESERIALIZER_H
