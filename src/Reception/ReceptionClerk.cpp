#include "../../include/Reception/ReceptionClerk.h"

namespace FactorySim {
    ReceptionClerk::ReceptionClerk(
        std::string id,
        std::string name,
        float entry,
        float speed,
        float duration)
            :
    Worker(id, name, WorkerRole::RECEIVER, fillRandom(0.0f, 1.0f)),
    data_entry_accuracy(fillRandom(0.0f, 1.0f)),
    processing_speed(speed),
    processing_duration(duration){};

    IntakeRecord ReceptionClerk::processArrival(const Batch &, const ReceptionScale &) {
        //
    }

    // Simulating Exhaustion
    void ReceptionClerk::work(float delta) {
        accumulateFatigue(delta);
    }



}