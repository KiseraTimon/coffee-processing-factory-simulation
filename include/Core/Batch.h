#pragma once
#include <string>
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

        static float fillRandom(float min, float max) {
            // Static generator so the method is only seeded once
            static std::mt19937 gen(std::random_device{}());

            // Uniform distribution for the range [0.0, 0.6]
            std::uniform_real_distribution<float> dis(min, max);

            return dis(gen);
        }

    public:
        Batch(
            std::string id,
            std::string farm_id,
            CoffeeVariety var,
            float initial_weight);

        // Modifiers
        void applyWeightLoss(float fraction);
        void updateGrade(CoffeeGrade new_grade);
        void addEvent(const std::string& desc);

        // Getters
        [[nodiscard]] float getWeight() const { return weight_kg; }
        [[nodiscard]] std::string getId() const { return batch_id; }
        [[nodiscard]] BatchStage getStage() const { return current_stage; }
        void setStage(BatchStage stage) { current_stage = stage; }
    };

}