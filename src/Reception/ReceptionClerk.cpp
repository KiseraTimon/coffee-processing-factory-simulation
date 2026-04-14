#include "../../include/Reception/ReceptionClerk.h"
#include "../../include/Core/Utils.h"
#include <random>

namespace FactorySim {
    ReceptionClerk::ReceptionClerk(
        std::string id,
        std::string name,
        float speed,
        float duration)
            :
    Worker(id, name, WorkerRole::RECEIVER, Utils::fillRandom(0.0f, 1.0f)),
    data_entry_accuracy(Utils::fillRandom(0.0f, 1.0f)),
    processing_speed(speed),
    processing_duration(duration){};

    IntakeRecord ReceptionClerk::processArrival(const Batch& batch, const ReceptionScale& scale, std::mt19937& rng) {
        // Clerk uses scale to weigh batch
        float measured_weight = scale.weigh(batch.getWeight(), rng);

        // Data entry errors simulation
        std::bernoulli_distribution error_dist(1.0f - data_entry_accuracy);
        if (error_dist(rng)) {
            // Clerk makes an error
            measured_weight *= 1.10f;
        }

        // Random ticket number
        std::uniform_int_distribution<int> tkt_dist(1000, 9999);
        std::string ticket = "TKT-" + std::to_string(tkt_dist(rng));

        // IntakeRecord
        return IntakeRecord(
            "REC_" + batch.getId(),
            batch.getId(),
            measured_weight,
            this->getEntityId(),    // Clerk's ID
            ticket,
            std::chrono::system_clock::now());
    }

    // Simulating Exhaustion
    void ReceptionClerk::work(float delta) {
        accumulateFatigue(delta);
    }

    void ReceptionClerk::logEvent(EventLog &log) {
        //
    }



}