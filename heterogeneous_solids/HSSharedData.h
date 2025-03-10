//
// Created by Alberto Elorza Rubio on 12/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_HSSHAREDDATA_H
#define HETEROGENEOUS_SOLIDS_HSSHAREDDATA_H

namespace hs {

    class HSSharedData {
    public:
        static const float MinResolution;
        static const float MaxResolution;

        HSSharedData();

        [[nodiscard]] float getBezierResolution() const;
        void setBezierResolution(float bezierResolution);
    private:
        float BezierResolution;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_HSSHAREDDATA_H
