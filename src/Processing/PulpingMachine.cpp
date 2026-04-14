#include "../../include/Processing/PulpingMachine.h"
#include <utility>

namespace FactorySim {

    PulpingMachine::PulpingMachine(std::string id, float throughput, float water_usage, float wear_factor)
        : Machine(std::move(id), throughput),
          pulp_efficiency(1.0f), water_per_kg(water_usage), blade_wear_factor(wear_factor) {}

    void PulpingMachine::applyBladeDegradation(float dt) {
        pulp_efficiency -= (blade_wear_factor * dt);
        if (pulp_efficiency < 0.20f) pulp_efficiency = 0.20f;
    }

    void PulpingMachine::process(Batch& batch, float dt) {
        if (status != MachineStatus::RUNNING) return;

        applyBladeDegradation(dt);

        // Pulping removes 40% of the cherry's weight (the fruit skin)
        batch.applyWeightLoss(0.40f * pulp_efficiency);

        // Worn blades crush beans, raising contamination
        if (pulp_efficiency < 0.60f) {
            float crushing_damage = (0.60f - pulp_efficiency) * dt;
            batch.addContamination(crushing_damage);
        }

        batch.setStage(BatchStage::PROCESSING);
    }

    void PulpingMachine::onBreakdown() { pulp_efficiency -= 0.30f; /* Catastrophic jam */ }
    void PulpingMachine::logEvent(EventLog& log) {}
}