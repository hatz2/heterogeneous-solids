//
// Created by Alberto Elorza Rubio on 25/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SHADERIOJSON_H
#define HETEROGENEOUS_SOLIDS_SHADERIOJSON_H

#include "ShaderManager.h"
#include "../io/Resources.h"

#include <map>
#include <vector>

namespace hs {

    class ShaderIOJSON : public ShaderIO {
    public:
        explicit ShaderIOJSON(Resources& resources);

        const std::set<std::string>& getShaderPrograms() override;
        std::optional<std::shared_ptr<ShaderProgramSources>> getProgramSources(const std::string& name) override;
    private:
        Resources& resources;
        void loadIndex();
        std::shared_ptr<ShaderProgramSources> loadSources(const std::vector<std::string>& sources);

        std::map<std::string, std::vector<std::string>> index;
        std::set<std::string> programs;
        bool indexLoaded;
        std::map<std::string, std::shared_ptr<ShaderProgramSources>> programsData;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SHADERIOJSON_H
