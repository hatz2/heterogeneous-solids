//
// Created by Alberto Elorza Rubio on 20/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SAVEOBJECTVISITOR_H
#define HETEROGENEOUS_SOLIDS_SAVEOBJECTVISITOR_H

#include <nlohmann/json.hpp>
#include "../../utils/NodeVisitor.h"
#include "ResourceSerializer.h"

namespace hs::json {

    class SaveObjectVisitor: public NodeVisitor {
    public:
        SaveObjectVisitor(nlohmann::json& container, ResourceSerializer& resourceSerializer);

        void doGroupNode(GroupNode& group3D) override;
        void doHeterogeneousSolid(hs::HeterogeneousSolid& heterogeneousSolid) override;
        void doCell(hs::Cell& cell) override;
        void doTrimmedCell(hs::TrimmedCell& trimmedCell) override;
    private:
        nlohmann::json& json;
        ResourceSerializer& resourceSerializer;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SAVEOBJECTVISITOR_H
