#pragma once
#include "../Core/CoreTypes.h"
#include "../Core/Batch.h"
#include <string>
#include <random>
#include <memory>

namespace FactorySim {
    class FarmPlot
    {
    protected:
        std::string plot_id;
        CoffeeVariety variety;
        float area_ha;
        int altitude;
        float cherry_density; // kgs per ha
        float yield{};
        float ripeness_mean;
        float ripeness_stddev;
        float yield_estimate; //kgs

    public:
        FarmPlot(
            std::string& id,
            CoffeeVariety variety,
            float area,
            int alt,
            float density,
            float yield,
            float r_mean = 0.85f,
            float r_stddev = 0.10f)
                :
        plot_id(id),
        variety(variety),
        area_ha(area),
        altitude(alt),
        cherry_density(density),
        ripeness_mean(r_mean),
        ripeness_stddev(r_stddev),
        yield_estimate(yield)
        {}

        // UML Actions

        /**
         *
         * @param worker_efficiency passed onto the function so the harvester worker influences harvest
         * @param rng random number generator
         * @return Batch of Farm Produce
         */
        std::unique_ptr<Batch> harvest(
            float worker_efficiency,
            std::mt19937& rng);

        /**
         *
         * @param rng Randomly assigns ripeness quantity to yield
         * @return Standard Deviation for Cherry Qualities
         */
        float getRipenessSample(
            std::mt19937& rng) const;

        /**
         *
         * @param days Days it takes to restore cherries
         */
        void regrow(float days);

        // Getter
        std::string getPlotID() { return plot_id; }
    };
}