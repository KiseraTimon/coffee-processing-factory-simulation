#pragma once
#include <string>
#include <vector>

namespace FactorySim {

    enum class BatchStage {
        HARVESTED, RECEIVED, GRADED, CLEANED, PROCESSING, 
        MILLED, ROASTED, PACKAGED, WAREHOUSED, SOLD, DELIVERED
    };

    enum class MachineStatus {
        RUNNING, IDLE, BROKEN, MAINTENANCE
    };

    enum class WorkerRole {
        NONE, GENERAL, RECEIVER, ROASTER, GRADER, PACKAGER, TECHNICIAN, MANAGER
    };

    enum WorkerShift {
        MORNING, AFTERNOON, DAY, NIGHT
    };

    enum class CoffeeGrade {
        AA, AB, C, PEABERRY, BELOW_GRADE, UNGRADED
    };

    enum class CoffeeVariety {
        ARABICA, ROBUSTA, SL28, SL34, BOURBON, TYPICA, GESHA
    };

    enum class ProcessingMethod {
        WASHED, NATURAL, HONEY, UNASSIGNED
    };

    // Forward declaration of Event Logs
    class EventLog; 
}