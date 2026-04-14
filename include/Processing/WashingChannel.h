#pragma once
#include "../Core/Machine.h"

namespace FactorySim {
    class WashingChannel : public Machine {
    private:
        float capacity_kg_per_cycle;
        float water_flow_l_per_min;
        float cycle_duration_min;
        float water_used_total_l;

    public:
        WashingChannel(std::string id, float capacity, float water_flow, float duration);

        void process(Batch& batch, float dt) override;
        void onBreakdown() override;
        void logEvent(EventLog& log) override;
    };
}