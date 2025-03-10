//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_ISOCURVE_H
#define HETEROGENEOUS_SOLIDS_ISOCURVE_H

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <array>
#include "../../scene/drawables/Poliline.h"

namespace hs {

    class TrimmedCell;

    class IsoCurve {
    private:
        const std::array<unsigned int, 4>& curveCoefs;
        TrimmedCell& trimmedCell;
        std::unique_ptr<Poliline> poliline;

        // TODO: Distinguish between uvw recalculation and xyz recalculation.
        //  Whether parent' shapeCoefs has been mutated or not
        bool needsRecalc;
    public:
        IsoCurve(const std::array<unsigned int, 4>& curveCoefs, TrimmedCell& trimmedCell);
        IsoCurve(const IsoCurve&) = delete;

        void recalculate();

        void needRecalculation(bool U, bool R);

        void render(RenderContext& context);
    };

} // hs

#include "TrimmedCell.h"

#endif //HETEROGENEOUS_SOLIDS_ISOCURVE_H
