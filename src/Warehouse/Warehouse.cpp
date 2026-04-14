#include "../../include/Warehouse/Warehouse.h"
#include "../../include/System/EventLog.h"
#include <cmath>
#include <iostream>

namespace FactorySim {

    Warehouse::Warehouse(std::string id, int capacity, float temp, float humidity)
        : warehouse_id(std::move(id)), total_capacity_bags(capacity), 
          current_occupancy(0), temperature_c(temp), humidity_pct(humidity) {}

    bool Warehouse::isFull() const {
        return current_occupancy >= total_capacity_bags;
    }

    bool Warehouse::store(PackageUnit bag) {
        if (isFull()) {
            return false; // Back-pressures the packaging queue!
        }

        std::string b_id = bag.batch_id;

        // Checking if we already have an InventoryRecord for the batch. If not, create one.
        if (inventory_ledger.find(b_id) == inventory_ledger.end()) {

            // New batch! Assigns it to a random rack/slot
            std::string assigned_slot = "RACK-" + std::to_string(inventory_ledger.size() + 1);
            
            // Assuming fresh roasted coffee has 6 months (4320 hours) of shelf life
            inventory_ledger.emplace(b_id, InventoryRecord(b_id, assigned_slot, 4320.0f));

            EventLog::getInstance().log(warehouse_id, "Allocated new slot " + assigned_slot + " for Batch " + b_id);
        }

        // Adding the physical bag to the storage vector for the batch
        physical_storage[b_id].push_back(std::move(bag));

        // Updating the ledger and capacity
        inventory_ledger.at(b_id).quantity_bags++;
        current_occupancy++;

        EventLog::getInstance().log(warehouse_id, "Stored Bag " + bag.package_id + " (Lot: " + bag.lot_code + ")");

        return true;
    }

    std::optional<PackageUnit> Warehouse::retrieve(const std::string& batch_id) {
        // Checking if the batch exists in our storage
        auto storage_it = physical_storage.find(batch_id);
        
        // Returns nothing if batch is not in storage
        if (storage_it == physical_storage.end() || storage_it->second.empty()) {
            std::cout << "Warehouse Error: Batch " << batch_id << " not found or empty.\n";
            return std::nullopt;
        }

        // Grabbing the last bag from the stack
        PackageUnit retrieved_bag = std::move(storage_it->second.back());
        storage_it->second.pop_back(); // Removing it from the vector

        // Updating the ledger and capacity
        inventory_ledger.at(batch_id).quantity_bags--;
        current_occupancy--;

        // Cleaning up empty vectors and ledgers to save memory
        if (inventory_ledger.at(batch_id).quantity_bags == 0) {
            physical_storage.erase(batch_id);
            inventory_ledger.erase(batch_id);
        }

        return retrieved_bag;
    }

    void Warehouse::tick(float dt) {
        // Logic Note: tick() ages inventory — use Arrhenius equation for degradation
        
        /**
         *Arrhenius Approximation: For every 10C above baseline (e.g., 20C), degradation rate doubles
         *If the warehouse is 30C, shelf life drops twice as fast.
         */
        float degradation_multiplier = std::pow(2.0f, (temperature_c - 20.0f) / 10.0f);
        
        /**
         *High humidity also accelerates staling (simple linear multiplier)
         */
        if (humidity_pct > 60.0f) {
            degradation_multiplier *= (1.0f + ((humidity_pct - 60.0f) / 100.0f));
        }

        float hours_to_deduct = dt * degradation_multiplier;

        // Applying degradation to every batch in the ledger
        for (auto& pair : inventory_ledger) {
            InventoryRecord& record = pair.second;
            record.remaining_shelf_life_h -= hours_to_deduct;

            if (record.remaining_shelf_life_h <= 0.0f) {
                // Future Idea: Discard expired coffee
                // std::cout << "Warning: Batch " << record.batch_id << " has expired!\n";
            }
        }
    }
}