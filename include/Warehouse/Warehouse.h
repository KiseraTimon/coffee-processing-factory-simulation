#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include "../Packaging/PackageUnit.h"
#include "InventoryRecord.h"

namespace FactorySim {
    class Warehouse {
    private:
        std::string warehouse_id;
        int total_capacity_bags;
        int current_occupancy;
        float temperature_c;
        float humidity_pct;

        // Physical Storage: Maps a Batch ID to a stack of physical bags
        std::unordered_map<std::string, std::vector<PackageUnit>> physical_storage;

        // Data Ledger: Maps a Batch ID to its inventory metadata for O(1) lookup
        std::unordered_map<std::string, InventoryRecord> inventory_ledger;

    public:
        Warehouse(std::string id, int capacity, float temp, float humidity);

        // Standard getters
        [[nodiscard]] bool isFull() const;
        [[nodiscard]] int getOccupancy() const { return current_occupancy; }

        // Simulation Actions
        bool store(PackageUnit bag);
        std::optional<PackageUnit> retrieve(const std::string& batch_id);

        // System tick to age the inventory
        void tick(float dt);
    };
}