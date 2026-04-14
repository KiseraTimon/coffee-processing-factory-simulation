#include "../../include/Packaging/PackagingMachine.h"
#include <random>
#include <iostream>

namespace FactorySim {

    PackagingMachine::PackagingMachine(std::string id, PackagingType type, float rate_bpm, 
                                       float accuracy, float seal_fail, float label_fail, float changeover)
        :
    // Throughput dictated dynamically by bag size and rate
    Machine(std::move(id), 0.0f),
    pkg_type(type),
    fill_rate_bags_per_min(rate_bpm),
    fill_accuracy_g(accuracy),
    seal_failure_rate(seal_fail),
    label_error_rate(label_fail),
    changeover_min(changeover),
    current_changeover_timer_h(0.0f),
    total_bags_produced(0) {}

    void PackagingMachine::triggerChangeover(PackagingType new_type) {
        if (pkg_type != new_type) {
            pkg_type = new_type;
            current_changeover_timer_h = changeover_min / 60.0f; // Mins to hours
        }
    }

    PackageUnit PackagingMachine::fillBag(const Batch& batch, float target_g, std::mt19937& rng) {
        // Logic Note: fill_weight = N(target_g, fill_accuracy_g)
        std::normal_distribution<float> weight_dist(target_g, fill_accuracy_g);
        float actual_weight = weight_dist(rng);

        // Bernoulli distributions for physical failures
        std::bernoulli_distribution seal_dist(seal_failure_rate / efficiency); // Wear makes it worse
        std::bernoulli_distribution label_dist(label_error_rate / efficiency);

        bool seal_ok = !seal_dist(rng);
        bool label_ok = !label_dist(rng);

        std::string lot_code = "LOT-" + batch.getId().substr(0, 8);
        std::string bag_id = "PKG_" + std::to_string(++total_bags_produced);

        return PackageUnit(bag_id, batch.getId(), actual_weight, lot_code, seal_ok, label_ok);
    }

    void PackagingMachine::process(Batch& batch, float dt) {
        if (status != MachineStatus::RUNNING) return;

        // Checking if blocked by a changeover
        if (current_changeover_timer_h > 0.0f) {
            current_changeover_timer_h -= dt;
            return; 
        }

        // Ensuring batch is ready for packaging
        if (batch.getStage() != BatchStage::ROASTED) {
            return; // Failed packing
        }
        if (batch.getWeight() <= 0.01f) {
            batch.setStage(BatchStage::PACKAGED); // Successful packing
            return;
        }

        // Determining target weight per bag based on current machine settings
        float target_weight_g = 250.0f;
        if (pkg_type == PackagingType::RETAIL_500G) target_weight_g = 500.0f;
        else if (pkg_type == PackagingType::EXPORT_60KG) target_weight_g = 60000.0f;

        // Calculating how many bags we can physically pack in this time step
        float minutes_passed = dt * 60.0f;
        float potential_bags = (fill_rate_bags_per_min * efficiency) * minutes_passed;
        int bags_to_pack = static_cast<int>(potential_bags);

        // Packing the bags
        // We need a static RNG for this machine's operations
        static std::mt19937 rng(std::random_device{}());

        for (int i = 0; i < bags_to_pack; ++i) {
            // Stop if short of coffee in the bulk batch
            if (batch.getWeight() <= 0.01f) {
                batch.setStage(BatchStage::PACKAGED);
                break;
            }

            // Creating the bag
            PackageUnit new_bag = fillBag(batch, target_weight_g, rng);
            
            // Populating output buffer
            output_buffer.push_back(new_bag);

            // Deducting the physical weight from the bulk batch (convert g to kg)
            batch.applyWeightLoss((new_bag.net_weight_g / 1000.0f) / batch.getWeight());
        }
    }

    std::vector<PackageUnit> PackagingMachine::collectOutput() {
        // Move semantics: Giving the buffer to the caller and clearing internal ones instantly
        std::vector<PackageUnit> extracted = std::move(output_buffer);
        output_buffer.clear();
        return extracted;
    }

    void PackagingMachine::onBreakdown() { 
        // Heating element for the bag sealer burnt out
        seal_failure_rate *= 3.0f; 
    }
    
    void PackagingMachine::logEvent(EventLog& log) {}
}