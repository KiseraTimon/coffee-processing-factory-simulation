#include "../../include/System/SimulationEngine.h"
#include "../../include/System/EventLog.h"
#include <chrono>

namespace FactorySim {

    SimulationEngine::SimulationEngine() : is_running(false), dt_hours(0.1f) {}

    void SimulationEngine::initializeFactory() {
        EventLog& log = EventLog::getInstance();
        log.log("SYS", "Initializing Factory Entities...");

        farms.push_back(std::make_unique<FarmPlot>("PLOT_01", CoffeeVariety::ARABICA, 10.0f, 1800, 5000.0f, 50000.0f, 0.0f, 0.0f));
        harvesters.push_back(std::make_unique<Harvester>("WKR_01", "John", 0.9f, 50.0f));
        harvesters[0]->assignPlot(farms[0].get());

        scale = std::make_unique<ReceptionScale>("SCALE_01", "Main Scale", 5000.0f, 0.1f, 0.05f, 0);
        tank = std::make_unique<FlotationTank>("TANK_01", 10000.0f, 20.0f, 0.95f, 2.0f, 30.0f);
        debris_remover = std::make_unique<DebrisRemover>("DR_01", 0.99f, 0.01f);
        pulper = std::make_unique<PulpingMachine>("PULP_01", 2000.0f, 1.5f, 0.02f);
        sorter = std::make_unique<OpticalSorter>("SORT_01", 0.98f, 0.01f, 4);
        roaster = std::make_unique<Roaster>("ROAST_01", 60.0f, RoastProfile::MEDIUM);
        packager = std::make_unique<PackagingMachine>("PACK_01", PackagingType::RETAIL_250G, 40.0f, 2.0f, 0.01f, 0.01f, 30.0f);
        warehouse = std::make_unique<Warehouse>("WH_01", 10000, 22.0f, 50.0f);
    }

    void SimulationEngine::stageHarvesting() {
        std::mt19937 rng(std::random_device{}());
        while (is_running) {
            for (auto& worker : harvesters) {
                auto new_batch = worker->performHarvest(dt_hours, rng);
                if (new_batch) {
                    queue_reception.push(std::move(new_batch));
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    void SimulationEngine::stageReception() {
        while (is_running) {
            if (auto batch_opt = queue_reception.try_pop()) {
                auto batch = std::move(*batch_opt);
                scale->process(*batch, dt_hours);

                EventLog::getInstance().log("SYS_QUEUE", "Batch " + batch->getId() + " moving to Cleaning Stage.");

                queue_cleaning.push(std::move(batch));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void SimulationEngine::stageCleaning() {
        while (is_running) {
            if (auto batch_opt = queue_cleaning.try_pop()) {
                auto batch = std::move(*batch_opt);
                tank->process(*batch, dt_hours);
                debris_remover->process(*batch, dt_hours);
                queue_processing.push(std::move(batch));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void SimulationEngine::stageProcessing() {
        while (is_running) {
            if (auto batch_opt = queue_processing.try_pop()) {
                auto batch = std::move(*batch_opt);
                pulper->process(*batch, dt_hours);
                queue_milling.push(std::move(batch));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void SimulationEngine::stageMilling() {
        while (is_running) {
            if (auto batch_opt = queue_milling.try_pop()) {
                auto batch = std::move(*batch_opt);
                sorter->process(*batch, dt_hours);
                queue_roasting.push(std::move(batch));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void SimulationEngine::stageRoasting() {
        while (is_running) {
            if (auto batch_opt = queue_roasting.try_pop()) {
                auto batch = std::move(*batch_opt);
                roaster->process(*batch, dt_hours);
                queue_packaging.push(std::move(batch));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void SimulationEngine::stagePackaging() {
        while (is_running) {
            if (auto batch_opt = queue_packaging.try_pop()) {
                auto batch = std::move(*batch_opt);
                packager->process(*batch, dt_hours);

                std::vector<PackageUnit> finished_bags = packager->collectOutput();
                for (auto& bag : finished_bags) {
                    warehouse->store(std::move(bag));
                }
            }
            warehouse->tick(dt_hours);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void SimulationEngine::run() {
        is_running = true;
        EventLog::getInstance().log("SYS", "Starting Master Threads...");

        std::thread t_harvest(&SimulationEngine::stageHarvesting, this);
        std::thread t_reception(&SimulationEngine::stageReception, this);
        std::thread t_cleaning(&SimulationEngine::stageCleaning, this);
        std::thread t_processing(&SimulationEngine::stageProcessing, this);
        std::thread t_milling(&SimulationEngine::stageMilling, this);
        std::thread t_roasting(&SimulationEngine::stageRoasting, this);
        std::thread t_packaging(&SimulationEngine::stagePackaging, this);

        while (is_running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        t_harvest.join();
        t_reception.join();
        t_cleaning.join();
        t_processing.join();
        t_milling.join();
        t_roasting.join();
        t_packaging.join();
    }

    void SimulationEngine::stop() {
        is_running = false;
    }
}