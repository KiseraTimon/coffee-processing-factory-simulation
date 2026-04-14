#pragma once
#include <random>

namespace FactorySim {
    class WeatherModel {
    private:
        float humidity_pct;
        float temp_c;
        float solar_radiation_wm2;
        float rain_probability;
        float wind_speed_kmh;
        float drying_modifier;
        bool is_raining;

        // Private constructor for Singleton pattern
        WeatherModel();

    public:
        // Delete copy constructor and assignment operator
        WeatherModel(const WeatherModel&) = delete;
        WeatherModel& operator=(const WeatherModel&) = delete;

        // Standard Thread-Safe Singleton
        static WeatherModel& getInstance();

        void tick(float dt, std::mt19937& rng);
        
        [[nodiscard]] float getDryingModifier() const { return drying_modifier; }
        [[nodiscard]] bool isRaining() const { return is_raining; }
    };
}