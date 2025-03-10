//
// Created by Alberto Elorza Rubio on 18/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_STATEFULDIALOG_H
#define HETEROGENEOUS_SOLIDS_STATEFULDIALOG_H

#include "Dialog.h"

#include <imgui.h>
#include <memory>
#include <tuple>

namespace hs {

    template <typename ...Types>
    class StatefulDialog: public Dialog {
    public:
        explicit StatefulDialog(std::string title);
        void render() override;
        void show(Types&...);
    protected:
        DoClose renderBody() override;
        virtual DoClose renderBody(Types&...) = 0;
        std::unique_ptr<std::tuple<Types&...>> state;
    };

    template<typename ...Types>
    StatefulDialog<Types...>::StatefulDialog(std::string title) : Dialog(std::move(title)), state(nullptr) {

    }

    template<typename... Types>
    void StatefulDialog<Types...>::show(Types&... types) {
        state = std::make_unique<std::tuple<Types&...>>(types...);
        Dialog::show();
    }

    template<typename ...Types>
    Dialog::DoClose StatefulDialog<Types...>::renderBody() {
        return std::apply([this](Types&... args) {
            return this->renderBody(args...);
        }, *state);
    }

    template <typename ...Types>
    void StatefulDialog<Types...>::render() {
        if (requestShow) {
            ImGui::OpenPopup(title.c_str());
            requestShow = false;
        }
        bool open = true;
        if (ImGui::BeginPopupModal(title.c_str(), &open, ImGuiWindowFlags_AlwaysAutoResize)) {
            if (state == nullptr || !open || renderBody()) {
                state = nullptr;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }

} // hs

#endif //HETEROGENEOUS_SOLIDS_STATEFULDIALOG_H
