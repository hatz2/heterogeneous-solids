//
// Created by Alberto Elorza Rubio on 20/01/2024.
//

#include "JSONUtils.h"

namespace hs::json {

    void serialize(nlohmann::json& json, const SceneNodeState& state) {
        json["description"] = state.getDescription();
        json["visible"] = state.isVisible();
    }

    void deserialize(nlohmann::json& json, SceneNodeState& state) {
        state.setDescription(json["description"]);
        state.setVisible(json["visible"]);
    }

    void serialize(nlohmann::json& json, TrimmingNode& node) {
        serialize(json, node.getState());
        auto& op = node.getOperation();
        json["op"] = op.getMachiningProcess().name();
        for (const auto& [name, value] : op.getMachiningParams()) {
            json["params"][name] = value.getValue();
        }
    }

    void deserialize(nlohmann::json& json, TrimmingNode& node) {
        deserialize(json, node.getState());
        auto& op =  node.getOperation();
        op.setMachiningProcess(json["op"]);
        for (const auto& [name, value] : json["params"].items())
            op.getMachiningParams().at(name).set(value); // FIXME: for wrong name could throw
    }

    void serialize(nlohmann::json& json, const Material& material) {
        json["description"] = material.getDescriptionProp().getDescription();
        json["shininess"] = material.getShininess();
        json["metallic"] = material.getMetallic();
        json["roughness"] = material.getRoughness();
        auto kA = material.getKA();
        json["kA"] = { kA.x, kA.y, kA.z };
        auto kD = material.getKD();
        json["kD"] = { kD.x, kD.y, kD.z };
        auto kS = material.getKS();
        json["kS"] = { kS.x, kS.y, kS.z };
    }

    void deserialize(nlohmann::json& json, Material& material) {
        material.getDescriptionProp().setDescription(json["description"]);
        material.setShininess(json["shininess"]);
        material.setMetallic(json["metallic"]);
        material.setRoughness(json["roughness"]);
        material.setKA({ json["kA"][0], json["kA"][1], json["kA"][2] });
        material.setKD({ json["kD"][0], json["kD"][1], json["kD"][2] });
        material.setKS({ json["kS"][0], json["kS"][1], json["kS"][2] });
    }

    void serialize(nlohmann::json& json, HeterogeneousMaterial& material) {
        json["description"] = material.getDescriptionProp().getDescription();
        json["type"] = material.getType();
        json["axis"] = material.getAxis();
        auto coefs = material.getCoefs();
        json["coefs"] = { coefs.x, coefs.y, coefs.z, coefs.w };
        auto range = material.getValueRange();
        json["range"] = { range.x, range.y };
        int p = 0;
        for (auto& featurePoint : material.getFeaturePoints())
            json["point"][p++] = { featurePoint.x, featurePoint.y, featurePoint.z };
    }

    void deserialize(nlohmann::json& json, HeterogeneousMaterial& material) {
        material.getDescriptionProp().setDescription(json["description"]);
        material.setType(json["type"]);
        material.setAxis(json["axis"]);
        material.setCoefs({ json["coefs"][0], json["coefs"][1], json["coefs"][2], json["coefs"][3] });
        material.setValueRange({ json["range"][0], json["range"][1] });
        material.getFeaturePoints().clear();
        for (auto& point : json["point"])
            material.getFeaturePoints().emplace_back(point[0], point[1], point[2]);
    }

    void serialize(nlohmann::json& json, const Transform& transform) {
        auto scale = transform.getScale();
        json["scale"] = { scale.x, scale.y, scale.z };
        auto rotation = transform.getRotation();
        json["rotation"] = { rotation.x, rotation.y, rotation.z };
        auto translation = transform.getTranslation();
        json["translation"] = { translation.x, translation.y, translation.z };
    }

    void deserialize(nlohmann::json& json, Transform& transform) {
        auto scale = json["scale"];
        transform.setScale({ scale[0], scale[1], scale[2] });
        auto rotation = json["rotation"];
        transform.setRotation({ rotation[0], rotation[1], rotation[2] });
        auto translation = json["translation"];
        transform.setTranslation({ translation[0], translation[1], translation[2] });
    }
} // hs