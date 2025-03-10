//
// Created by Alberto Elorza Rubio on 20/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_JSONUTILS_H
#define HETEROGENEOUS_SOLIDS_JSONUTILS_H

#include <nlohmann/json.hpp>
#include "../../scene/objects/SceneNodeState.h"
#include "../../heterogeneous_solids/trimmed_cells/TrimmingNode.h"
#include "../../scene/Material.h"
#include "../../heterogeneous_solids/HeterogeneousMaterial.h"

namespace hs::json {

    void serialize(nlohmann::json& json, const SceneNodeState& state);
    void deserialize(nlohmann::json& json, SceneNodeState& state);

    void serialize(nlohmann::json& json, TrimmingNode& node);
    void deserialize(nlohmann::json& json, TrimmingNode& node);

    void serialize(nlohmann::json& json, const Material& material);
    void deserialize(nlohmann::json& json, Material& material);

    void serialize(nlohmann::json& json, HeterogeneousMaterial& material);
    void deserialize(nlohmann::json& json, HeterogeneousMaterial& material);

    void serialize(nlohmann::json& json, const Transform& transform);
    void deserialize(nlohmann::json& json, Transform& transform);

} // hs

#endif //HETEROGENEOUS_SOLIDS_JSONUTILS_H
