//
// Created by Alberto Elorza Rubio on 05/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SHADERMANAGER_H
#define HETEROGENEOUS_SOLIDS_SHADERMANAGER_H

#include "../utils/MapCache.h"
#include "ShaderProgram.h"
#include <optional>
#include <set>

namespace hs {

    struct ShaderSource {
        std::string content;
        std::string origin;
    };

    struct ShaderProgramSources {
        std::vector<ShaderSource> vertexSources;
        std::vector<ShaderSource> fragmentSources;
        std::vector<ShaderSource> geometrySources;
    };

    class ShaderIO {
    public:
        virtual const std::set<std::string>& getShaderPrograms() = 0;
        virtual std::optional<std::shared_ptr<ShaderProgramSources>> getProgramSources(const std::string& name) = 0;

        virtual ~ShaderIO() = default;
    };

    struct ShaderProgramSlot {
        std::shared_ptr<ShaderProgram> shaderProgram;
        ShaderProgramSources sources;
        std::string name;
    };

    class ShaderManager {
    public:
        explicit ShaderManager(ShaderIO& shaderIO);

        ShaderManager(const ShaderManager&) = delete;

        std::shared_ptr<ShaderProgram> requireShaderProgram(const std::string& name);
        std::optional<ShaderProgramSources> getShaderSources(const std::string& name);
        void updateProgramSources(const std::string& name, const ShaderProgramSources &sources);

        const std::set<std::string>& getShaderPrograms();
    private:
        std::map<std::string, ShaderProgramSlot> shaderProgramSlots;
        ShaderIO& shaderIO;

        // Update sources do not recompile nor link, in order to prevent throwing an error outside the rendering
        static void updateSources(ShaderProgramSlot& slot);

        std::map<std::string, ShaderProgramSlot>::iterator ensureProgramSlot(const std::string& name);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SHADERMANAGER_H
