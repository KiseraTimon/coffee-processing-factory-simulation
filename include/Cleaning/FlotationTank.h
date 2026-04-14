#pragma once
#include "../Core/Machine.h"

namespace FactorySim {
    class FlotationTank : public Machine {
    private:
        float capacity; // Litres
        float water_temp;
        float float_removal_rate;
        float water_level;  // per kgs/litres
        float cycle_duration;   // mins

    public:
        FlotationTank(
            std::string id,
            float capacity,
            float water_temp,
            float float_removal_rate,
            float water_level,
            float cycle_duration);

        float calculateDefectsRemoved(float contamination) const;

        // Override Method
        void process(Batch &batch, float delta) override;
        void onBreakdown() override;
        void logEvent(EventLog &log) override;

    };
}
