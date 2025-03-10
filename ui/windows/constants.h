//
// Created by Alberto Elorza Rubio on 10/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_CONSTANTS_H
#define HETEROGENEOUS_SOLIDS_CONSTANTS_H

#include <imgui.h>

namespace hs {

    const ImGuiTreeNodeFlags_ DefaultTreeBranchFlags = static_cast<const ImGuiTreeNodeFlags_>(
        ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick
    );

    const ImGuiTreeNodeFlags_ DefaultOpenTreeBranchFlags = static_cast<const ImGuiTreeNodeFlags_>(
        ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick
    );

    const ImGuiTreeNodeFlags_ DefaultTreeLeafFlags = static_cast<const ImGuiTreeNodeFlags_>(
        ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen
    );

} // hs

#endif //HETEROGENEOUS_SOLIDS_CONSTANTS_H
