#pragma once
#include "../Core/Machine.h"
#include "PackageUnit.h"
#include <vector>

namespace FactorySim {
    class PackagingMachine : public Machine {
    private:
        PackagingType pkg_type;
        float fill_rate_bags_per_min;
        float fill_accuracy_g;
        float seal_failure_rate;
        float label_error_rate;
        float changeover_min;

        // Simulation state variables
        float current_changeover_timer_h;
        int total_bags_produced;

        // Stores finished bags
        std::vector<PackageUnit> output_buffer;

    public:
        PackagingMachine(
            std::string id,
            PackagingType type,
            float rate_bpm,
            float accuracy,
            float seal_fail,
            float label_fail,
            float changeover);

        // Changes the bag type and triggers machine downtime
        void triggerChangeover(PackagingType new_type);

        // Generates a single physical bag
        PackageUnit fillBag(const Batch& batch, float target_g, std::mt19937& rng);

        void process(Batch& batch, float dt) override;
        void onBreakdown() override;
        void logEvent(EventLog& log) override;

        // Vector allowing downstream systems e.g. Warehouse to collect the finished bags
        std::vector<PackageUnit> collectOutput();
    };
}