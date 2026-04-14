#include "../../include/Delivery/DeliveryData.h"

namespace FactorySim {

    DeliveryRoute::DeliveryRoute(std::string id, std::string orig, std::string dest, float dist, 
                                 float base_dur, float road_cond, float traffic)
        : route_id(std::move(id)), origin(std::move(orig)), destination(std::move(dest)), 
          distance_km(dist), base_duration_hours(base_dur), 
          road_condition_factor(road_cond), traffic_delay_mean_hours(traffic) {}

    float DeliveryRoute::estimateDuration(float driver_familiarity) const {
        // UML Logic: driver_familiarity reduces base_duration_hours multiplicatively
        float familiarity_discount = 1.0f - (driver_familiarity * 0.20f); // Up to 20% faster if highly familiar
        return (base_duration_hours * road_condition_factor) * familiarity_discount;
    }

    float DeliveryRoute::sampleActualDuration(std::mt19937& rng) const {
        // UML Logic: actual_duration = base * road_condition_factor + N(0, traffic_delay_mean_hours)
        std::normal_distribution<float> traffic_dist(0.0f, traffic_delay_mean_hours);
        
        float actual = (base_duration_hours * road_condition_factor) + traffic_dist(rng);
        return actual < 0.1f ? 0.1f : actual; // Cannot magically teleport
    }
}