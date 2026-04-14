#include "../../include/Processing/WashingChannel.h"
#include <utility>

namespace FactorySim {

    WashingChannel::WashingChannel(std::string id, float capacity, float water_flow, float duration)
        : Machine(std::move(id), 2000.0f),
          capacity_kg_per_cycle(capacity), water_flow_l_per_min(water_flow), 
          cycle_duration_min(duration), water_used_total_l(0.0f) {}

    void WashingChannel::process(Batch& batch, float dt) {
        if (status != MachineStatus::RUNNING) return;

        // Water consumption in minutes
        float minutes_run = dt * 60.0f;
        water_used_total_l += (water_flow_l_per_min * minutes_run);

        // Highly efficient at removing natural contamination and fermentation residues
        batch.reduceContamination(0.80f * efficiency); 
    }

    void WashingChannel::onBreakdown() {}
    void WashingChannel::logEvent(EventLog& log) {}
}