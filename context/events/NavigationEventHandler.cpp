//
// Created by Alberto Elorza Rubio on 27/12/2023.
//

#include "NavigationEventHandler.h"
#include "../../command/basic/RemoveObjectCommand.h"

#include <iostream>

namespace hs {
    NavigationEventHandler::NavigationEventHandler(Selector& selector, CommandHistory& commandHistory) :
        selector(selector), commandHistory(commandHistory) {

    }

    void NavigationEventHandler::handle(const KeyEvent& event) {
        std::optional<std::reference_wrapper<SceneNode>> nextSelection = std::nullopt;
        switch (event.key) {
            case ImGuiKey_UpArrow:
                nextSelection = selector.getSelectedObject().getParent();
                break;
            case ImGuiKey_DownArrow:
                nextSelection = selector.getSelectedObject().getChild(0);
                break;
            case ImGuiKey_LeftArrow:
                nextSelection = selector.getSelectedObject().getPreviousSibling();
                break;
            case ImGuiKey_RightArrow:
                nextSelection = selector.getSelectedObject().getNextSibling();
                break;
            case ImGuiKey_Delete: {
                auto& node = selector.getSelectedObject();
                if (auto parent = node.getParent())
                    commandHistory.execute<RemoveObjectCommand>(node.getIndexInParent(), parent.value());
                break;
            }
            default:
                break;
        }
        if (nextSelection) {
            selector.select(nextSelection.value());
        }
    }
} // hs