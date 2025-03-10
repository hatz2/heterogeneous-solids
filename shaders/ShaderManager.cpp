//
// Created by Alberto Elorza Rubio on 05/12/2023.
//

#include "ShaderManager.h"
#include "ShaderError.h"

#include <numeric>
#include <spdlog/spdlog.h>

namespace hs {
    ShaderManager::ShaderManager(ShaderIO& shaderIO) : shaderProgramSlots(), shaderIO(shaderIO) {

    }

    std::shared_ptr<ShaderProgram> ShaderManager::requireShaderProgram(const std::string& name) {
        return ensureProgramSlot(name)->second.shaderProgram;
    }

    const std::set<std::string>& ShaderManager::getShaderPrograms() {
        return shaderIO.getShaderPrograms();
    }

    std::optional<ShaderProgramSources> ShaderManager::getShaderSources(const std::string& name) {
        return ensureProgramSlot(name)->second.sources;
    }

    void ShaderManager::updateProgramSources(const std::string& name, const ShaderProgramSources& sources) {
        auto& slot = ensureProgramSlot(name)->second;
        slot.sources = sources;
        updateSources(slot);
    }

    void ShaderManager::updateSources(ShaderProgramSlot& slot) {
        auto& sources = slot.sources;
        auto& program = slot.shaderProgram;

        auto writeShaderData = [](Shader& shader, const std::vector<ShaderSource>& sources) {
            // At this point is ensured sources is > 0
            std::string content = sources.front().content;
            std::string name = sources.front().origin;
            for (auto source = sources.begin() + 1; source != sources.end(); source++) {
                content += "\n" + source->content;
                name += ", " + source->origin;
            }
            shader.setSource(content);
            shader.setName(name);
        };

        if (sources.vertexSources.empty()) {
            program->setVertexShader(nullptr);
            spdlog::warn("Creating shader program without vertex: {}", slot.name);
        } else {
            auto shader = program->getVertexShader();
            if (!shader) {
                shader = std::make_shared<Shader>(GL_VERTEX_SHADER);
                program->setVertexShader(shader);
            }
            writeShaderData(*shader, sources.vertexSources);
        }

        if (sources.fragmentSources.empty()) {
            program->setFragmentShader(nullptr);
            spdlog::warn("Creating shader program without fragment: {}", slot.name);
        } else {
            auto shader = program->getFragmentShader();
            if (!shader) {
                shader = std::make_shared<Shader>(GL_FRAGMENT_SHADER);
                program->setFragmentShader(shader);
            }
            writeShaderData(*shader, sources.fragmentSources);
        }

        if (sources.geometrySources.empty()) program->setGeometryShader(nullptr);
        else {
            auto shader = program->getGeometryShader();
            if (!shader) {
                shader = std::make_shared<Shader>(GL_GEOMETRY_SHADER);
                program->setGeometryShader(shader);
            }
            writeShaderData(*shader, sources.geometrySources);
        }

        program->requireLink();
    }

    std::map<std::string, ShaderProgramSlot>::iterator ShaderManager::ensureProgramSlot(const std::string& name) {
        {
            auto slot = shaderProgramSlots.find(name);
            if (slot != shaderProgramSlots.end()) return slot;
        }

        auto sources = shaderIO.getProgramSources(name);
        if (!sources) throw ShaderError("Shader not found");

        auto shaderProgram = std::make_shared<ShaderProgram>();
        shaderProgram->setName(name);
        auto slot = shaderProgramSlots.insert({name, {
            shaderProgram,
            *sources.value(),
            name
        }});
        updateSources(slot.first->second);

        return slot.first;
    }
} // hs