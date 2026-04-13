#pragma once
#include <string>
#include <utility>
#include "CoreTypes.h"

namespace FactorySim {

    class Entity
    {
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