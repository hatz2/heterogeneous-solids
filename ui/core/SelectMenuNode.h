//
// Created by Alberto Elorza Rubio on 09/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SELECTMENUNODE_H
#define HETEROGENEOUS_SOLIDS_SELECTMENUNODE_H

#include <vector>
#include <string>
#include "MenuNode.h"

namespace hs {

    class SelectMenuNode: public MenuNode {
    public:
        explicit SelectMenuNode(int& result);
        SelectMenuNode(const SelectMenuNode&) = delete;

        void addOption(std::string option);
        void clearOptions();

        void renderMenuNode() override;
    private:
        int& result;
        std::vector<std::string> options;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SELECTMENUNODE_H
