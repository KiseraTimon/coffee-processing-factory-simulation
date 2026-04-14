#include "../../include/Milling/DensitySorter.h"
#include <utility>
#include <algorithm> // For std::min

namespace FactorySim {

    DensitySorter::DensitySorter(std::string id, float throughput, float vibration, float airflow)
        : Machine(std::move(id), throughput),
          vibration_hz(vibration), airflow_m3_per_min(airflow) {
        
        /**
         *Note: separation_efficiency is proportional to vibration_hz * airflow
         *Assumption is that  optimal settings are 50Hz and 100m3/min (Product = 5000)
         */
        separation_efficiency = (vibration_hz * airflow_m3_per_min) / 5000.0f;
        
        // Capped efficiency at 95% (no machine is perfect)
        separation_efficiency = std::min(separation_efficiency, 0.95f);
    }

    float DensitySorter::calcDefectsRemoved(float defect_count) const {
        return defect_count * separation_efficiency * efficiency;
    }

    void DensitySorter::process(Batch& batch, float dt) {
        if (status != MachineStatus::RUNNING) return;

        // Calculating how much contamination is being removed
        float defects_to_remove = calcDefectsRemoved(batch.getContamination());

        // Reducing the contamination in the batch
        batch.reduceContamination(separation_efficiency * efficiency);

        /**
         *Since we are physically blowing hollow/bad beans into a waste chute
         *the batch loses actual physical weight.
         */
        batch.applyWeightLoss(defects_to_remove * 0.10f); // Assuming defects make up a fraction of total mass
    }

    void DensitySorter::onBreakdown() {
        airflow_m3_per_min = 0.0f; // Blower motor died
        separation_efficiency = 0.0f;
    }
    
    void DensitySorter::logEvent(EventLog& log) {}
}