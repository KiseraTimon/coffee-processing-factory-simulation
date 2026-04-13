#pragma once
#include "Entity.h"
#include "Batch.h"
#include <random>
#include <utility>

namespace FactorySim {
    class Machine: public Entity
    {
    protected:
        MachineStatus status;
        float throughput_capacity;  // kg per hour
        float efficiency;           // 0.0 to 1.0
        float mtbf_hours;           // Mean Time Between Failures
        float mttr_hours;           // Mean Time To Repair
        float hours_since_maint;
        float maint_interval_h;
        float energy_kw;
        float cost_per_hour;

        // Pure Virtual: Derived classes to trigger specific breakdown logic
        virtual void onBreakdown() = 0;

        float fillRandom(float min, float max) {
            // Static generator so the method is only seeded once
            static std::mt19937 gen(std::random_device{}());

            // Uniform distribution for the range [0.0, 0.6]
            std::uniform_real_distribution<float> dis(min, max);

            return dis(gen);
        }

    public:
        Machine(
            std::string id,
            float throughput)
                :
        Entity(std::move(id)),
        status(MachineStatus::RUNNING),
        throughput_capacity(throughput),
        efficiency(1.0f),
        mtbf_hours(fillRandom(1.0f, 24.0f)),
        mttr_hours(fillRandom(0.0f, 1.0f)),
        hours_since_maint(0.0f),
        maint_interval_h(fillRandom(100.0f, 500.0f)),
        energy_kw(fillRandom(10.0f, 100.0f)),
        cost_per_hour(fillRandom(5.0f, 10.0f))
        {}

        // Pure Virtual: Processing Logic for Machines are Defined in Derived Classes
        virtual void process(Batch& batch, float delta) = 0;

        // Getters
        [[nodiscard]] float getActualThroughput() const {
            return throughput_capacity * efficiency;
        }

        // Modifiers
        bool tryBreakdown(std::mt19937& rng, float delta) {
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

        void beginRepair() {
            if (status == MachineStatus::BROKEN) {
                status = MachineStatus::MAINTENANCE;
            }
        }

        void completeMaintenance() {
            status = MachineStatus::IDLE;
            hours_since_maint = 0.0f;
            efficiency = 1.0f; // Maintenance resets efficiency
        }
    };
}