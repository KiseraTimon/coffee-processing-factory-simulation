#pragma once
#include "../Core/Machine.h"

namespace FactorySim {
    class DensitySorter : public Machine {
    private:
        float separation_efficiency;
        float vibration_hz;
        float airflow_m3_per_min;

    public:
        DensitySorter(std::string id, float throughput, float vibration, float airflow);

        [[nodiscard]] float calcDefectsRemoved(float defect_count) const;

        void process(Batch& batch, float dt) override;
        void onBreakdown() override;
        void logEvent(EventLog& log) override;
    };
}