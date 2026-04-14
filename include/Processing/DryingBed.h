#pragma once
#include "../Core/Machine.h"
#include "WeatherModel.h"

namespace FactorySim {
    class DryingBed : public Machine {
    private:
        float area_sqm;
        float capacity_kg;
        float target_moisture_pct;
        float drying_rate_pct_per_day;
        int turns_per_day;

    public:
        DryingBed(std::string id, float area, float capacity);

        [[nodiscard]] bool isDryingComplete(const Batch& batch) const;

        void applyWeather(const WeatherModel& weather, float dt);

        void process(Batch& batch, float dt) override;
        void onBreakdown() override;
        void logEvent(EventLog& log) override;
    };
}