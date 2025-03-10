//
// Created by Alberto Elorza Rubio on 13/12/2023.
//

#include "AddLightDialog.h"

#include "imgui.h"
#include "../components.h"

namespace hs {
    const std::string AddLightDialog::DefaultName = "New Light";

    AddLightDialog::AddLightDialog(std::string title, std::shared_ptr<ContextManager> contextManager):
        ContextDialog(std::move(title), std::move(contextManager)), name(DefaultName), lightType(LightType::Point)
    {

    }

    void AddLightDialog::reset() {
        lightType = LightType::Point;
        name = DefaultName;
    }

    Dialog::DoClose AddLightDialog::renderBody(const Context& context) {
        InputText("Name", &name);
        lightTypeCombo("Type", lightType);
        auto size = ImGui::GetContentRegionAvail().x / 4;
        if (ImGui::Button("Reset", ImVec2(size, 0))) {
            reset();
        }
        ImGui::SameLine(0, size * 2);
        if (ImGui::Button("Confirm", ImVec2(size, 0))) {
            context.getScene().getLights().pushNewCustomLight(name, lightType);
            return true;
        }
        return false;
    }
} // hs