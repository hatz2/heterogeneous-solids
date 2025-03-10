//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#include "IsoSurface.h"
#include "../BezierData.h"
#include "../utils.h"

namespace hs {
    void IsoSurface::recalculateU() {
        auto resolution = trimmedCell.getMainCell().getSharedData().getBezierResolution();
        auto& trimmedCoefs = trimmedCell.getTrimmedCoefs();

        float param = 1.f / (resolution - 1.f);

        glm::vec3 pt(0), tgS(0), tgT(0);
        float Bi, Bj, BDi, BDj;

        pointsAndTgsInU.clear();

        for (int u = 0; u < (int)resolution; u++) {
            float uu = param * (float)u;
            for (int v = 0; v < (int)resolution; v++) {
                float vv = param * (float)v;
                pt = {}, tgS = {}, tgT = {};
                for (int i = 0; i <= 3; i++) {
                    Bi = B(i, uu),
                    BDi = BD(i, uu);
                    for (int j = 0; j <= 3; j++) {
                        Bj = B(j, vv),
                        BDj = BD(j, vv);

                        auto& coef = trimmedCoefs[surfaceCoefs[(i*4) + j]];

                        pt += coef * Bi * Bj;
                        tgS += coef * BDi * Bj;
                        tgT += coef * Bi * BDj;
                    }
                }
                tgS = glm::normalize(tgS);
                tgT = glm::normalize(tgT);

                pointsAndTgsInU.push_back({ pt, tgS, tgT });
            }
        }

        if (auto parent = trimmedCell.getParentTrimmedCell()) {
            pointsAndTgsInU = parent->get().evaluatePointsAndTangents(pointsAndTgsInU);
        }
    }

    void IsoSurface::recalculateR() {
        std::vector<glm::vec3> pointsInR;
        std::vector<glm::vec3> normalsInR;

        std::vector<glm::vec3> pointsInU;
        for (PointAndTangentsST pointAndTgs : pointsAndTgsInU) pointsInU.push_back(pointAndTgs.point);
        auto pointsAndTgsInR = trimmedCell.getMainCell().evaluatePointAndTangents(pointsInU);

        for (int idx = 0; idx < pointsAndTgsInU.size(); idx++) {
            pointsInR.push_back(pointsAndTgsInR[idx].point);
            glm::vec3 tgSInR =  (pointsAndTgsInR[idx].tgU * pointsAndTgsInU[idx].tgS.x) +
                                (pointsAndTgsInR[idx].tgV * pointsAndTgsInU[idx].tgS.y) +
                                (pointsAndTgsInR[idx].tgW * pointsAndTgsInU[idx].tgS.z);
            glm::vec3 tgTInR =  (pointsAndTgsInR[idx].tgU * pointsAndTgsInU[idx].tgT.x) +
                                (pointsAndTgsInR[idx].tgV * pointsAndTgsInU[idx].tgT.y) +
                                (pointsAndTgsInR[idx].tgW * pointsAndTgsInU[idx].tgT.z);
            normalsInR.push_back(glm::normalize(glm::cross(tgSInR, tgTInR)));
        }

        normalField = std::make_unique<NormalField>(pointsInR, normalsInR);

        auto resolution = trimmedCell.getMainCell().getSharedData().getBezierResolution();

        std::vector<unsigned int> indices;
        for (int row = 0; row < (int)resolution - 1; row++) {
            int rowOffset = row * (int) resolution;
            for (int offset = 0; offset < (int) resolution - 1; offset++) {
                indices.push_back(rowOffset + offset);
                indices.push_back(rowOffset + (int) resolution + offset);
                indices.push_back(rowOffset + offset + 1);
                indices.push_back(rowOffset + offset + 1);
                indices.push_back(rowOffset + (int) resolution + offset);
                indices.push_back(rowOffset + (int) resolution + offset + 1);
            }
        }

        mesh = std::make_unique<Mesh>(indices, pointsInR, normalsInR, pointsInU);
    }

    IsoSurface::IsoSurface(const std::array<unsigned int, 16>& surfaceCoefs, TrimmedCell& trimmedCell):
        surfaceCoefs(surfaceCoefs), trimmedCell(trimmedCell), needsRecalcU(true), needsRecalcR(true)
    {

    }

    void IsoSurface::recalculate() {
        if (needsRecalcU) {
            recalculateU();
            needsRecalcU = false;
        }

        if (needsRecalcR) {
            recalculateR();
            needsRecalcR = false;
        }
    }

    void IsoSurface::needRecalculation(bool U, bool R) {
        needsRecalcU = U;
        needsRecalcR = R;
    }

    void IsoSurface::render(RenderContext& context) {
        recalculate();
        if (context.getRenderMode() == RenderMode::Normals) normalField->render(context);
        else mesh->render(context);
    }
} // hs