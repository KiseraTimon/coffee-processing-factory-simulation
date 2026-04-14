#include "../../include/Milling/OpticalSorter.h"
#include <utility>

namespace FactorySim {

    // UML Logic: Throughput scales with nozzle_count
    OpticalSorter::OpticalSorter(std::string id, float accuracy, float false_reject, int nozzles)
        : Machine(std::move(id), nozzles * 50.0f), // Each nozzle processes 50kg/hr
          detection_accuracy(accuracy), false_rejection_rate(false_reject), 
          nozzle_count(nozzles), is_calibrated(true) {}

    void OpticalSorter::calibrate() {
        is_calibrated = true;
        // Resets the false rejection rate to its baseline
        false_rejection_rate = 0.01f; 
    }

    void OpticalSorter::process(Batch& batch, float dt) {
        if (status != MachineStatus::RUNNING) return;

        /**
         *NOTE: is_calibrated=false raises false_rejection_rate
         *Machines naturally drift out of calibration over time
         */
        if (hours_since_maint > maint_interval_h * 0.5f) {
            is_calibrated = false;
            false_rejection_rate += (0.05f * dt); // Gets worse over time
        }

        // The camera detects and removes visual defects e.g black beans, quakers
        float cleaning_power = detection_accuracy * efficiency;
        batch.reduceContamination(cleaning_power);

        // Simulating False Rejections
        float yield_loss_pct = false_rejection_rate * dt;
        
        // Adding the weight of the actual defects removed to the good beans accidentally shot out
        float total_weight_loss = (cleaning_power * 0.02f) + yield_loss_pct;
        
        batch.applyWeightLoss(total_weight_loss);
    }

    void OpticalSorter::onBreakdown() {
        // Cracked camera lens
        is_calibrated = false;
        detection_accuracy *= 0.10f;
    }
    
    void OpticalSorter::logEvent(EventLog& log) {}
}