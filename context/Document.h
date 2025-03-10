//
// Created by Alberto Elorza Rubio on 21/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_DOCUMENT_H
#define HETEROGENEOUS_SOLIDS_DOCUMENT_H

#include <string>

namespace hs {

    class Document {
    public:
        virtual void save() = 0;
        virtual void load() = 0;

        virtual const std::string& getResource() = 0;

        virtual ~Document() = default;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_DOCUMENT_H
