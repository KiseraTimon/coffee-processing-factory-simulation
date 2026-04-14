#pragma once
#include <chrono>
#include <string>
#include <utility>

namespace FactorySim {
    class IntakeRecord
    {
    public:
        std::string record_id;
        std::string batch_id;
        float measured_weight;  //kgs
        std::string clerk_id;
        std::string ticket_number;
        std::chrono::time_point<std::chrono::system_clock> arrival_time;

        // Constructor
        IntakeRecord(
            std::string rec_id,
            std::string b_id,
            float weight,
            std::string c_id,
            std::string ticket,
            std::chrono::time_point<std::chrono::system_clock> arrival)
            : record_id(std::move(rec_id)),
              batch_id(std::move(b_id)),
              measured_weight(weight),
              clerk_id(std::move(c_id)),
              ticket_number(std::move(ticket)),
              arrival_time(arrival)
        {}
    };
}