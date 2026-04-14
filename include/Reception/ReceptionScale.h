#pragma once
#include "../Core/Machine.h"
#include <random>

namespace FactorySim{
    class ReceptionScale : public Machine
    {
    private:
        float max_capacity_kg;
        float precision_kg;
        float drift_per_day;
        int days_since_calibration;

    public:
        // Constructor
        ReceptionScale(
            std::string id,
            std::string name,
            float max_kg,
            float precision_kg,
            float drift,
            int days_since_calibration);

        [[nodiscard]] float weigh(float true_weight, std::mt19937& rng) const;

        void calibrate();

        // Override Method
        void logEvent(EventLog &log) override;

        // Empty Overrides
        void onBreakdown() override {
            //
        }
        void process(Batch &batch, float delta) override {
            //
        }
    };
}