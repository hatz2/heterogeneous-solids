//
// Created by Alberto Elorza Rubio on 21/01/2024.
//

#include <spdlog/spdlog.h>
#include "ObjectDeserializer.h"
#include "../../scene/objects/GroupNode.h"
#include "../../heterogeneous_solids/HeterogeneousSolid.h"
#include "JSONUtils.h"

namespace hs::json {

    ObjectDeserializer::ObjectDeserializer(ResourceDeserializer& resourceDeserializer) :
        resourceDeserializer(resourceDeserializer)
    {

    }

    void ObjectDeserializer::applyGroupNode(nlohmann::json& json, GroupNode& group3D) {
        deserialize(json["transform"], group3D.getOwnedTransform()->get());
        deserialize(json, group3D.getState());
        for (auto& item : json["children"]) {
            if (item["type"] == "group") {
                auto group = std::make_unique<GroupNode>();
                applyGroupNode(item, *group);
                std::unique_ptr<SceneNode> obj = std::move(group);
                group3D.addChild(obj);
            } else if (item["type"] == "heterogeneous_solid") {
                std::unique_ptr<SceneNode> hs = getHeterogeneousSolid(item);
                group3D.addChild(hs);
            } else continue; //TODO: log unexpected type
        }
    }

    std::unique_ptr<HeterogeneousSolid> ObjectDeserializer::getHeterogeneousSolid(nlohmann::json& json) {
        auto heterogeneousSolid = std::make_unique<HeterogeneousSolid>();
        deserialize(json["transform"], heterogeneousSolid->getOwnedTransform()->get());
        deserialize(json, heterogeneousSolid->getState());
        if (auto material = resourceDeserializer.findHeterogeneousMaterial(json["material"])) {
            heterogeneousSolid->setMaterial(material.value());
        } else spdlog::warn("Unable to fetch heterogeneous material resource");
        for (auto& item : json["cells"]) {
            std::unique_ptr<SceneNode> child = getCell(item);
            heterogeneousSolid->addChild(child);
        }
        return heterogeneousSolid;
    }

    std::unique_ptr<Cell> ObjectDeserializer::getCell(nlohmann::json& json) {
        auto cell = std::make_unique<Cell>();
        auto& coefs = cell->getCellCoefGroup()->getCoefs();
        for (int i = 0; i < 64; i++) {
            auto& coef = json["coefs"][i];
            coefs[i]->getPositionCoef().setShapePosition({
               coef["position"][0], coef["position"][1], coef["position"][2]
            });
            MaterialCoef& materialCoef = coefs[i]->getMaterialCoef();
            materialCoef.setA0(coef["a0"]);
            materialCoef.setKeepContinuity(coef["continuity"]);
        }
        deserialize(json, cell->getState());
        int idx = 0;
        for (const auto& trimmedCell : cell->getTrimmedCells()) {
            applyToTrimmedCell(json["trimmed_cells"][idx++], *trimmedCell);
        }
        return cell;
    }

    void ObjectDeserializer::applyToTrimmedCell(nlohmann::json& json, TrimmedCell& trimmedCell) {
        deserialize(json, *trimmedCell.getCanonicalNode());
        if (auto macroIdx = json["macro"]; !macroIdx.empty()) {
            if (auto macro = resourceDeserializer.findMacro(macroIdx)) {
                trimmedCell.setActiveNode(macro.value());
            } else spdlog::warn("Unable to fetch a macro in the resource deserializer");
        }
        auto& children = json["trimmed_cells"];
        if (!children.empty()) {
            trimmedCell.reserve(children.size());
            int idx = 0;
            for (auto& child : trimmedCell.getSubTrimmedCells()) {
                applyToTrimmedCell(children[idx++], *child);
            }
        }
    }
} // hs