//
// Created by Alberto Elorza Rubio on 13/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_COMPONENTS_H
#define HETEROGENEOUS_SOLIDS_COMPONENTS_H

#include <imgui.h>
#include "../scene/lights/Light.h"

namespace hs {

    bool lightTypeCombo(const char* label, LightType& lightType);
    bool visibilityBadge(bool& visible);

    void alignForWidth(float width, float alignment = 0.5);

    bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
    bool InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
    bool InputTextMultiline(const char* label, std::string* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
} // hs

#endif //HETEROGENEOUS_SOLIDS_COMPONENTS_H
