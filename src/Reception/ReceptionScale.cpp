#include "../../include/Reception/ReceptionScale.h"
#include "../../include/System/EventLog.h"
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

    float ReceptionScale::weigh(float true_weight) const {
        std::mt19937 rng;
        // Computing Standard Deviation of Scale Error
        float error_stddev = precision_kg + (drift_per_day * static_cast<float>(days_since_calibration));

        // Normal Distribution
        std::normal_distribution<float> dist(0.0f, error_stddev);

        float measured_weight = true_weight + dist(const_cast<std::mt19937&>(rng));

        // No negative weights
        return (measured_weight < 0.0f) ? 0.0f : measured_weight;
    }

    void ReceptionScale::process(Batch &batch, float delta) {
        float measured = weigh(batch.getWeight());
        EventLog::getInstance().log(getEntityId(),
            "Weighed Batch " + batch.getId() + " at " + std::to_string(measured) + "kg");

        batch.setStage(BatchStage::RECEIVED);
    }

    void ReceptionScale::calibrate() {
        drift_per_day = 0.0f;
        days_since_calibration = 0;
    }

    void ReceptionScale::logEvent(EventLog &log) {
        //
    }


}