#pragma once
#include <string>
#include <utility>
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

        void accumulateFatigue(float delta) {
            fatigue += (delta * 0.05f); // 5% fatigue per simulated hour
            if (fatigue > 1.0f) fatigue = 1.0f;
        }

    public:
        Worker(
            std::string id,
            std::string name,
            WorkerRole role,
            float skill_level)
        : Entity(std::move(id)),
        name(std::move(name)),
        role(role),
        skill_level(skill_level),
        fatigue(0.0f),
        error_rate(fillRandom(0.0f, 0.6f)),
        absent_prob((fillRandom(0.0f, 0.6f)))
        {}

        [[nodiscard]] float getEfficiency() const {
            return (1.0f - fatigue) * skill_level;
        }

        void rest(float hours) {
            fatigue -= (hours * 0.10f); // Recover 10% per hour rested
            if (fatigue < 0.0f) fatigue = 0.0f;
        }

        // Pure virtual: Specific workers (Harvester, Inspector) will define what 'work' does
        virtual void work(float dt) = 0;

    };

}