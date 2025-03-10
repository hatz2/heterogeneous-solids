//
// Created by Alberto Elorza Rubio on 01/04/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_MATERIALCOEF_H
#define HETEROGENEOUS_SOLIDS_MATERIALCOEF_H

#include <memory>
#include "../../utils/Observer.h"

namespace hs {

    class MaterialCoef: private Observer<float> {
    public:
        explicit MaterialCoef(float& a0, bool keepContinuity = true);
        MaterialCoef(const MaterialCoef& other) = delete;
        ~MaterialCoef() override;

        std::shared_ptr<Subject<float>> getMaterialCoefSync();
        void setMaterialCoefSync(std::shared_ptr<Subject<float>> materialCoefSync);

        [[nodiscard]] float getA0() const;
        void setA0(float a0);

        [[nodiscard]] bool isKeepContinuity() const;
        void setKeepContinuity(bool keepContinuity);
    private:
        std::shared_ptr<Subject<float>> materialCoefSync;
        float& a0;
        bool keepContinuity;

        void updateObserver(float a0) override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MATERIALCOEF_H
