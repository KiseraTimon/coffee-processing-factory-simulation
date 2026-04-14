#include "../../include/Core/Worker.h"
#include "../../include/Core/Utils.h"
#include <utility>

namespace FactorySim {
    Worker::Worker(
            std::string id,
            std::string name,
            WorkerRole role,
            float skill_level)
        : Entity(std::move(id)),
        name(std::move(name)),
        role(role),
        skill_level(skill_level),
        fatigue(0.0f),
        error_rate(Utils::fillRandom(0.0f, 0.6f)),
        absent_prob(Utils::fillRandom(0.0f, 0.6f))
    {}

    void Worker::accumulateFatigue(float delta) {
        fatigue += (delta * 0.05f); // 5% fatigue per simulated hour
        if (fatigue > 1.0f) fatigue = 1.0f;
    }

    float Worker::getEfficiency() const {
        return (1.0f - fatigue) * skill_level;
    }

    void Worker::rest(float delta) {
        fatigue -= (delta * 0.10f); // Recover 10% per hour rested
        if (fatigue < 0.0f) fatigue = 0.0f;
    }

}