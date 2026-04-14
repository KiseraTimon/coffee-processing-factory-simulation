#include "../../include/Harvest/FarmPlot.h"
#include <algorithm>
#include <utility>

namespace FactorySim {
    FarmPlot::FarmPlot(
            std::string id,
            CoffeeVariety variety,
            float area,
            int alt,
            float density,
            float yield,
            float r_mean = 0.85f,
            float r_stddev = 0.10f)
                :
        plot_id(std::move(id)),
        variety(variety),
        area_ha(area),
        altitude(alt),
        cherry_density(density),
        ripeness_mean(r_mean),
        ripeness_stddev(r_stddev),
        yield_estimate(yield)
    {}

    float FarmPlot::getRipenessSample(std::mt19937 &rng) const {
        std::normal_distribution<float> dist(ripeness_mean, ripeness_stddev);
        float sample = dist(rng);

        // Ensure the value stays strictly between 0.0 (0%) and 1.0 (100%)
        return std::clamp(sample, 0.0f, 1.0f);
    }

    std::unique_ptr<Batch> FarmPlot::harvest(float requested_kg, std::mt19937& rng) {
        // Calculating how much coffee is actually left on the farm
        float available_kg = area_ha * cherry_density;

        // Pick Limit
        float actual_harvest_kg = std::min(requested_kg, available_kg);

        if (actual_harvest_kg <= 0.0f) {
            return nullptr; // Farm is empty!
        }

        // Depleting the plot's density
        cherry_density -= (actual_harvest_kg / area_ha);
        if (cherry_density < 0.0f) cherry_density = 0.0f;

        std::string new_batch_id = "BATCH_" + plot_id + "_" + std::to_string(rng() % 10000);

        return std::make_unique<Batch>(new_batch_id, plot_id, variety, actual_harvest_kg);
    }

    void FarmPlot::regrow(float days) {
        // Restores cherry_density over time; driven with a seasonal curve
        // Temporary: I am using a flat recovery rate of 5kg per hectare per day
        float recovery_rate = 5.0f;
        cherry_density += (days * recovery_rate);

        // Optional: Cap it so the density doesn't grow to infinity
        float max_density = yield_estimate / area_ha;
        if (cherry_density > max_density) {
            cherry_density = max_density;
        }
    }



}