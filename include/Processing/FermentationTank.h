#pragma once
#include "../Core/Machine.h"

namespace FactorySim {
    class FermentationTank : public Machine {
    private:
        float capacity_kg;
        float target_hours;
        float current_temp_c;
        float hours_elapsed;
        float over_ferment_risk;

    public:
        FermentationTank(std::string id, float capacity, float target_h, float temp);

        [[nodiscard]] bool isComplete() const;
        [[nodiscard]] float calcQualityDelta() const;

        void process(Batch& batch, float dt) override;
        void onBreakdown() override;
        void logEvent(EventLog& log) override;
    };
}