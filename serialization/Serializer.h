//
// Created by Alberto Elorza Rubio on 18/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SERIALIZER_H
#define HETEROGENEOUS_SOLIDS_SERIALIZER_H

#include "../context/Context.h"

namespace hs {

    class Serializer {
    public:
        virtual std::string serialize(const Context& context) = 0;
        virtual void deserialize(const Context& context, const std::string& source) = 0;

        virtual ~Serializer() = default;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SERIALIZER_H
