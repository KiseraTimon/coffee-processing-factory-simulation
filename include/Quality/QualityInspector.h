#pragma once
#include "GradeResult.h"
#include "../Core/Worker.h"
#include "../Core/CoreTypes.h"
#include <random>

#include "../Core/Batch.h"

namespace FactorySim {
    class QualityInspector : public Worker
    {
    private:
        Certificate certificate;
        float inspection_speed;     //kgs per minute
        float false_positive_rate;
        float false_negative_rate;

    public:
        QualityInspector(
            std::string id,
            std::string name,
            float speed,
            float false_positive_rate,
            float false_negative_rate);

        GradeResult inspect(const Batch&, std::mt19937&);

        // Override Methods
        void work(float dt) override;
        void logEvent(EventLog &log) override;

    };
}
