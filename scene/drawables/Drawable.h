//
// Created by Alberto Elorza Rubio on 01/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_DRAWABLE_H
#define HETEROGENEOUS_SOLIDS_DRAWABLE_H

#include "../RenderContext.h"

namespace hs {

    class Drawable {
    public:
        virtual void render(RenderContext& renderContext) = 0;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_DRAWABLE_H
