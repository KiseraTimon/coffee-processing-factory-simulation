#include "../../include/Core/Batch.h"
#include "../../include/Core/Utils.h"
#include <utility>

namespace FactorySim {

    // Constructor
    Batch::Batch(
        std::string id,
        std::string farm_id,
        CoffeeVariety var,
        float initial_weight)
        :
    batch_id(std::move(id)),
    origin_farm_id(std::move(farm_id)),
    variety(var),
    method(ProcessingMethod::UNASSIGNED),
    grade(CoffeeGrade::UNGRADED),
    current_stage(BatchStage::HARVESTED),
    weight_kg(initial_weight),
    cherry_ripeness(Utils::fillRandom(0.7f, 1.0f)), // Random ripeness
    moisture_pct(Utils::fillRandom(0.3f, 0.7f)),    // Random moisture
    contamination(Utils::fillRandom(0.0f, 0.4f)),   // Random contamination
    roast_color_score(0.0f),
    degassing_hours_req(0.0f) {}

    // Modifiers

    void Batch::applyWeightLoss(float fraction) {
        weight_kg -= (weight_kg * fraction);

        // Safety check to ensure floating point math doesn't result in negative mass
        if (weight_kg < 0.0f) {
            weight_kg = 0.0f;
        }
    }

    void Batch::updateGrade(CoffeeGrade new_grade) {
        grade = new_grade;
    }

    void Batch::addEvent(const std::string& desc) {
        event_trail.push_back(desc);
    }

}