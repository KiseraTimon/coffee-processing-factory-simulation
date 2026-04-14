# ☕ Coffee Processing Factory Simulation

![C++ Version](https://img.shields.io/badge/C%2B%2B-17%2B-blue.svg)
![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Architecture](https://img.shields.io/badge/architecture-Multithreaded_OOP-orange.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)

An advanced, multithreaded Object-Oriented C++ simulation of a modern coffee "Wet Mill" processing facility. This project simulates the entire lifecycle of coffee production—from agricultural harvesting and chemical processing to dynamic warehouse management and probabilistically driven sales logistics.

## 📖 Table of Contents
- [Overview](#-overview)
- [Key Features](#-key-features)
- [Factory Pipeline (The Stages)](#-factory-pipeline-the-stages)
- [Core Architecture](#-core-architecture)
- [Mathematical Models](#-mathematical-models)
- [Project Structure](#-project-structure)
- [Building and Running](#-building-and-running)
- [Future Enhancements](#-future-enhancements)

---

## 🔬 Overview
This project was built to explore advanced C++ concepts (such as polymorphism, memory ownership via smart pointers, thread synchronization, and discrete-event simulation). It models the flow of raw material (`Batch`) through a series of workers and machines.

Machines experience wear and tear, workers suffer from fatigue, weather affects processing times, and random events (like road traffic or machine breakdowns) occur dynamically, forcing the simulation to react to bottlenecks in real-time.

---

## ✨ Key Features
* **Multithreaded Engine:** The factory utilizes `std::thread` to run multiple processing stages concurrently, connected by custom `ThreadSafeQueue` buffers.
* **Strict Memory Safety:** Heavy reliance on `std::unique_ptr` and `std::move` semantics. A physical batch of coffee can mathematically only exist in one place at a time.
* **Abstract Base Classes:** Strong OOP principles using pure virtual functions (`Machine`, `Worker`, `Entity`) to guarantee consistent polymorphic behavior.
* **Data-Driven Randomness:** Uses `<random>` (`std::normal_distribution`, `std::poisson_distribution`, `std::bernoulli_distribution`) to simulate real-world variance in worker skill, machine breakdowns, and customer behavior.
* **Thread-Safe Singletons:** Includes a global `EventLog` and a dynamic `WeatherModel` that safely interact across all running threads.

---

## 🏭 Factory Pipeline (The Stages)

The simulation routes a `Batch` payload through 11 distinct stages:

| Stage | Entities Involved | Description |
| :--- | :--- | :--- |
| **1. Harvest** | `FarmPlot`, `Harvester` | Workers pick cherries based on skill/fatigue. Depletes farm density. |
| **2. Reception** | `ReceptionScale`, `Clerk` | Weighs incoming batches. Human error can introduce data inaccuracies. |
| **3. Cleaning** | `FlotationTank`, `DebrisRemover` | Removes floating defects and twigs. Machines degrade over time. |
| **4. Quality** | `QualityInspector` | Grades the coffee. Fatigue increases false-positive rejection rates. |
| **5. Processing** | `Pulper`, `FermentationTank`, `DryingBed` | Removes mucilage. Time and temperature drive chemistry and moisture. |
| **6. Milling** | `Huller`, `DensitySorter`, `OpticalSorter` | Transitions parchment to green coffee using lasers and airflow. |
| **7. Roasting** | `Roaster` | Batch-processing drum that applies extreme heat, causing 15-20% weight loss. |
| **8. Packaging** | `PackagingMachine` | Converts the bulk `Batch` mass into hundreds of discrete `PackageUnit` bags. |
| **9. Warehouse** | `Warehouse`, `InventoryRecord` | `O(1)` ledger system. Coffee shelf-life degrades based on warehouse temperature. |
| **10. Sales** | `Customer`, `Order` | Autonomous agents generate orders and evaluate prices based on psychology. |
| **11. Delivery** | `Vehicle`, `Driver`, `Route` | Fulfills orders. Factors in traffic, distance, and vehicle breakdowns. |

---

## 🏗️ Core Architecture

### **The Payload: `Batch`**
Instead of swapping object types (which causes slicing/polymorphism traps), `Batch` acts as a **Stateful Token**. It carries all mutable data (weight, moisture, contamination, grade, roast color) and changes its `BatchStage` enum as it flows through the pipeline.

### **The Actors: `Machine` & `Worker`**
Both inherit from `Entity` (providing a unique ID and logging contract).
* `Machine` handles throughput capacity, efficiency decay, and Mean-Time-Between-Failures (MTBF).
* `Worker` handles stamina, shift roles, and error rates.

### **The Engine: `SimulationEngine`**
The master loop of the application. It initializes all pointers, launches the background threads (`std::thread`), and manages the `std::mutex` locks required to safely move pointers from one queue to the next.

---

## 🧮 Mathematical Models
The simulation is grounded in real-world physics and economics:
* **The Arrhenius Equation:** Used in the `FermentationTank` and `Warehouse` to simulate chemical reaction rates. For every 10°C increase in temperature, fermentation and staling happen twice as fast.
* **Poisson Arrival Process:** Used by the `Customer` class to generate realistic, sporadic order arrivals based on a mean frequency.
* **Logistic Sigmoid Function:** Used in the Sales desk to model price sensitivity. If the factory's price exceeds the customer's "willingness to pay," the probability of a sale drops along a smooth S-curve rather than an instant hard-fail.
* **Exponential Distribution:** Used inside the base `Machine` class to predict the exact time until the next random hardware breakdown.

---

## 📂 Project Structure

```text
CoffeeFactorySim/
├── CMakeLists.txt
├── include/
│   ├── Cleaning/      # Tanks, Debris Removers
│   ├── Core/          # Base Classes (Batch, Entity, Machine, Worker, Types)
│   ├── Delivery/      # Vehicles, Drivers, Routes
│   ├── Harvest/       # Harvesters, FarmPlots
│   ├── Milling/       # Hullers, Sorters
│   ├── Packaging/     # Bagging machines, Package Units
│   ├── Processing/    # Weather, Pulping, Fermentation, Drying
│   ├── Quality/       # Inspectors, Grade Results
│   ├── Reception/     # Scales, Clerks, Intake Records
│   ├── Roasting/      # Drum Roasters
│   ├── Sales/         # Customers, Orders
│   ├── System/        # Simulation Engine, EventLog, ThreadSafeQueue
│   └── Warehouse/     # Inventory Ledgers, Storage
├── src/               # Contains matching .cpp files for all headers above
└── main.cpp           # The application entry point
```

---

## Here is the complete README.md file content. You can easily copy this and save it directly as README.md in the root of your project folder.

Markdown
# ☕ Coffee Processing Factory Simulation

![C++ Version](https://img.shields.io/badge/C%2B%2B-17%2B-blue.svg)
![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Architecture](https://img.shields.io/badge/architecture-Multithreaded_OOP-orange.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)

An advanced, multithreaded Object-Oriented C++ simulation of a modern coffee "Wet Mill" processing facility. This project simulates the entire lifecycle of coffee production—from agricultural harvesting and chemical processing to dynamic warehouse management and probabilistically driven sales logistics.

## 📖 Table of Contents
- [Overview](#-overview)
- [Key Features](#-key-features)
- [Factory Pipeline (The Stages)](#-factory-pipeline-the-stages)
- [Core Architecture](#-core-architecture)
- [Mathematical Models](#-mathematical-models)
- [Project Structure](#-project-structure)
- [Building and Running](#-building-and-running)
- [Future Enhancements](#-future-enhancements)

---

## 🔬 Overview
This project was built to explore advanced C++ concepts (such as polymorphism, memory ownership via smart pointers, thread synchronization, and discrete-event simulation). It models the flow of raw material (`Batch`) through a series of workers and machines.

Machines experience wear and tear, workers suffer from fatigue, weather affects processing times, and random events (like road traffic or machine breakdowns) occur dynamically, forcing the simulation to react to bottlenecks in real-time.

---

## ✨ Key Features
* **Multithreaded Engine:** The factory utilizes `std::thread` to run multiple processing stages concurrently, connected by custom `ThreadSafeQueue` buffers.
* **Strict Memory Safety:** Heavy reliance on `std::unique_ptr` and `std::move` semantics. A physical batch of coffee can mathematically only exist in one place at a time.
* **Abstract Base Classes:** Strong OOP principles using pure virtual functions (`Machine`, `Worker`, `Entity`) to guarantee consistent polymorphic behavior.
* **Data-Driven Randomness:** Uses `<random>` (`std::normal_distribution`, `std::poisson_distribution`, `std::bernoulli_distribution`) to simulate real-world variance in worker skill, machine breakdowns, and customer behavior.
* **Thread-Safe Singletons:** Includes a global `EventLog` and a dynamic `WeatherModel` that safely interact across all running threads.

---

## 🏭 Factory Pipeline (The Stages)

The simulation routes a `Batch` payload through 11 distinct stages:

| Stage | Entities Involved | Description |
| :--- | :--- | :--- |
| **1. Harvest** | `FarmPlot`, `Harvester` | Workers pick cherries based on skill/fatigue. Depletes farm density. |
| **2. Reception** | `ReceptionScale`, `Clerk` | Weighs incoming batches. Human error can introduce data inaccuracies. |
| **3. Cleaning** | `FlotationTank`, `DebrisRemover` | Removes floating defects and twigs. Machines degrade over time. |
| **4. Quality** | `QualityInspector` | Grades the coffee. Fatigue increases false-positive rejection rates. |
| **5. Processing** | `Pulper`, `FermentationTank`, `DryingBed` | Removes mucilage. Time and temperature drive chemistry and moisture. |
| **6. Milling** | `Huller`, `DensitySorter`, `OpticalSorter` | Transitions parchment to green coffee using lasers and airflow. |
| **7. Roasting** | `Roaster` | Batch-processing drum that applies extreme heat, causing 15-20% weight loss. |
| **8. Packaging** | `PackagingMachine` | Converts the bulk `Batch` mass into hundreds of discrete `PackageUnit` bags. |
| **9. Warehouse** | `Warehouse`, `InventoryRecord` | `O(1)` ledger system. Coffee shelf-life degrades based on warehouse temperature. |
| **10. Sales** | `Customer`, `Order` | Autonomous agents generate orders and evaluate prices based on psychology. |
| **11. Delivery** | `Vehicle`, `Driver`, `Route` | Fulfills orders. Factors in traffic, distance, and vehicle breakdowns. |

---

## 🏗️ Core Architecture

### **The Payload: `Batch`**
Instead of swapping object types (which causes slicing/polymorphism traps), `Batch` acts as a **Stateful Token**. It carries all mutable data (weight, moisture, contamination, grade, roast color) and changes its `BatchStage` enum as it flows through the pipeline.

### **The Actors: `Machine` & `Worker`**
Both inherit from `Entity` (providing a unique ID and logging contract).
* `Machine` handles throughput capacity, efficiency decay, and Mean-Time-Between-Failures (MTBF).
* `Worker` handles stamina, shift roles, and error rates.

### **The Engine: `SimulationEngine`**
The master loop of the application. It initializes all pointers, launches the background threads (`std::thread`), and manages the `std::mutex` locks required to safely move pointers from one queue to the next.

---

## 🧮 Mathematical Models
The simulation is grounded in real-world physics and economics:
* **The Arrhenius Equation:** Used in the `FermentationTank` and `Warehouse` to simulate chemical reaction rates. For every 10°C increase in temperature, fermentation and staling happen twice as fast.
* **Poisson Arrival Process:** Used by the `Customer` class to generate realistic, sporadic order arrivals based on a mean frequency.
* **Logistic Sigmoid Function:** Used in the Sales desk to model price sensitivity. If the factory's price exceeds the customer's "willingness to pay," the probability of a sale drops along a smooth S-curve rather than an instant hard-fail.
* **Exponential Distribution:** Used inside the base `Machine` class to predict the exact time until the next random hardware breakdown.

---

## 📂 Project Structure

```text
CoffeeFactorySim/
├── CMakeLists.txt
├── include/
│   ├── Cleaning/      # Tanks, Debris Removers
│   ├── Core/          # Base Classes (Batch, Entity, Machine, Worker, Types)
│   ├── Delivery/      # Vehicles, Drivers, Routes
│   ├── Harvest/       # Harvesters, FarmPlots
│   ├── Milling/       # Hullers, Sorters
│   ├── Packaging/     # Bagging machines, Package Units
│   ├── Processing/    # Weather, Pulping, Fermentation, Drying
│   ├── Quality/       # Inspectors, Grade Results
│   ├── Reception/     # Scales, Clerks, Intake Records
│   ├── Roasting/      # Drum Roasters
│   ├── Sales/         # Customers, Orders
│   ├── System/        # Simulation Engine, EventLog, ThreadSafeQueue
│   └── Warehouse/     # Inventory Ledgers, Storage
├── src/               # Contains matching .cpp files for all headers above
└── main.cpp           # The application entry point
```

## 🚀 Building and Running
This project uses CMake as its build system. Ensure you have a modern C++ compiler (supporting C++17 or higher) installed (e.g., GCC, Clang, or MSVC).
* Clone the repository
```bash
git clone https://github.com/KiseraTimon/coffee-processing-factory-simulation.git
```

* Navigate into the repository
```bash
cd coffee-processing-factory-simulation
```

* Create a build directory
```bash
mkdir build
```
```bash
cd build
```

* Run CMake and compile
```bash
cmake ..
```

```bash
cmake --build
```

Open the project in your IDE (Preferably CLion). It will detect the CMakeLists.txt file. Select the `Coffee_Processing_Factory_Simulation` target and press run

## 🔮 Future Enhancements
* **Financial Ledger**: Track operational costs (electricity, water, wages) vs. order revenue to calculate live factory ROI.

* **UI/Dashboard** :Attach a frontend visualizer (like Dear ImGui or a web-based socket) to the SimulationEngine to watch queue bottlenecks form in real-time.

* **Dynamic Hiring / Scaling**: Allow the SimulationEngine to automatically hire more workers or buy more machines when it detects a massive backlog in a specific queue.

---

*Built with C++ to explore the beautiful intersection of software architecture and industrial engineering.*

