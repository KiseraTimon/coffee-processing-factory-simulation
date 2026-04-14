#include "../../include/Processing/FermentationTank.h"
#include <cmath>
#include <utility>

namespace FactorySim {

    FermentationTank::FermentationTank(std::string id, float capacity, float target_h, float temp)
        : Machine(std::move(id), 0.0f), // Throughput is 0 because it's a batch-hold process
          capacity_kg(capacity), target_hours(target_h),
          current_temp_c(temp), hours_elapsed(0.0f), over_ferment_risk(0.0f) {}

    bool FermentationTank::isComplete() const {
        return hours_elapsed >= target_hours;
    }

    float FermentationTank::calcQualityDelta() const {
        // Returns a negative penalty based on how over-fermented the batch is
        return -(over_ferment_risk * 0.1f);
    }

    void FermentationTank::process(Batch& batch, float dt) {
        if (status != MachineStatus::RUNNING) return;

        // Arrhenius Approximation: Baseline temp is 20C.
        // If it's 30C, fermentation happens 2x as fast. If it's 10C, it happens half as fast.
        float temp_factor = std::pow(2.0f, (current_temp_c - 20.0f) / 10.0f);

        // Advance simulated fermentation time
        hours_elapsed += (dt * temp_factor);

        // Note: over_ferment_risk = max(0.0f, (elapsed - target) * temp_factor)
        if (hours_elapsed > target_hours) {
            over_ferment_risk = (hours_elapsed - target_hours) * temp_factor;

            // Over-fermentation creates acetic acid (vinegar taste), ruining the batch
            batch.addContamination(over_ferment_risk * 0.05f * dt);
        }
    }

    void FermentationTank::onBreakdown() { current_temp_c += 5.0f; /* Cooling jacket failed! */ }
    void FermentationTank::logEvent(EventLog& log) {}
}