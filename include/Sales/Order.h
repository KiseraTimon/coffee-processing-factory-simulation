#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <utility>
#include "../Core/CoreTypes.h"

namespace FactorySim {

    // Logic Note: OrderLineItem = { CoffeeGrade grade; float quantity_kg; float unit_price; }
    struct OrderLineItem {
        CoffeeGrade grade;
        float quantity_kg;
        float unit_price;
    };

    struct Order {
        std::string order_id;
        std::string customer_id;
        std::vector<OrderLineItem> items;
        OrderStatus status;
        float total_value;
        bool payment_received;
        std::chrono::system_clock::time_point requested_delivery;

        Order(std::string o_id, std::string c_id, std::vector<OrderLineItem> line_items, float value)
            : order_id(std::move(o_id)), customer_id(std::move(c_id)), items(std::move(line_items)),
              status(OrderStatus::PENDING), total_value(value), payment_received(false) {
            
            // Default requested delivery is 7 days from now
            requested_delivery = std::chrono::system_clock::now() + std::chrono::hours(24 * 7);
        }
    };
}