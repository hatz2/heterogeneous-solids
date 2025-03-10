//
// Created by Alberto Elorza Rubio on 20/01/2024.
//

#include <spdlog/spdlog.h>
#include "SaveObjectVisitor.h"
#include "../../scene/objects/GroupNode.h"
#include "../../heterogeneous_solids/HeterogeneousSolid.h"
#include "JSONUtils.h"

namespace hs::json {
    SaveObjectVisitor::SaveObjectVisitor(nlohmann::json& container, ResourceSerializer& resourceSerializer) :
        json(container), resourceSerializer(resourceSerializer)
    {

    }

    void SaveObjectVisitor::doGroupNode(GroupNode& group3D) {
        json["type"] = "group";
        serialize(json["transform"], group3D.getOwnedTransform()->get());
        serialize(json, group3D.getState());
        nlohmann::json& children = json["children"];
        for (std::unique_ptr<SceneNode>& child : group3D) {
            children.push_back({});
            SaveObjectVisitor visitor(children.back(), resourceSerializer);
            child->visitNode(visitor);
        }
    }

    void SaveObjectVisitor::doHeterogeneousSolid(HeterogeneousSolid& heterogeneousSolid) {
        json["type"] = "heterogeneous_solid";
        serialize(json["transform"], heterogeneousSolid.getOwnedTransform()->get());
        serialize(json, heterogeneousSolid.getState());
        if (auto materialIdx = resourceSerializer.findHeterogeneousMaterialIndex(heterogeneousSolid.getMaterial())) {
            json["material"] = materialIdx.value();
        } else spdlog::warn("Unable to fetch a heterogeneous material resource");
        nlohmann::json& children = json["cells"];
        for (Cell* cell : heterogeneousSolid.getCells()) {
            children.push_back({});
            SaveObjectVisitor visitor(children.back(), resourceSerializer);
            visitor.doCell(*cell);
        }
    }

    void SaveObjectVisitor::doCell(Cell& cell) {
        auto& coefs = cell.getCellCoefGroup()->getCoefs();
        for (int i = 0; i < 64; i++) {
            auto& coef = json["coefs"][i];
            glm::vec3 shapePosition = coefs[i]->getPositionCoef().getShapePosition();
            coef["position"] = { shapePosition.x, shapePosition.y, shapePosition.z };
            coef["a0"] = coefs[i]->getMaterialCoef().getA0();
            coef["continuity"] = coefs[i]->getMaterialCoef().isKeepContinuity();
        }
        serialize(json, cell.getState());
        nlohmann::json& children = json["trimmed_cells"];
        for (TrimmedCell* trimmedCell : cell.getTrimmedCells()) {
            children.push_back({});
            SaveObjectVisitor visitor(children.back(), resourceSerializer);
            visitor.doTrimmedCell(*trimmedCell);
        }
    }

    void SaveObjectVisitor::doTrimmedCell(TrimmedCell& trimmedCell) {
        serialize(json, *trimmedCell.getCanonicalNode());
        if (!trimmedCell.usingCanonicalNode()) {
                auto idx = resourceSerializer.findMacroIndex(trimmedCell.getActiveNode());
            if (idx) json["macro"] = idx.value();
            else spdlog::warn("Unable to fetch a macro in the resource serializer");
        }
        if (trimmedCell.childCount() > 0) {
            nlohmann::json& children = json["trimmed_cells"];
            for (std::unique_ptr<TrimmedCell>& subTrimmedCell: trimmedCell.getSubTrimmedCells()) {
                children.push_back({});
                SaveObjectVisitor visitor(children.back(), resourceSerializer);
                visitor.doTrimmedCell(*subTrimmedCell);
            }
        }
    }
} // hs