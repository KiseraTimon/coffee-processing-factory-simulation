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
    Machine(id, 1.0f),
    capacity(capacity),
    water_temp(water_temp),
    float_removal_rate(float_removal_rate), // To be calculated instead of being instantiated. Affected by Machine efficiency
    water_level(water_level),
    cycle_duration(cycle_duration) // Affected by the Machine efficiency
    {}

    float FlotationTank::calculateDefectsRemoved(float contamination) const {
        //
    }

    void FlotationTank::process(Batch &batch, float delta) {
        //
    }

    void FlotationTank::onBreakdown() {
        //
    }




}