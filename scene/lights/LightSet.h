//
// Created by Alberto Elorza Rubio on 29/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_LIGHTSET_H
#define HETEROGENEOUS_SOLIDS_LIGHTSET_H

#include "Light.h"
#include "../Camera.h"

namespace hs {

    class LightSet {
    public:
        using iterator = std::vector<std::reference_wrapper<Light>>::iterator;

        LightSet();

        Light& getAmbientLight();
        Light& getModelingLight();
        std::vector<Light>& getCustomLights();

        void compile();

        void setEditingLight(int light);
        [[nodiscard]] int getEditingLight();
        void removeEditingLight();
        void pushNewCustomLight(const std::string& name, LightType type);

        iterator begin() noexcept;
        iterator end() noexcept;

        [[nodiscard]] const std::vector<std::reference_wrapper<Light>>& getCompiledLights() const;

    private:
        Light ambientLight;
        Light modelingLight;
        std::vector<Light> customLights;
        std::vector<std::reference_wrapper<Light>> compiledLights;
        int editingLight;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_LIGHTSET_H
