#include "../../include/Roasting/Roaster.h"
#include <utility>
#include <iostream>

namespace FactorySim {

    Roaster::Roaster(std::string id, float capacity, RoastProfile profile)
        :
    // Throughput is 0 because it's limited by batch capacity, not flow rate
    Machine(std::move(id), 0.0f),
    capacity_kg(capacity),
    profile(profile),
    drum_temp_c(200.0f),
    roast_duration_min(12.0f),
    dev_time_ratio(0.20f),
    cool_down_min(5.0f),
    weight_loss_pct(15.0f),
    current_cooldown_timer_h(0.0f) {

        // Adjusting machine parameters based on the chosen profile
        if (profile == RoastProfile::LIGHT) {
            drum_temp_c = 195.0f;
            roast_duration_min = 10.0f;
            weight_loss_pct = 13.0f; // Light roasts lose less water weight
        } else if (profile == RoastProfile::DARK) {
            drum_temp_c = 220.0f;
            roast_duration_min = 15.0f;
            weight_loss_pct = 20.0f; // Dark roasts lose the most weight
        }
    }

    float Roaster::calcRoastLoss() const {
        // Logic Note: Weight loss is typically 15-20%
        return weight_loss_pct / 100.0f;
    }

    void Roaster::process(Batch& batch, float dt) {
        if (status != MachineStatus::RUNNING) return;

        // Checking if the machine is still cooling down from the last batch
        if (current_cooldown_timer_h > 0.0f) {
            current_cooldown_timer_h -= dt;
            return; // Machine is blocked, batch must wait in queue
        }

        // Reject batch if it exceeds the drum capacity
        if (batch.getWeight() > capacity_kg) {
            std::cout << "Error: Batch " << batch.getId() << " exceeds Roaster "
                      << getEntityId() << " capacity!\n";
            return;
        }

        // Applying the massive physical weight loss from roasting
        batch.applyWeightLoss(calcRoastLoss());

        /**
         *Logic Note: dev_time_ratio controls flavor development
         *A perfect development ratio is around 20-25%. If it's too high or low, it "bakes" the coffee.
         */
        if (dev_time_ratio < 0.15f || dev_time_ratio > 0.25f) {
            batch.addContamination(0.10f); // Penalizing the batch by increasing defect/contamination score
        }

        // Applying Roasting specific stats (Agtron color scale: Higher = lighter)
        float agtron_score = 75.0f; // Default medium
        float degassing_hours = 24.0f;

        if (profile == RoastProfile::LIGHT) {
            agtron_score = 90.0f;
            degassing_hours = 12.0f; // Light roasts degas faster
        } else if (profile == RoastProfile::DARK) {
            agtron_score = 45.0f;
            degassing_hours = 72.0f; // Dark roasts need days to release CO2
        }

        batch.setRoastStats(agtron_score, degassing_hours);
        batch.setStage(BatchStage::ROASTED);

        // Locking the machine into cooldown mode
        current_cooldown_timer_h = cool_down_min / 60.0f;
    }

    void Roaster::onBreakdown() {
        /**
         *Thermal runaway! The drum overheats, heavily degrading the machine's efficiency
         */
        drum_temp_c += 50.0f;
        efficiency *= 0.50f;
    }

    void Roaster::logEvent(EventLog& log) {
        //
    }
}