//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_MENUNODE_H
#define HETEROGENEOUS_SOLIDS_MENUNODE_H

namespace hs {

    class MenuNode {
    public:
        virtual void renderMenuNode() = 0;
        virtual ~MenuNode() = default;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MENUNODE_H
