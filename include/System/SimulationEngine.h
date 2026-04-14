#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>

// Include your base classes
#include "../Core/Machine.h"
#include "../Core/Worker.h"
#include "../Core/Batch.h"

namespace FactorySim {

    class SimulationEngine {
    private:
        // Thread safety
        std::atomic<bool> is_running;
        std::mutex queue_mutex;

        // The Master Clock
        float current_time_hours;
        float dt_hours; // E.g. 0.1 hours per tick

        // Entity Lists (Allows growing/shrinking the factory dynamically)
        std::vector<std::unique_ptr<Machine>> factory_machines;
        std::vector<std::unique_ptr<Worker>> factory_workers;

        // The Factory Queues (Conveyor Belts)
        std::queue<std::unique_ptr<Batch>> farm_to_reception;
        std::queue<std::unique_ptr<Batch>> reception_to_cleaning;
        std::queue<std::unique_ptr<Batch>> cleaning_to_processing;
        std::queue<std::unique_ptr<Batch>> processing_to_milling;
        std::queue<std::unique_ptr<Batch>> milling_to_roasting;
        std::queue<std::unique_ptr<Batch>> roasting_to_packaging;
        std::queue<std::unique_ptr<Batch>> packaging_to_warehouse;
        std::queue<std::unique_ptr<Batch>> warehouse_to_sales;
        std::queue<std::unique_ptr<Batch>> sales_to_delivery;

    public:
        SimulationEngine();

        // Setup
        void initializeFactory();

        // The Master Loop
        void run();
        void stop();

        // Pipeline Stages
        void runReceptionStage();
        void runCleaningStage();
    };

}