#pragma once
#include <chrono>
#include <string>

namespace FactorySim {
    class IntakeRecord
    {
    public:
        std::string record_id;
        std::string batch_id;
        float measured_weight;  //kgs
        std::string clerk_id;
        std::string ticket_number;
        std::chrono::time_point<> arrival_time;

        // Constructor
        IntakeRecord(
            std::string record_id,
            std::string batch_id,
            float measured_weight,
            std::string clerk_id,
            std::string ticket_number,
            std::chrono::time_point<> arrival);
    };
}
