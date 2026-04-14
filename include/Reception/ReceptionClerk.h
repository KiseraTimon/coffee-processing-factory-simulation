#pragma once
#include "IntakeRecord.h"
#include "ReceptionScale.h"
#include "../Core/Batch.h"
#include "../Core/Worker.h"
#include <random>

namespace FactorySim {
    class ReceptionClerk : public Worker
    {
    private:
        float data_entry_accuracy;
        float processing_speed;
        float processing_duration;

    public:
        ReceptionClerk(
            std::string id,
            std::string name,
            float speed,
            float duration);

        // Override Method
        void work(float dt) override;
        void logEvent(EventLog &log) override;

        IntakeRecord processArrival(const Batch&, const ReceptionScale&, std::mt19937&);

    };
}
