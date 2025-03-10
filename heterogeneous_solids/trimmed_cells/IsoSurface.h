//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_ISOSURFACE_H
#define HETEROGENEOUS_SOLIDS_ISOSURFACE_H

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <array>
#include "../../scene/drawables/Mesh.h"
#include "../../scene/drawables/NormalField.h"
#include "../BezierData.h"

namespace hs {

    class TrimmedCell;

    using IsoSurfaceName = unsigned int;

    class IsoSurface {
    private:
        const std::array<unsigned int, 16>& surfaceCoefs;
        TrimmedCell& trimmedCell;

        bool needsRecalcU;
        bool needsRecalcR;

        std::unique_ptr<NormalField> normalField;
        std::unique_ptr<Mesh> mesh;

        std::vector<PointAndTangentsST> pointsAndTgsInU;

        void recalculateU();
        void recalculateR();

    public:
        IsoSurface(const std::array<unsigned int, 16>& surfaceCoefs, TrimmedCell& trimmedCell);
        IsoSurface(const IsoSurface&) = delete;

        void recalculate();

        void needRecalculation(bool U, bool R);

        void render(RenderContext& context);
    };

} // hs

#include "TrimmedCell.h"

#endif //HETEROGENEOUS_SOLIDS_ISOSURFACE_H
