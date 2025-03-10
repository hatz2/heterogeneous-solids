//
// Created by Alberto Elorza Rubio on 12/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_RESOURCES_H
#define HETEROGENEOUS_SOLIDS_RESOURCES_H

#include <string>
#include <filesystem>

namespace hs {

    class Resources {
    public:
        /**
         * Resources will be always instanced with the path of the executable
         * @param executablePath the path of the executable
         */
        explicit Resources(const std::filesystem::path& executablePath);

        [[nodiscard]] std::filesystem::path getFont(const std::string& fontName) const;
        [[nodiscard]] std::filesystem::path getShader(const std::string& shaderName) const;
        [[nodiscard]] std::filesystem::path getModel(const std::string& modelName) const;
    private:
        std::filesystem::path resourcesPath;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_RESOURCES_H
