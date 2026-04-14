#pragma once
#include "../Core/Machine.h"

namespace FactorySim {
    class OpticalSorter : public Machine {
    private:
        float detection_accuracy;
        float false_rejection_rate;
        int nozzle_count;
        bool is_calibrated;

    public:
        OpticalSorter(std::string id, float accuracy, float false_reject, int nozzles);

        void calibrate();

        void process(Batch& batch, float dt) override;
        void onBreakdown() override;
        void logEvent(EventLog& log) override;
    };
}