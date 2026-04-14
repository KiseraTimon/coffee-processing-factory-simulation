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
        void addContamination(float amount);
        void adjustMoisture(float amount);
        void reduceContamination(float fraction);

        // Getters
        float getWeight() const { return weight_kg; }
        std::string getId() const { return batch_id; }
        BatchStage getStage() const { return current_stage; }
        float getContamination() const { return contamination; }
        float getRipeness() const { return cherry_ripeness; }
        float getMoisture() const { return moisture_pct; }
        void setStage(BatchStage stage) { current_stage = stage; }
    };

}