#include "../../include/Processing/DryingBed.h"
#include <utility>

namespace FactorySim {

    DryingBed::DryingBed(std::string id, float area, float capacity)
        : Machine(std::move(id), 0.0f), // Beds rarely "break" mechanically
          area_sqm(area), capacity_kg(capacity), target_moisture_pct(11.0f), 
          drying_rate_pct_per_day(5.0f), turns_per_day(4) {}

    bool DryingBed::isDryingComplete(const Batch& batch) const {
        // Target moisture is assumbed to be 11% for safe storage
        return batch.getMoisture() <= target_moisture_pct;
    }

    void DryingBed::process(Batch& batch, float dt) {
        // Fetch the global weather state
        WeatherModel& weather = WeatherModel::getInstance();

        // Moisture changes this tick
        float days_elapsed = dt / 24.0f;
        float base_moisture_loss = drying_rate_pct_per_day * days_elapsed;
        
        // Weather multiplier (negative if raining)
        float actual_moisture_change = base_moisture_loss * weather.getDryingModifier();

        // Batch moisture
        batch.adjustMoisture(-actual_moisture_change);

        // Water weight evaporation simulation
        if (actual_moisture_change > 0) {
            batch.applyWeightLoss(actual_moisture_change / 100.0f);
        }
    }

    void DryingBed::applyWeather(const WeatherModel& weather, float dt) {
        /**
         * Future Idea: Hook to store local bed state based on weather
        */
    }

    void DryingBed::onBreakdown() { /* Tarp ripped! */ }
    void DryingBed::logEvent(EventLog& log) {}
}