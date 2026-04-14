#include "../../include/Cleaning/FlotationTank.h"

namespace  FactorySim {
    FlotationTank::FlotationTank(
        std::string id,
        float capacity,
        float water_temp,
        float float_removal_rate,
        float water_level,
        float cycle_duration)
            :
    // High throughput for tanks
    Machine(id, 5000.0f),
    capacity(capacity),
    water_temp(water_temp),
    float_removal_rate(float_removal_rate), // To be calculated instead of being instantiated. Affected by Machine efficiency
    water_level(water_level),
    cycle_duration(cycle_duration) // Affected by the Machine efficiency
    {}

    float FlotationTank::calculateDefectsRemoved(float contamination) const {
        return contamination * (float_removal_rate * efficiency);
    }

    void FlotationTank::process(Batch &batch, float delta) {
        if (status != MachineStatus::RUNNING) return;

        // Calculating water consumption
        float water_used = batch.getWeight() * water_level;

        /**
         * Future Ideas:
         * Cost Tracking for Resources
         */

        // Removing defects
        float cleaning_power = float_removal_rate * efficiency;
        batch.reduceContamination(cleaning_power);

        // Weight loss
        float weight_loss_estimate = 0.05f * cleaning_power;
        batch.applyWeightLoss(weight_loss_estimate);
    }

    void FlotationTank::onBreakdown() {
        //
    }

    void FlotationTank::logEvent(EventLog &log) {
        //
    }





}