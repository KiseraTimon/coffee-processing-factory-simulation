#include "../../include/Sales/Customer.h"
#include <cmath>
#include <utility>

namespace FactorySim {

    Customer::Customer(std::string id, std::string n, CustomerType t, CoffeeGrade grade, 
                       float sensitivity, float freq_days, int terms)
        : customer_id(std::move(id)), name(std::move(n)), type(t), 
          preferred_grade(grade), price_sensitivity(sensitivity), 
          order_freq_mean_days(freq_days), payment_terms_days(terms), order_count(0) {}

    std::optional<Order> Customer::tryGenerateOrder(float dt_days, std::mt19937& rng) const {
        // The Poisson rate (lambda) for the given time delta
        float expected_orders_in_window = dt_days / order_freq_mean_days;
        std::poisson_distribution<int> arrival_dist(expected_orders_in_window);

        // Order arrivals today
        if (arrival_dist(rng) == 0) {
            return std::nullopt; // No order today
        }

        // Customer wants to buy; determining how much based on who they are.
        float requested_kg = 0.0f;
        if (type == CustomerType::CAFE) requested_kg = 20.0f;           // Cafes buy a few bags
        else if (type == CustomerType::ROASTER) requested_kg = 500.0f;  // Small Roasters buy pallets
        else if (type == CustomerType::IMPORTER) requested_kg = 18000.0f; // Importers buy shipping containers!

        // Random variance to the order size (± 20%)
        std::uniform_real_distribution<float> variance(0.8f, 1.2f);
        requested_kg *= variance(rng);

        // Order Line Item (placeholder market price of $8.00/kg)
        float unit_price = 8.00f; 
        OrderLineItem item = { preferred_grade, requested_kg, unit_price };

        std::vector<OrderLineItem> items;
        items.push_back(item);

        float total_value = requested_kg * unit_price;

        std::string order_id = "ORD-" + customer_id + "-" + std::to_string(++order_count);

        return Order(order_id, customer_id, items, total_value);
    }

    bool Customer::evaluateOffer(float price, CoffeeGrade grade, std::mt19937& rng) const {
        // Base willingness to pay based on Grade
        float willingness_to_pay = 5.0f; // Baseline for C grade
        if (grade == CoffeeGrade::AA) willingness_to_pay = 12.0f;
        else if (grade == CoffeeGrade::AB) willingness_to_pay = 9.0f;
        else if (grade == CoffeeGrade::PEABERRY) willingness_to_pay = 15.0f;

        // Wholesale discounts (for Importers), retails pays a premium
        if (type == CustomerType::IMPORTER) willingness_to_pay *= 0.75f;
        else if (type == CustomerType::CAFE) willingness_to_pay *= 1.20f;

        /**
         *Logic Note: Sigmoid evaluation model
         *Formula: 1 / (1 + exp(-sensitivity * (willingness - price)))
         */
        float x = price_sensitivity * (willingness_to_pay - price);
        float acceptance_probability = 1.0f / (1.0f + std::exp(-x));

        // Die roll against buyer's psychological probability
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        return dist(rng) < acceptance_probability;
    }
}