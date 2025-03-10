//
// Created by Alberto Elorza Rubio on 13/12/2023.
//

#include "components.h"

#include <imgui.h>
#include "../bindings/IconsMaterialDesign.h"

namespace hs {

    bool lightTypeCombo(const char* label, LightType& lightType) {
        const char* items[] = { "Point", "Directional", "Spotlight" };
        int type = 0;
        switch (lightType) {
            case LightType::Ambient:
            case LightType::Point:
                type = 0;
                break;
            case LightType::Directional:
                type = 1;
                break;
            case LightType::SpotLight:
                type = 2;
                break;
        }
        if (ImGui::Combo(label, &type, items, 3)) {
            LightType variants[] = { LightType::Point, LightType::Directional, LightType::SpotLight };
            lightType = variants[type];
            return true;
        }
        return false;
    }

    bool visibilityBadge(bool& visible) {
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
        bool pressed = ImGui::SmallButton(visible ? ICON_MD_VISIBILITY : ICON_MD_VISIBILITY_OFF);
        ImGui::PopStyleColor();
        visible = visible != pressed;
        return pressed;
    }

    void alignForWidth(float width, float alignment) {
        ImGuiStyle& style = ImGui::GetStyle();
        float avail = ImGui::GetContentRegionAvail().x;
        float off = (avail - width) * alignment;
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
    }

    struct InputTextCallback_UserData {
        std::string*            Str;
        ImGuiInputTextCallback  ChainCallback;
        void*                   ChainCallbackUserData;
    };

    int InputTextCallback(ImGuiInputTextCallbackData* data) {
        auto* user_data = (InputTextCallback_UserData*)data->UserData;
        if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
            // Resize string callback
            // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
            std::string* str = user_data->Str;
            IM_ASSERT(data->Buf == str->c_str());
            str->resize(data->BufTextLen);
            data->Buf = (char*)str->c_str();
        } else if (user_data->ChainCallback) {
            // Forward to user callback, if any
            data->UserData = user_data->ChainCallbackUserData;
            return user_data->ChainCallback(data);
        }
        return 0;
    };

    bool InputText(
        const char* label,
        std::string* str,
        ImGuiInputTextFlags flags,
        ImGuiInputTextCallback callback,
        void* user_data
    ) {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        InputTextCallback_UserData cb_user_data{ str, callback, user_data };
        return ImGui::InputText(
            label, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data
        );
    }

    bool InputTextWithHint(
        const char* label,
        const char* hint,
        std::string* str,
        ImGuiInputTextFlags flags,
        ImGuiInputTextCallback callback,
        void* user_data
    ) {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        InputTextCallback_UserData cb_user_data{ str, callback, user_data };
        return ImGui::InputTextWithHint(
            label, hint, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data
        );
    }

    bool InputTextMultiline(
        const char* label,
        std::string* str,
        const ImVec2& size,
        ImGuiInputTextFlags flags,
        ImGuiInputTextCallback callback,
        void* user_data
    )  {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        InputTextCallback_UserData cb_user_data{ str, callback, user_data };
        return ImGui::InputTextMultiline(
            label, (char*)str->c_str(), str->capacity() + 1, size, flags, InputTextCallback, &cb_user_data
        );
    }
} // hs