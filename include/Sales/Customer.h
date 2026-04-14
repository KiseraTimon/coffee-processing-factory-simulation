#pragma once
#include <string>
#include <random>
#include <optional>
#include "Order.h"
#include "../Core/CoreTypes.h"

namespace FactorySim {
    class Customer {
    private:
        std::string customer_id;
        std::string name;
        CustomerType type;
        CoffeeGrade preferred_grade;
        float price_sensitivity;
        float order_freq_mean_days;
        int payment_terms_days;

        // Internal counter for generating unique order IDs
        mutable int order_count; 

    public:
        Customer(std::string id, std::string n, CustomerType t, CoffeeGrade grade, 
                 float sensitivity, float freq_days, int terms);

        // Simulation actions
        [[nodiscard]] std::optional<Order> tryGenerateOrder(float dt_days, std::mt19937& rng) const;
        
        [[nodiscard]] bool evaluateOffer(float price, CoffeeGrade grade, std::mt19937& rng) const;

        [[nodiscard]] std::string getId() const { return customer_id; }
        [[nodiscard]] CustomerType getType() const { return type; }
    };
}