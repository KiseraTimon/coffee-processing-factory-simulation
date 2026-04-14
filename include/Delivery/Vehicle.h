#pragma once
#include "../Core/Machine.h"
#include "../Packaging/PackageUnit.h"
#include "DeliveryData.h"
#include "Driver.h"
#include <vector>
#include <optional>

namespace FactorySim {
    class Vehicle : public Machine {
    private:
        VehicleType vehicle_type;
        float capacity_kg;
        float current_load_kg;
        float fuel_per_km;
        float avg_speed_kmh;
        float breakdown_prob_per_km;

        // Active Delivery State
        std::vector<PackageUnit> cargo;
        Driver* current_driver;
        float distance_remaining_km;
        bool is_en_route;

    public:
        Vehicle(std::string id, VehicleType type, float capacity, float fuel, float speed, float breakdown_prob);

        bool load(const std::vector<PackageUnit>& items);
        void assignDriver(Driver* driver);
        bool dispatch(const DeliveryRoute& route);

        // Override Methods
        void process(Batch& empty_batch, float dt) override;
        void onBreakdown() override;
        void logEvent(EventLog& log) override;
    };
}