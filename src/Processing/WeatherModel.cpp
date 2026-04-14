#include "../../include/Processing/WeatherModel.h"

namespace FactorySim {

    WeatherModel::WeatherModel() 
        : humidity_pct(60.0f), temp_c(25.0f), solar_radiation_wm2(800.0f),
          rain_probability(0.05f), wind_speed_kmh(10.0f), drying_modifier(1.0f), is_raining(false) {}

    WeatherModel& WeatherModel::getInstance() {
        static WeatherModel instance; // Instantiated on first use
        return instance;
    }

    void WeatherModel::tick(float dt, std::mt19937& rng) {
        // Sample for rain using Bernoulli distribution
        std::bernoulli_distribution rain_dist(rain_probability);
        is_raining = rain_dist(rng);

        if (is_raining) {
            // Rain actively adds moisture back to the beans (negative drying)
            drying_modifier = -0.5f; 
            temp_c -= 2.0f * dt; // Temp drops during rain
        } else {
            // Simplified evaporation physics: hotter, windier, and drier = faster drying
            drying_modifier = (temp_c / 25.0f) + (wind_speed_kmh / 20.0f) - (humidity_pct / 100.0f);
            
            // Baseline drying rate on a normal day
            if (drying_modifier < 0.1f) drying_modifier = 0.1f;
        }
    }
}