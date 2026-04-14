#pragma once
#include <string>
#include <random>
#include <chrono>
#include <utility>

namespace FactorySim {

    class DeliveryRoute {
    private:
        std::string route_id;
        std::string origin;
        std::string destination;
        float distance_km;
        float base_duration_hours;
        float road_condition_factor;
        float traffic_delay_mean_hours;

    public:
        DeliveryRoute(std::string id, std::string orig, std::string dest, float dist, 
                      float base_dur, float road_cond, float traffic);

        [[nodiscard]] float estimateDuration(float driver_familiarity) const;
        [[nodiscard]] float sampleActualDuration(std::mt19937& rng) const;
        [[nodiscard]] float getDistance() const { return distance_km; }
    };

    struct DeliveryRecord {
        std::string delivery_id;
        std::string order_id;
        std::string vehicle_id;
        std::string driver_id;
        bool condition_ok;
        std::chrono::system_clock::time_point dispatch_ts;
        std::chrono::system_clock::time_point arrival_ts;
    };
}