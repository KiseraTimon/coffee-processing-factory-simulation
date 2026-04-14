#pragma once
#include "../Core/Machine.h"

namespace FactorySim {
    class DebrisRemover : public Machine {
    private:
        float remover_efficiency;
        float blade_wear_factor;

    public:
        DebrisRemover(
            std::string id,
            float remover_efficiency,
            float blade_wear_factor);

        void applyWear(float delta);

        // Override Methods
        void process(Batch &batch, float delta) override;
        void onBreakdown() override;
        void logEvent(EventLog &log) override;
    };
}
