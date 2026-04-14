#pragma once
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <random>

#include "ThreadSafeQueue.h"
#include "../Core/Batch.h"
#include "../Harvest/FarmPlot.h"
#include "../Harvest/Harvester.h"
#include "../Reception/ReceptionScale.h"
#include "../Cleaning/FlotationTank.h"
#include "../Cleaning/DebrisRemover.h"
#include "../Processing/PulpingMachine.h"
#include "../Milling/OpticalSorter.h"
#include "../Roasting/Roaster.h"
#include "../Packaging/PackagingMachine.h"
#include "../Warehouse/Warehouse.h"

namespace FactorySim {
    class SimulationEngine {
    private:
        std::atomic<bool> is_running;
        float dt_hours;

        // Factory Entities
        std::vector<std::unique_ptr<FarmPlot>> farms;
        std::vector<std::unique_ptr<Harvester>> harvesters;
        std::unique_ptr<ReceptionScale> scale;
        std::unique_ptr<FlotationTank> tank;
        std::unique_ptr<DebrisRemover> debris_remover;
        std::unique_ptr<PulpingMachine> pulper;
        std::unique_ptr<OpticalSorter> sorter;
        std::unique_ptr<Roaster> roaster;
        std::unique_ptr<PackagingMachine> packager;
        std::unique_ptr<Warehouse> warehouse;

        // Conveyor Belts (Queues)
        ThreadSafeQueue<std::unique_ptr<Batch>> queue_reception;
        ThreadSafeQueue<std::unique_ptr<Batch>> queue_cleaning;
        ThreadSafeQueue<std::unique_ptr<Batch>> queue_processing;
        ThreadSafeQueue<std::unique_ptr<Batch>> queue_milling;
        ThreadSafeQueue<std::unique_ptr<Batch>> queue_roasting;
        ThreadSafeQueue<std::unique_ptr<Batch>> queue_packaging;

    public:
        SimulationEngine();
        void initializeFactory();
        void run();
        void stop();

    private:
        // Thread loops
        void stageHarvesting();
        void stageReception();
        void stageCleaning();
        void stageProcessing();
        void stageMilling();
        void stageRoasting();
        void stagePackaging();
    };
}