//
// Created by Alberto Elorza Rubio on 20/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_JSONSERIALIZER_H
#define HETEROGENEOUS_SOLIDS_JSONSERIALIZER_H

#include "../Serializer.h"
#include <nlohmann/json.hpp>

namespace hs {

    class JSONSerializer: public Serializer {
    public:
        explicit JSONSerializer(unsigned char indent = 2);

        std::string serialize(const Context& context) override;
        void deserialize(const Context& context, const std::string& source) override;

        static void serializeToJSON(const Context& context, nlohmann::json& json);
        static void deserializeFromJSON(const Context& context, nlohmann::json& json);
    private:
        unsigned char indent;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_JSONSERIALIZER_H
