#include "../../include/Milling/Huller.h"
#include <utility>

namespace FactorySim {

    Huller::Huller(std::string id, float throughput, float breakage_rate)
        : Machine(std::move(id), throughput),
          base_hull_breakage_rate(breakage_rate) {}

    void Huller::process(Batch& batch, float dt) {
        if (status != MachineStatus::RUNNING) return;

        // Removing the hull drops the physical weight of the batch by 20%
        batch.applyWeightLoss(0.20f);

        // "Higher wear -> more breakage; tracked with hours_since_maint attribute"
        // Breakage spikes exponentially if past our maintenance interval
        float wear_multiplier = 1.0f + (hours_since_maint / maint_interval_h);
        float actual_breakage = base_hull_breakage_rate * wear_multiplier * dt;

        // Broken beans introduce contamination
        batch.addContamination(actual_breakage);

        // Transitioning Batch Stage
        batch.setStage(BatchStage::MILLED);
    }

    void Huller::onBreakdown() { 
        // Friction fire or jammed gears
        base_hull_breakage_rate *= 2.0f; // Permanent damage until repaired
    }
    
    void Huller::logEvent(EventLog& log) {}
}