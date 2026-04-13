#pragma once
#include <string>
#include <utility>
#include <random>
#include "CoreTypes.h"
#include "Entity.h"

namespace FactorySim {

    class Worker : public Entity
    {
    private:
        float fillRandom() {
            // Static generator so the method is only seeded once
            static std::mt19937 gen(std::random_device{}());

            // Uniform distribution for the range [0.0, 0.6]
            std::uniform_real_distribution<float> dis(0.0f, 0.6f);

            return dis(gen);
        }

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
        error_rate(fillRandom()),
        absent_prob((fillRandom()))
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