#include "../../include/Delivery/Driver.h"
#include <utility>

namespace FactorySim {

    Driver::Driver(std::string id, std::string name, float skill, std::string license, float threshold, float familiarity)
        : Worker(std::move(id), std::move(name), WorkerRole::GENERAL, skill), // Using GENERAL as a placeholder
          license_class(std::move(license)), hours_driven_today(0.0f), 
          fatigue_threshold_hours(threshold), route_familiarity(familiarity) {}

    bool Driver::canDrive() const {
        return hours_driven_today < fatigue_threshold_hours;
    }

    void Driver::work(float dt) {
        hours_driven_today += dt;
        accumulateFatigue(dt);
    }

    void Driver::logEvent(EventLog& log) {}
}