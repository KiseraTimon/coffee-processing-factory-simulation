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
        NONE, GENERAL, HARVESTER, RECEIVER, ROASTER, GRADER, PACKAGER, TECHNICIAN, MANAGER
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

    enum class Certificate {
        NONE, Q_GRADER, LICENSED_CUPPER
    };

    enum class Disposition {
        ACCEPTED, REJECTED, REPROCESS
    };

    enum class RoastProfile {
        LIGHT, MEDIUM, DARK, ESPRESSO
    };

    enum class PackagingType {
        RETAIL_250G, RETAIL_500G, EXPORT_60KG
    };

    // Forward declaration of Event Logs
    class EventLog;
}