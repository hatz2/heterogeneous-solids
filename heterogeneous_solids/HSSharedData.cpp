//
// Created by Alberto Elorza Rubio on 12/12/2023.
//

#include "HSSharedData.h"

namespace hs {
    const float HSSharedData::MinResolution = 2;
    const float HSSharedData::MaxResolution = 24;

    HSSharedData::HSSharedData(): BezierResolution(16) {

    }

    float HSSharedData::getBezierResolution() const {
        return BezierResolution;
    }

    void HSSharedData::setBezierResolution(float bezierResolution) {
        if (bezierResolution < MinResolution || bezierResolution > MaxResolution) return;
        BezierResolution = bezierResolution;
    }
} // hs