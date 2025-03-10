//
// Created by Alberto Elorza Rubio on 09/12/2023.
//

#include <imgui.h>
#include "SelectMenuNode.h"

namespace hs {
    SelectMenuNode::SelectMenuNode(int& result) : result(result) {

    }

    void SelectMenuNode::addOption(std::string option) {
        options.push_back(std::move(option));
    }

    void SelectMenuNode::clearOptions() {
        options.clear();
    }

    void SelectMenuNode::renderMenuNode() {
        result = -1;
        for (int i = 0; i < options.size(); i++) {
            if (ImGui::MenuItem(options[i].c_str())) result = i;
        }
    }
} // hs