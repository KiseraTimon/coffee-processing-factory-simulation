#pragma once
#include "Entity.h"
#include "Batch.h"
#include <random>

namespace FactorySim {
    class Machine: public Entity
    {
    protected:
        MachineStatus status;
        float throughput_capacity;  // kg per hour
        float efficiency;           // 0.0 to 1.0
        float mtbf_hours;           // Mean time between failures
        float mttr_hours;           // Mean repair time
        float hours_since_maint;
        float maint_interval_h;
        float energy_kw;
        float cost_per_hour;

        // Pure Virtual: Derived classes to trigger specific breakdown logic
        virtual void onBreakdown() = 0;

    public:
        Machine(
            std::string id,
            float throughput);

        // Pure Virtual: Processing Logic for Machines are Defined in Derived Classes
        virtual void process(Batch& batch, float delta) = 0;

        // Getters
        [[nodiscard]] float getActualThroughput() const;

        // Modifiers
        bool tryBreakdown(std::mt19937& rng, float delta);

        void beginRepair();

        void completeMaintenance();
    };
}