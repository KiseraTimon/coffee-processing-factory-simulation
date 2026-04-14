#include "include/System/SimulationEngine.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "========================================\n";
    std::cout << "   COFFEE FACTORY SIMULATION V1.0       \n";
    std::cout << "========================================\n";

    FactorySim::SimulationEngine engine;

    engine.initializeFactory();

    // Running the simulation engine in a background thread to stop it safely in future
    std::thread engine_thread(&FactorySim::SimulationEngine::run, &engine);

    // Running the factory for 30 seconds
    std::this_thread::sleep_for(std::chrono::seconds(30));

    std::cout << "\n[SYS] Shutting down factory pipeline...\n";
    engine.stop();
    engine_thread.join();

    std::cout << "Simulation Complete. Exiting.\n";
    return 0;
}