#include "../../include/Delivery/Vehicle.h"
#include <iostream>

namespace FactorySim {

    Vehicle::Vehicle(std::string id, VehicleType type, float capacity, float fuel, float speed, float breakdown_prob)
        : Machine(std::move(id), 0.0f),
          vehicle_type(type), capacity_kg(capacity), current_load_kg(0.0f),
          fuel_per_km(fuel), avg_speed_kmh(speed), breakdown_prob_per_km(breakdown_prob),
          current_driver(nullptr), distance_remaining_km(0.0f), is_en_route(false) {}

    bool Vehicle::load(const std::vector<PackageUnit>& items) {
        if (is_en_route) return false;

        float incoming_weight_kg = 0.0f;
        for (const auto& item : items) {
            incoming_weight_kg += (item.net_weight_g / 1000.0f);
        }

        if (current_load_kg + incoming_weight_kg > capacity_kg) {
            std::cout << "Vehicle " << getEntityId() << " overloaded!\n";
            return false;
        }

        cargo.insert(cargo.end(), items.begin(), items.end());
        current_load_kg += incoming_weight_kg;
        return true;
    }

    void Vehicle::assignDriver(Driver* driver) {
        current_driver = driver;
    }

    bool Vehicle::dispatch(const DeliveryRoute& route) {
        if (status != MachineStatus::IDLE || current_driver == nullptr || is_en_route) {
            return false;
        }

        if (!current_driver->canDrive()) {
            std::cout << "Driver " << current_driver->getEntityId() << " is too fatigued to drive!\n";
            return false;
        }

        distance_remaining_km = route.getDistance();
        is_en_route = true;
        status = MachineStatus::RUNNING;
        return true;
    }

    void Vehicle::process(Batch& empty_batch, float dt) {
        // If not driving, do nothing
        if (!is_en_route || status != MachineStatus::RUNNING) return;

        // Distance travelled in tick
        float distance_traveled = avg_speed_kmh * dt;

        // Roll for breakdowns based on distance traveled!
        static std::mt19937 rng(std::random_device{}());
        std::bernoulli_distribution breakdown_dist(breakdown_prob_per_km * distance_traveled);
        
        if (breakdown_dist(rng)) {
            status = MachineStatus::BROKEN;
            onBreakdown();
            return;
        }

        // Updating vehicle and driver state
        distance_remaining_km -= distance_traveled;
        current_driver->work(dt);

        // Checking if arrived
        if (distance_remaining_km <= 0.0f) {
            std::cout << "Vehicle " << getEntityId() << " arrived at destination!\n";
            is_en_route = false;
            status = MachineStatus::IDLE;
            cargo.clear(); // Delivery complete!
            current_load_kg = 0.0f;
        }
    }

    void Vehicle::onBreakdown() {
        std::cout << "Vehicle " << getEntityId() << " broke down on the road!\n";
        is_en_route = false; 
    }

    void Vehicle::logEvent(EventLog& log) {}
}