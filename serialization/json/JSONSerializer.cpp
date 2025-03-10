//
// Created by Alberto Elorza Rubio on 20/01/2024.
//

#include "JSONSerializer.h"
#include "SaveObjectVisitor.h"
#include "ObjectDeserializer.h"
#include "ResourceSerializer.h"

namespace hs {
    JSONSerializer::JSONSerializer(unsigned char indent) : indent(indent) {

    }

    std::string JSONSerializer::serialize(const Context& context) {
        nlohmann::json json;
        serializeToJSON(context, json);
        return json.dump(indent);
    }

    void JSONSerializer::deserialize(const Context& context, const std::string& source) {
        nlohmann::json json = nlohmann::json::parse(source);
        deserializeFromJSON(context, json);
    }

    void JSONSerializer::serializeToJSON(const Context& context, nlohmann::json& json) {
        {
            json::ResourceSerializer resourceSerializer(json);
            resourceSerializer.serializeMacroSet(context.getMacroSet());
            auto& materialEditor = context.getMaterialEditor();
            resourceSerializer.serializeMaterialSet(materialEditor.getMaterials());
            resourceSerializer.serializeHeterogeneousMaterialSet(materialEditor.getHeterogeneousMaterials());

            json::SaveObjectVisitor visitor(json["root"], resourceSerializer);
            context.getScene().getRoot().visitNode(visitor);
        }
    }

    void JSONSerializer::deserializeFromJSON(const Context& context, nlohmann::json& json) {
        {
            auto& materialEditor = context.getMaterialEditor();
            json::ResourceDeserializer resourceDeserializer(
                context.getMacroSet(),
                materialEditor.getMaterials(),
                materialEditor.getHeterogeneousMaterials()
            );
            resourceDeserializer.deserializeResources(json);

            json::ObjectDeserializer objectDeserializer(resourceDeserializer);
            objectDeserializer.applyGroupNode(json["root"], context.getScene().getRoot());
        }
    }
} // hs