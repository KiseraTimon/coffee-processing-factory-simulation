#pragma once
#include "../Core/Machine.h"

namespace FactorySim {
    class Roaster : public Machine {
    private:
        float capacity_kg;
        RoastProfile profile;
        float drum_temp_c;
        float roast_duration_min;
        float dev_time_ratio;
        float cool_down_min;
        float weight_loss_pct;

        // Simulation state variable to lock the machine
        float current_cooldown_timer_h; 

    public:
        Roaster(std::string id, float capacity, RoastProfile profile);

        [[nodiscard]] float calcRoastLoss() const;

        void process(Batch& batch, float dt) override;
        void onBreakdown() override;
        void logEvent(EventLog& log) override;
    };
}