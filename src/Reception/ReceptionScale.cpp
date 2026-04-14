#include "../../include/Reception/ReceptionScale.h"
#include <utility>

namespace FactorySim {
    ReceptionScale::ReceptionScale(
        std::string id,
        std::string name,
        float max_kg,
        float precision_kg,
        float drift,
        int days_since_calibration)
            :
    Machine(std::move(id), 1.0f),
    max_capacity_kg(max_kg),
    precision_kg(precision_kg),
    drift_per_day(drift),
    days_since_calibration(days_since_calibration)
    {}

    void ReceptionScale::onBreakdown() {
        //
    }

    float ReceptionScale::weigh(float true_weight) const {
        return true_weight + (precision_kg + drift_per_day * static_cast<float>(days_since_calibration));
    }

    void ReceptionScale::process(Batch &batch, float delta) {

    }

    void ReceptionScale::calibrate() {
        drift_per_day = 0.0f;
        days_since_calibration = 0;
    }


}