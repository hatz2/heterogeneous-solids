//
// Created by Alberto Elorza Rubio on 01/02/2024.
//

#include "CellWindow.h"

#include "../../heterogeneous_solids/Cell.h"
#include "../components.h"
#include "../../command/basic/UpdateDescriptionCommand.h"
#include "../../command/basic/UpdateVisibilityCommand.h"
#include "../../command/basic/ApplyTranslationCommand.h"
#include "../../command/basic/SetCoefA0Command.h"
#include "../../command/basic/SetCoefContinuityCommand.h"

namespace hs {
    CellWindow::CellWindow(std::string title, std::shared_ptr<ContextManager> contextManager) :
        ContextWindow(std::move(title), std::move(contextManager))
    {

    }

    void CellWindow::renderBody(const Context& context) {
        auto& selector = context.getSelector();
        if (auto cell = selector.getCell())
            renderCell(context, cell.value());
        // TODO: Show all coefs
        /*if (ImGui::BeginListBox("##coefs", size)) {
            for (const auto& coef : cell.getShapeCoefs()) {
                ImGui::Text("%s", ShapeCoef::getNameFromType(coef->getType()));
            }
            ImGui::EndListBox();
        }*/
        if (auto coef = selector.getCellCoef())
            renderCoef(context, coef.value());
    }

    void CellWindow::renderCell(const Context& context, Cell& cell) {
        auto& state = cell.getState();

        std::string description = state.getDescription();
        if (InputTextWithHint("Description", state.getDefaultDescription().c_str(), &description))
            context.getCommandHistory().execute<UpdateDescriptionCommand>(description, state);

        bool visible = state.isVisible();
        if (ImGui::Checkbox("Show Object", &visible))
            context.getCommandHistory().execute<UpdateVisibilityCommand>(visible, state);

        ImGui::SeparatorText("Cell properties");
        glm::vec3 perlin = cell.getPerlinPeriod();
        if (ImGui::DragFloat3("Perlin Period", glm::value_ptr(perlin))) {
            cell.setPerlinPeriod(perlin);
        }
        ImGui::SeparatorText("Coefficients");
        auto size = ImGui::GetContentRegionAvail();
        auto minHeight = 10 * ImGui::GetTextLineHeight();
        if (size.y < minHeight) size.y = minHeight;
    }

    void CellWindow::renderCoef(const Context& context, CellCoef& coef) {
        auto renderSingleCoef = [&context](CellCoef& coef) {
            if (!ImGui::CollapsingHeader(
                (
                    coef.getState().getDescriptionOrDefault() +
                    " : " + coef.getCell().getState().getDescriptionOrDefault()
                ).c_str(), ImGuiTreeNodeFlags_DefaultOpen
            )) return;
            MaterialCoef& materialCoef = coef.getMaterialCoef();

            ImGui::PushID(&materialCoef);
            bool continuity = materialCoef.isKeepContinuity();
            if (ImGui::Checkbox("Keep Continuity", &continuity))
                context.getCommandHistory().execute<SetCoefContinuityCommand>(materialCoef, continuity);
            float a0 = materialCoef.getA0();
            if (ImGui::DragFloat("A0", &a0, 0.01, 0, 1))
                context.getCommandHistory().execute<SetCoefA0Command>(materialCoef, a0);
            ImGui::PopID();
        };
        auto shapeCoef = coef.getAttachedShapeCoef();
        if (shapeCoef) {
            ImGui::Text("Coefficient Type: %s", ShapeCoef::getNameFromType(shapeCoef.value()->getType()));
            ImGui::Spacing();
            for (auto coef : shapeCoef.value()->getSharedCoefs()) renderSingleCoef(*coef);
            ImGui::Spacing();
            ImGui::Separator();
            Transform& transform = shapeCoef.value()->getTransform();
            glm::vec3 shapeCoefPosition = transform.getTranslation();
            if (ImGui::DragFloat3("Position", glm::value_ptr(shapeCoefPosition), 0.01))
                context.getCommandHistory().execute<ApplyTranslationCommand>(transform, shapeCoefPosition, true);
        } else renderSingleCoef(coef);
    }
} // hs