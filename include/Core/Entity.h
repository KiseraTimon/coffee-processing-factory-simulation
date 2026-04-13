#pragma once
#include <string>
#include <utility>
#include "CoreTypes.h"

namespace FactorySim {

    class Entity
    {
    private:
        static float fillRandom(float min, float max) {
            // Static generator so the method is only seeded once
            static std::mt19937 gen(std::random_device{}());

            // Uniform distribution for the range [0.0, 0.6]
            std::uniform_real_distribution<float> dis(min, max);

            return dis(gen);
        }

    protected:
        std::string entity_id;

    public:
        // Constructor
        explicit Entity(std::string id): entity_id(std::move(id)){}

        // Destructor
        virtual ~Entity() = default;

        // Getter
        [[nodiscard]] std::string getEntityId() const {return entity_id;}

        // Pure Virtual: Every derived class must implement its own logging logic
        virtual void logEvent(EventLog& log) = 0;
    };

}