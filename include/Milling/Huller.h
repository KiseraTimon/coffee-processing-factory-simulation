#pragma once
#include "../Core/Machine.h"

namespace FactorySim {
    class Huller : public Machine {
    private:
        float base_hull_breakage_rate;

    public:
        Huller(std::string id, float throughput, float breakage_rate);

        void process(Batch& batch, float dt) override;
        void onBreakdown() override;
        void logEvent(EventLog& log) override;
    };
}