//
// Created by Alberto Elorza Rubio on 21/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_OBJECTDESERIALIZER_H
#define HETEROGENEOUS_SOLIDS_OBJECTDESERIALIZER_H

#include <nlohmann/json.hpp>
#include "../../scene/objects/GroupNode.h"
#include "../../heterogeneous_solids/HeterogeneousSolid.h"
#include "ResourceDeserializer.h"

namespace hs::json {

    class ObjectDeserializer {
    public:
        explicit ObjectDeserializer(ResourceDeserializer& resourceDeserializer);

        void applyGroupNode(nlohmann::json& json, GroupNode& group3D);
        std::unique_ptr<HeterogeneousSolid> getHeterogeneousSolid(nlohmann::json& json);
        std::unique_ptr<Cell> getCell(nlohmann::json& json);
        // Trimmed cells are generated automatically
        void applyToTrimmedCell(nlohmann::json& json, TrimmedCell& trimmedCell);
    private:
        ResourceDeserializer& resourceDeserializer;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_OBJECTDESERIALIZER_H
