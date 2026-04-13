#pragma once
#include "../Core/Worker.h"
#include "FarmPlot.h"
#include <memory>
#include <random>

namespace FactorySim {
    class Harvester : public Worker
    {
    private:
        float pick_rate;     // kgs per hour
        FarmPlot* assigned_plot;

    public:
        // Constructor
        Harvester(
            std::string id,
            std::string name,
            float skill,
            float pick_rate);

        // Assigns the Harvester a Plot
        void assignPlot(FarmPlot* plot);

        // Override Methods
        void work(float delta) override;
        void logEvent(EventLog &log) override;

        // Simulation Logic
        std::unique_ptr<Batch> performHarvest(float delta, std::mt19937& rng);
    };
}