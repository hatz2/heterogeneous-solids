//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#include "IsoCurve.h"
#include "../BezierData.h"
#include "../utils.h"

namespace hs {
    IsoCurve::IsoCurve(const std::array<unsigned int, 4>& curveCoefs, TrimmedCell& trimmedCell):
        curveCoefs(curveCoefs), trimmedCell(trimmedCell), needsRecalc(true)
    {

    }

    void IsoCurve::recalculate() {
        if (!needsRecalc) return;

        auto resolution = trimmedCell.getMainCell().getSharedData().getBezierResolution();
        auto& trimmedCoefs = trimmedCell.getTrimmedCoefs();

        std::vector<glm::vec3> points;
        float param = 1.f / (resolution - 1.f);

        float Bi;
        glm::vec3 pt(0);

        for (int t = 0; t < (int)resolution; t++) {
            float tt = param * (float)t;
            pt = {};
            for (int i = 0; i <= 3; i++) {
                Bi = B(i, tt);
                pt = pt + (trimmedCoefs[curveCoefs[i]] * Bi);
            }
            points.push_back(pt);
        }

        if (auto parent = trimmedCell.getParentTrimmedCell()) {
            points = parent->get().evaluate(points);
        }

        points = trimmedCell.getMainCell().evaluate(points);

        poliline = std::make_unique<Poliline>(points, false);
        needsRecalc = false;
    }

    void IsoCurve::needRecalculation(bool U, bool R) {
        needsRecalc = U || R;
    }

    void IsoCurve::render(RenderContext& context) {
        recalculate();
        poliline->render(context);
    }
} // hs