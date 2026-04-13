#pragma once
#include <string>
#include <random>
#include "CoreTypes.h"
#include "Entity.h"

namespace FactorySim {

    class Worker : public Entity
    {

    protected:
        std::string name;
        WorkerRole role;
        float skill_level;
        float fatigue;
        float error_rate;
        float absent_prob;

        void accumulateFatigue(float delta);

    public:
        Worker(
            std::string id,
            std::string name,
            WorkerRole role,
            float skill_level);

        [[nodiscard]] float getEfficiency() const;

        void rest(float delta);

        // Pure virtual: Specific workers (Harvester, Inspector) will define what 'work' does
        virtual void work(float dt) = 0;

    };

}