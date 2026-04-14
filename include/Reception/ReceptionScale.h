#pragma once
#include "../Core/Machine.h"

namespace FactorySim{
    class ReceptionScale : public Machine
    {
    private:
        float max_capacity_kg;
        float precision_kg;
        float drift_per_day;
        int days_since_calibration;

    protected:
        // Override Method
        void onBreakdown() override;

    public:
        // Constructor
        ReceptionScale(
            std::string id,
            std::string name,
            float max_kg,
            float precision_kg,
            float drift,
            int days_since_calibration);

        [[nodiscard]] float weigh(float true_weight) const;

        void calibrate();

        // Override Method
        void process(Batch &batch, float delta) override;
    };
}