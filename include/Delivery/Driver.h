#pragma once
#include "../Core/Worker.h"

namespace FactorySim {
    class Driver : public Worker {
    private:
        std::string license_class;
        float hours_driven_today;
        float fatigue_threshold_hours;
        float route_familiarity;

    public:
        Driver(std::string id, std::string name, float skill, std::string license, float threshold, float familiarity);

        [[nodiscard]] bool canDrive() const;
        [[nodiscard]] float getFamiliarity() const { return route_familiarity; }

        void work(float dt) override;
        void logEvent(EventLog& log) override;
    };
}