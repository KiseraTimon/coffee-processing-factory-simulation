#pragma once
#include <string>
#include <optional>
#include <utility>

namespace FactorySim {
    struct InventoryRecord {
        std::string batch_id;
        int quantity_bags;
        std::string slot_id;
        
        // Optional ID field as batch might NOT have an order reserved yet!
        std::optional<std::string> reserved_order_id;
        
        // Dynamic shelf life tracker
        float remaining_shelf_life_h; 

        // Constructor
        InventoryRecord(
            std::string b_id,
            std::string slot,
            float initial_shelf_life)
            :
        batch_id(std::move(b_id)),
        quantity_bags(0),
        slot_id(std::move(slot)),
        reserved_order_id(std::nullopt),
        remaining_shelf_life_h(initial_shelf_life) {}
    };
}