//
// Created by Alberto Elorza Rubio on 29/11/2023.
//

#include "LightSet.h"

namespace hs {
    LightSet::LightSet():
        ambientLight("Default Ambient Light", LightType::Ambient),
        modelingLight("Default Modeling Light", LightType::Directional),
        customLights(),
        compiledLights(),
        editingLight(-1)
    {
        ambientLight.getLightProps().setIA({0.3, 0.3, 0.3});
        modelingLight.getLightProps().setID({0.5, 0.5, 0.5});
        modelingLight.getLightProps().setIS(glm::vec3{0});

        Light lightA("Primary Light", LightType::Directional);
        lightA.getLightProps().setPosition({0, 0, 0});
        lightA.getLightProps().setLookAt({-1, -1, -1});
        lightA.getLightProps().setID(glm::vec3(0.7));
        lightA.getLightProps().setIS(glm::vec3(0.7));

        Light lightB("Secondary Light", LightType::Directional);
        lightB.getLightProps().setPosition({0, 0, 0});
        lightB.getLightProps().setLookAt({1, 1, 1});
        lightB.getLightProps().setID(glm::vec3(0.7));
        lightB.getLightProps().setIS(glm::vec3(0.7));

        customLights.push_back(lightA);
        customLights.push_back(lightB);
        compile();
    }

    Light& LightSet::getAmbientLight() {
        return ambientLight;
    }

    Light& LightSet::getModelingLight() {
        return modelingLight;
    }

    std::vector<Light>& LightSet::getCustomLights() {
        return customLights;
    }

    void LightSet::removeEditingLight() {
        if (editingLight >= 0)
            customLights.erase(std::next(customLights.begin(), editingLight));
    }

    void LightSet::pushNewCustomLight(const std::string& name, LightType type) {
        customLights.emplace_back(name, type);
        if (!modelingLight.isEnabled()) compile();
    }

    void LightSet::compile() {
        compiledLights.clear();
        if (ambientLight.isEnabled())
            compiledLights.push_back(std::ref(ambientLight));
        if (modelingLight.isEnabled()) {
            compiledLights.push_back(std::ref(modelingLight));
        } else {
            for (auto& light: customLights)
                if (light.isEnabled())
                    compiledLights.push_back(std::ref(light));
        }
    }

    void LightSet::setEditingLight(int light) {
        editingLight = light >= customLights.size() ? -1 : light;
    }

    int LightSet::getEditingLight() {
        if (editingLight >= customLights.size()) editingLight = -1;
        return editingLight;
    }

    LightSet::iterator LightSet::begin() noexcept {
        return compiledLights.begin();
    }

    LightSet::iterator LightSet::end() noexcept {
        return compiledLights.end();
    }
} // hs