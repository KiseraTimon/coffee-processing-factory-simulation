#include "include/System/SimulationEngine.h"
#include <iostream>

int main() {
    std::cout << "--- COFFEE FACTORY SIMULATION ---\n";

    FactorySim::SimulationEngine engine;

    // Building the machines and workers
    engine.initializeFactory();

    // Starting the simulation loop
    engine.run();

    return 0;
}