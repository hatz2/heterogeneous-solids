//
// Created by Alberto Elorza Rubio on 05/12/2023.
//

#include "HeterogeneousSolidFactory.h"
#include "CellAggregator.h"
#include <array>

namespace hs::HeterogeneousSolidFactory {
    std::vector<glm::vec2> calculateBezierCircularPath(unsigned int maxCells, bool rotated) {
        std::vector<glm::vec2> circularPath;

        float angleRad1 = (glm::pi<float>() * 2.f) / float(maxCells);
        float angleRad = glm::pi<float>() / (2.f * float(maxCells));
        float tang = glm::tan(angleRad);
        float f = (4.f/3.f) * tang;

        for (int i = 0; i < maxCells; i++) {
            glm::vec2 p0 = { glm::cos(float(i) * angleRad1), glm::sin(float(i) * angleRad1) };
            glm::vec2 p3 = { glm::cos(float(i + 1) * angleRad1), glm::sin(float(i + 1) * angleRad1) };

            glm::vec2 p1 = { p0.x - (p0.y * f), p0.y + (p0.x * f) };
            glm::vec2 p2 = { p3.x + (p3.y * f), p3.y - (p3.x * f) };

            circularPath.push_back(p0);
            circularPath.push_back(p1);
            circularPath.push_back(p2);
        }

        if (rotated) {
            float cs = glm::cos(glm::pi<float>()/4);
            float sn = glm::sin(glm::pi<float>()/4);
            std::vector<glm::vec2> flipped;
            for (glm::vec2 v : circularPath)
                flipped.emplace_back((v.x * cs) - (v.y * sn), (v.x * sn) + (v.y * cs));
            circularPath = flipped;
        }

        return circularPath;
    }

    void addGridOfCells(CellAggregator& aggregator,
        unsigned int cellsI, unsigned int cellsJ, unsigned int cellsK,
        float sizeX, float sizeY, float sizeZ,
        float dispX, float dispY, float dispZ
    ) {
        float initX = -(sizeX * float(cellsI)) / 2.f;
        float initY = -(sizeY * float(cellsJ)) / 2.f;
        float initZ = -(sizeZ * float(cellsK)) / 2.f;

        auto calcShapeCoefs = [&](float initXCell, float initYCell, float initZCell) {
            std::array<glm::vec3, 64> shapeCoefs{};
            for (int i = 0; i <= 3; i++) {
                int ii = i * 16;
                for (int j = 0; j <= 3; j++) {
                    int jj = j * 4;
                    for (int k = 0; k <= 3; k++)
                        shapeCoefs[ii + jj + k] = glm::vec3{
                            initXCell + (float(i) * sizeX / 3.f) + dispX,
                            initYCell + (float(j) * sizeY / 3.f) + dispY,
                            initZCell + (float(k) * sizeZ / 3.f) + dispZ
                        };
                }
            }
            return shapeCoefs;
        };

        for (int i = 0; i < cellsI; i++) {
            for (int j = 0; j < cellsJ; j++) {
                for (int k = 0; k < cellsK; k++) {
                    aggregator.addNewCell(calcShapeCoefs(
                        initX + (float(i) * sizeX),
                        initY + (float(j) * sizeY),
                        initZ + (float(k) * sizeZ)
                    ));
                }
            }
        }
    }

    void addRingOfCells(CellAggregator& aggregator,
        unsigned int cells, unsigned int maxCells, float innerRadius,
        unsigned int xCells, unsigned int yCells,
        float xSize, float ySize,
        float dispX, float dispY, float dispZ
    ) {
        auto path = calculateBezierCircularPath(maxCells);

        float initLen = innerRadius;
        float initY = -(ySize * float(yCells)) / 2.f;
        int nPointsRev = (3 * int(cells)) + 1;

        auto calcShapeCoefs = [&](int x, int y, int z) {
            std::array<glm::vec3, 64> shapeCoefs{};
            for (int i = 0; i <= 3; i++) {
                int ii = i * 16;
                for (int j = 0; j <= 3; j++) {
                    int jj = j * 4;
                    for (int k = 0; k <= 3; k++) {
                        int idxI = cells == maxCells ? ((z * 3) + k) % (nPointsRev - 1) : ((z * 3) + k);
                        shapeCoefs[ii + jj + k] = glm::vec3{
                            (path[idxI].x * (initLen + (xSize / 3.0) * float(i) + (xSize * float(x)))) + dispX,
                            -(path[idxI].y * (initLen + (xSize / 3.0) * float(i) + (xSize * float(x)))) + dispY,
                            (initY + (float(y) * ySize) + (float(j) * (ySize / 3.0))) + dispZ
                        };
                    }
                }
            }
            return shapeCoefs;
        };

        for (int x = 0; x < xCells; x++) {
            for (int y = 0; y < yCells; y++) {
                for (int z = 0; z < cells; z++) {
                    aggregator.addNewCell(calcShapeCoefs(x, y, z));
                }
            }
        }
    }

    std::unique_ptr<HeterogeneousSolid> createParallelepipedShapedSolid(const std::string& name,
        unsigned int cellsI, unsigned int cellsJ, unsigned int cellsK,
        float sizeX, float sizeY, float sizeZ, float dispX, float dispY, float dispZ
    ) {
        std::unique_ptr<HeterogeneousSolid> solid = std::make_unique<HeterogeneousSolid>(name);
        CellAggregator aggregator(*solid);

        addGridOfCells(aggregator, cellsI, cellsJ, cellsK, sizeX, sizeY, sizeZ, dispX, dispY, dispZ);

        return solid;
    }

    std::unique_ptr<HeterogeneousSolid> createLShapedSolid(const std::string& name) {
        std::unique_ptr<HeterogeneousSolid> solid = std::make_unique<HeterogeneousSolid>(name);
        CellAggregator aggregator(*solid);

        addGridOfCells(aggregator, 2, 1, 3, 5, 5, 5, 0, -2.5, 0);
        addGridOfCells(aggregator, 2, 2, 1, 5, 5, 5, 0, 5, -5);

        return solid;
    }

    std::unique_ptr<HeterogeneousSolid> createDoubleLShapedSolid(const std::string& name) {
        std::unique_ptr<HeterogeneousSolid> solid = std::make_unique<HeterogeneousSolid>(name);
        CellAggregator aggregator(*solid);

        addGridOfCells(aggregator, 4, 1, 2, 5, 2, 5, 0, -1, 0);
        addGridOfCells(aggregator, 2, 2, 2, 5, 2, 5, 0, 2, 0);

        return solid;
    }

    std::unique_ptr<HeterogeneousSolid> createDoubleTShapedSolid(const std::string& name) {
        std::unique_ptr<HeterogeneousSolid> solid = std::make_unique<HeterogeneousSolid>(name);
        CellAggregator aggregator(*solid);

        addGridOfCells(aggregator, 6, 1, 2, 5, 2, 5, 0, -1, 0);
        addGridOfCells(aggregator, 2, 1, 8, 5, 2, 5, 0, -1, 0);
        addGridOfCells(aggregator, 2, 4, 2, 5, 2, 5, 0, 4, 0);

        return solid;
    }

    std::unique_ptr<HeterogeneousSolid> createBoneShapedSolid(const std::string& name) {
        std::unique_ptr<HeterogeneousSolid> solid = std::make_unique<HeterogeneousSolid>(name);
        CellAggregator aggregator(*solid);

        addGridOfCells(aggregator, 3, 2, 2, 5, 1, 5, 0, 0, 0);
        addGridOfCells(aggregator, 2, 2, 4, 5, 1, 5, -12.5, 0, 0);
        addGridOfCells(aggregator, 2, 2, 4, 5, 1, 5, 12.5, 0, 0);
        addGridOfCells(aggregator, 1, 2, 2, 5, 5, 5, -5, 6, 0);
        addGridOfCells(aggregator, 1, 2, 2, 5, 5, 5, 5, 6, 0);

        return solid;
    }

    std::unique_ptr<HeterogeneousSolid> createRingShapedSolid(const std::string& name,
        unsigned int cells, int maxCells, float innerRadius, int xCells, int yCells,
        float xSize, float ySize, float dispX, float dispY, float dispZ
    ) {
        std::unique_ptr<HeterogeneousSolid> solid = std::make_unique<HeterogeneousSolid>(name);
        CellAggregator aggregator(*solid);

        addRingOfCells(aggregator, cells, maxCells, innerRadius, xCells, yCells, xSize, ySize, dispX, dispY, dispZ);

        return solid;
    }

    std::unique_ptr<HeterogeneousSolid> createHeterogeneousBar1(const std::string &name) {
        std::unique_ptr<HeterogeneousSolid> solid = std::make_unique<HeterogeneousSolid>(name);
        CellAggregator aggregator(*solid);

        addGridOfCells(aggregator, 1, 1, 1, 25, 5, 10, 0, 0, 0);

        auto& cells = solid->getCells();

        // TODO: materialcoefs

        const int basePeriod = 21;
        //cells[0]->setPerlinPeriod({ basePeriod * 5, basePeriod, basePeriod * 2  });

        return solid;
    }
} // hs