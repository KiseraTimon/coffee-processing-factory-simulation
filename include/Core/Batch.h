#pragma once
#include <string>
#include <utility>
#include <vector>
#include <random>
#include "CoreTypes.h"

namespace FactorySim {

    class Batch {
    private:
        std::string batch_id;
        std::string origin_farm_id;
        CoffeeVariety variety;
        ProcessingMethod method;
        CoffeeGrade grade;
        BatchStage current_stage;

        float weight_kg;
        float cherry_ripeness;
        float moisture_pct;
        float contamination;

        // Roasting-specific attributes (default to 0 until Stage 7)
        float roast_color_score;
        float degassing_hours_req;

        std::vector<std::string> event_trail;

    public:
        Batch(
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
        cherry_ripeness(fillRandom(0.7f, 1.0f)),
        moisture_pct(fillRandom(0.3f, 0.7f)),
        contamination(fillRandom(0.0f, 0.4f)),
        roast_color_score(0.0f),
        degassing_hours_req(0.0f) {}

        // Modifiers
        void applyWeightLoss(float fraction) {
            weight_kg -= (weight_kg * fraction);
            if (weight_kg < 0.0f) weight_kg = 0.0f;
        }

        void updateGrade(CoffeeGrade new_grade) {
            grade = new_grade;
        }

        void addEvent(const std::string& desc) {
            event_trail.push_back(desc);
        }

        // Getters
        [[nodiscard]] float getWeight() const { return weight_kg; }
        [[nodiscard]] std::string getId() const { return batch_id; }
        [[nodiscard]] BatchStage getStage() const { return current_stage; }
        void setStage(BatchStage stage) { current_stage = stage; }
    };

}