#pragma once
#include "../Core/Machine.h"

namespace FactorySim {
    class PulpingMachine : public Machine {
    private:
        float pulp_efficiency;
        float water_per_kg;
        float blade_wear_factor;

    public:
        // Constructor
        PulpingMachine(
            std::string id,
            float throughput,
            float water_usage,
            float wear_factor);

        void applyBladeDegradation(float dt);

        // Override Methods
        void process(Batch& batch, float dt) override;
        void onBreakdown() override;
        void logEvent(EventLog& log) override;
    };
}