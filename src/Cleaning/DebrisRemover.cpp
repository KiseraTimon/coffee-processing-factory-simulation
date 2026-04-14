#include "../../include/Cleaning/DebrisRemover.h"

namespace FactorySim {
    DebrisRemover::DebrisRemover(
        std::string id,
        float remover_efficiency,
        float blade_wear_factor)
            :
    Machine(id, 1.0f),
    remover_efficiency(remover_efficiency),
    blade_wear_factor(blade_wear_factor)
    {}

    void DebrisRemover::applyWear(float delta) {
        // Efficiency Degradation
        efficiency -= (blade_wear_factor * delta);

        // Efficiency Lower Limit (10%)
        if (efficiency < 0.10f) {
            efficiency = 0.10f;
        }
    }

    void DebrisRemover::process(Batch& batch, float delta) {
        if (status != MachineStatus::RUNNING) return;

        // Machine Wear
        applyWear(delta);

        // Cleaning Power
        float cleaning_power = remover_efficiency * efficiency;

        // Cleaning
        batch.reduceContamination(cleaning_power);
    }

    void DebrisRemover::onBreakdown() {
        // Efficiency Reduces Until Machine is Fixed
        efficiency *= 0.50f;
    }

    void DebrisRemover::logEvent(EventLog &log) {
        //
    }

}