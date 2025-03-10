//
// Created by Alberto Elorza Rubio on 21/01/2024.
//

#include "FileDocument.h"
#include "../app/exceptions/ApplicationError.h"

#include <fstream>
#include <sstream>

namespace hs {
    FileDocument::FileDocument(std::string file, Serializer& serializer, const Context& context) :
        file(std::move(file)), serializer(serializer), context(context)
    {

    }

    void FileDocument::load() {
        std::ifstream input(file);
        if (!input.is_open())
            throw ApplicationError("Error opening file", "Unable to open the file", ApplicationErrorTopic::FileSystem);

        std::stringstream source;
        source << input.rdbuf();
        input.close();
        context.getCommandHistory().clear();
        // TODO: Clear all context
        serializer.deserialize(context, source.str());
    }

    void FileDocument::save() {
        std::ofstream output(file);
        if (!output.is_open())
            throw ApplicationError("Error saving file", "Unable to open the file", ApplicationErrorTopic::FileSystem);

        std::string data = serializer.serialize(context);
        output << data;
        output.close();
        context.getCommandHistory().setCheckpoint();
    }

    const std::string& FileDocument::getResource() {
        return file;
    }
} // hs