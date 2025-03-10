//
// Created by Alberto Elorza Rubio on 05/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_GRID_H
#define HETEROGENEOUS_SOLIDS_GRID_H

#include "../objects/SceneNode.h"
#include "../Camera.h"

namespace hs {

    class GridResource {
    private:
        GLuint idVBO;
        GLuint idVAO;
        GLuint count;
        friend class Grid;
    public:
        explicit GridResource(unsigned int rows);
        ~GridResource();

        GridResource(const GridResource&) = delete;
        GridResource& operator=(const GridResource&) = default;
    };

    class Grid {
    private:
        static std::unique_ptr<GridResource> gridResource;
        static const unsigned int gridRows;
    public:
        Grid();
        void render(hs::RenderContext& renderContext);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_GRID_H
