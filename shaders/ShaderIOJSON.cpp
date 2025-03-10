//
// Created by Alberto Elorza Rubio on 25/01/2024.
//

#include "ShaderIOJSON.h"
#include "ShaderError.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

namespace hs {
    ShaderIOJSON::ShaderIOJSON(Resources& resources) : resources(resources), indexLoaded(false) {

    }

    const std::set<std::string>& ShaderIOJSON::getShaderPrograms() {
        if (!indexLoaded) loadIndex();
        return programs;
    }

    std::optional<std::shared_ptr<ShaderProgramSources>> ShaderIOJSON::getProgramSources(const std::string& name) {
        if (!indexLoaded) loadIndex();
        auto program = programsData.find(name);
        if (program != programsData.end())
            return program->second;

        auto sources = index.find(name);
        if (sources == index.end()) throw ShaderError(("Requested program is not indexed: " + name).c_str());

        auto data = loadSources(sources->second);
        programsData.insert({ name, data });
        return data;
    }

    void ShaderIOJSON::loadIndex() {
        // TODO: Remove temporary hardcoded assets directory
        std::ifstream file(resources.getShader("shaders.json"));
        if (!file.is_open()) throw ShaderError("Unable to open shader index");
        std::stringstream source;
        source << file.rdbuf();
        nlohmann::json data = nlohmann::json::parse(source.str());
        file.close();
        for (const auto& [name, value] : data.items()) {
            std::vector<std::string> sources = value;
            index.insert({ name, sources });
            programs.insert(name);
        }
        indexLoaded = true;
    }

    std::shared_ptr<ShaderProgramSources> ShaderIOJSON::loadSources(const std::vector<std::string>& sources) {
        auto programData = std::make_shared<ShaderProgramSources>();
        for (auto& sourceName : sources) {
            std::filesystem::path sourcePath = resources.getShader(sourceName);

            std::vector<ShaderSource>* sourceTarget;
            std::string extension = sourcePath.extension().string();
            if (extension == ".vert") sourceTarget = &programData->vertexSources;
            else if (extension == ".frag") sourceTarget = &programData->fragmentSources;
            else if (extension == ".geom") sourceTarget = &programData->geometrySources;
            else throw ShaderError(("invalid shader extension: " + extension).c_str());

            std::ifstream file(sourcePath);
            if (!file.is_open()) throw ShaderError(("Unable to open shader source code: " + sourceName).c_str());

            std::stringstream source;
            source << file.rdbuf();

            sourceTarget->push_back({ source.str(), sourceName });
        }
        return programData;
    }
} // hs