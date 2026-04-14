#include "../../include/Core/Machine.h"
#include "../../include/Core/Utils.h"
#include <utility>

namespace FactorySim {
    Machine::Machine(
            std::string id,
            float throughput)
                :
        Entity(std::move(id)),
        status(MachineStatus::RUNNING),
        throughput_capacity(throughput),
        efficiency(1.0f),
        mtbf_hours(Utils::fillRandom(500.0f, 5000.0f)),
        mttr_hours(Utils::fillRandom(0.0f, 1.0f)),
        hours_since_maint(0.0f),
        maint_interval_h(Utils::fillRandom(100.0f, 500.0f)),
        energy_kw(Utils::fillRandom(10.0f, 100.0f)),
        cost_per_hour(Utils::fillRandom(5.0f, 10.0f))
    {}

    float Machine::getActualThroughput() const {
        return throughput_capacity * efficiency;
    }

    bool Machine::tryBreakdown(std::mt19937& rng, float delta) {
        /**
         *Simulating the probability of a breakdown based on the exponential distribution
        */
        if (status != MachineStatus::RUNNING) return false;

        std::exponential_distribution<float> exp_dist(1.0f / mtbf_hours);
        float time_to_next_failure = exp_dist(rng);

        if (time_to_next_failure < delta) {
            status = MachineStatus::BROKEN;
            onBreakdown(); // Calls the specific machine's breakdown side effects
            return true;
        }

        hours_since_maint += delta;
        return false;
    }

    void Machine::beginRepair() {
        if (status == MachineStatus::BROKEN) {
            status = MachineStatus::MAINTENANCE;
        }
    }

    void Machine::completeMaintenance() {
        status = MachineStatus::IDLE;
        hours_since_maint = 0.0f;
        efficiency = 1.0f; // Maintenance resets efficiency
    }


}