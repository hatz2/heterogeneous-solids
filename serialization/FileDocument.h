//
// Created by Alberto Elorza Rubio on 21/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_FILEDOCUMENT_H
#define HETEROGENEOUS_SOLIDS_FILEDOCUMENT_H

#include "../context/Document.h"
#include "Serializer.h"

namespace hs {

    class FileDocument: public Document {
    public:
        FileDocument(std::string file, Serializer& serializer, const Context& context);

        void load() override;
        void save() override;

        const std::string& getResource() override;
    private:
        std::string file;
        Serializer& serializer;
        const Context& context;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_FILEDOCUMENT_H
