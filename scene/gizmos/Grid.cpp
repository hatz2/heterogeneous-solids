//
// Created by Alberto Elorza Rubio on 05/12/2023.
//

#include "Grid.h"

namespace hs {
    GridResource::GridResource(unsigned int rows) : idVBO(0), idVAO(0), count(rows * 2) {
        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);
        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count * 4, nullptr, GL_STATIC_DRAW);

        for (int i = 0; i < rows; i++) {
            float offset = (i - (int)rows/4) * 2;
            float max = rows;
            float data[8] = {
                offset, -max,
                offset, max,
                -max, offset,
                max, offset
            };
            glBufferSubData(GL_ARRAY_BUFFER,  sizeof(float) * 8 * i,  sizeof(float) * 8, data);
        }

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);
    }

    GridResource::~GridResource() {
        if (idVAO) glDeleteVertexArrays(1, &idVAO);
        if (idVBO) glDeleteBuffers(1, &idVBO);
    }

    std::unique_ptr<GridResource> Grid::gridResource = nullptr;
    const unsigned int Grid::gridRows = 150;

    Grid::Grid() {
        if (!gridResource) gridResource = std::make_unique<GridResource>(Grid::gridRows);
    }

    void Grid::render(RenderContext& renderContext) {
        glBindVertexArray(gridResource->idVAO);
        glDrawArrays(GL_LINES, 0, gridResource->count);
    }
} // hs