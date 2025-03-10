//
// Created by Alberto Elorza Rubio on 05/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_HETEROGENEOUSSOLIDFACTORY_H
#define HETEROGENEOUS_SOLIDS_HETEROGENEOUSSOLIDFACTORY_H

#include <glm/glm.hpp>
#include "../HeterogeneousSolid.h"
#include "CellAggregator.h"

namespace hs::HeterogeneousSolidFactory {

    std::vector<glm::vec2> calculateBezierCircularPath(unsigned int maxCells, bool rotated = false);

    void addGridOfCells(CellAggregator& aggregator,
        unsigned int cellsI = 1, unsigned int cellsJ = 1, unsigned int cellsK = 1,
        float sizeX = 1, float sizeY = 1, float sizeZ = 1,
        float dispX = 0, float dispY = 0, float dispZ = 0
    );

    void addRingOfCells(CellAggregator& aggregator,
        unsigned int cells = 4, unsigned int maxCells = 4, float innerRadius = 1.,
        unsigned int xCells = 1, unsigned int yCells = 1,
        float xSize = 1., float ySize = 1.,
        float dispX = 0., float dispY = 0., float dispZ = 0.
    );

    std::unique_ptr<HeterogeneousSolid> createParallelepipedShapedSolid(const std::string& name,
        unsigned int cellsI = 1, unsigned int cellsJ = 1, unsigned int cellsK = 1,
        float sizeX = 1, float sizeY = 1, float sizeZ = 1,
        float dispX = 0, float dispY = 0, float dispZ = 0
    );

    std::unique_ptr<HeterogeneousSolid> createLShapedSolid(const std::string& name);

    std::unique_ptr<HeterogeneousSolid> createDoubleLShapedSolid(const std::string& name);

    std::unique_ptr<HeterogeneousSolid> createDoubleTShapedSolid(const std::string& name);

    std::unique_ptr<HeterogeneousSolid> createBoneShapedSolid(const std::string& name);

    std::unique_ptr<HeterogeneousSolid> createRingShapedSolid(const std::string& name,
        unsigned int cells = 4, int maxCells = 4, float innerRadius = 1,
        int xCells = 1, int yCells = 1, float xSize = 1, float ySize = 1,
        float dispX = 0, float dispY = 0, float dispZ = 0
    );

    std::unique_ptr<HeterogeneousSolid> createHeterogeneousBar1(const std::string& name);
} // hs

#endif //HETEROGENEOUS_SOLIDS_HETEROGENEOUSSOLIDFACTORY_H
