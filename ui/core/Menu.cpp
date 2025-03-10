//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#include "Menu.h"

#include <imgui.h>

namespace hs {
    void MenuSeparator::renderMenuNode() {
        ImGui::Separator();
    }

    const char* Menu::DEFAULT_TITLE = "<NO TITLE>";

    Menu::Menu(std::string title): title(std::move(title)), nodes() {

    }

    void Menu::renderMenuNode() {
        if (ImGui::BeginMenu(title.c_str())) {
            renderNodes();
            ImGui::EndMenu();
        }
    }

    void Menu::addItem(std::shared_ptr<MenuNode> node) {
        nodes.push_back(std::move(node));
    }

    void Menu::addSeparator() {
        nodes.push_back(std::make_unique<MenuSeparator>());
    }

    void Menu::renderMainMenu() {
        if (ImGui::BeginMainMenuBar()) {
            renderNodes();
            ImGui::EndMainMenuBar();
        }
    }

    void Menu::renderWindowMenu() {
        if (ImGui::BeginMenuBar()) {
            renderNodes();
            ImGui::EndMenuBar();
        }
    }

    void Menu::renderContextMenu() {
        if (ImGui::BeginPopupContextWindow()) {
            renderNodes();
            ImGui::EndPopup();
        }
    }

    bool Menu::empty() const {
        return nodes.empty();
    }

    void Menu::renderNodes() {
        for (const auto& node : nodes)
            node->renderMenuNode();
    }
} // hs