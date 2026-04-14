#include "../../include/Harvest/Harvester.h"
#include "../../include/System/EventLog.h"
#include <iostream>
#include <utility>

namespace  FactorySim {
    // Constructor
    Harvester::Harvester(
        std::string id,
        std::string name,
        float skill,
        float pick_rate)
    :
    Worker(std::move(id), std::move(name), WorkerRole::HARVESTER, skill),
    pick_rate(pick_rate),
    assigned_plot(nullptr)
    {}

    void Harvester::assignPlot(FarmPlot *plot) {
        assigned_plot = plot;
    }

    void Harvester::work(float delta) {
        accumulateFatigue(delta);
    }

    std::unique_ptr<Batch> Harvester::performHarvest(float delta, std::mt19937 &rng) {
        if (assigned_plot == nullptr) {
            std::cout<<"Harvester "<<name<<" has NOT been assigned to a plot!"<<std::endl;
            return nullptr;
        }

        // Throughput Calculations Based on Fatigue & Skill
        float actual_rate = pick_rate * getEfficiency();
        float attempt_rate = actual_rate * delta;

        // Triggering Harvest
        auto new_batch = assigned_plot->harvest(getEfficiency(), rng);

        if (new_batch) {
            // Worker Error Rate Influencing Batch Contamination
            std::bernoulli_distribution error_dist(error_rate);


            new_batch->addContamination(error_dist(rng));

            if (error_dist(rng)) {
                // Worker Made Mistake Picking Cherries
                new_batch->addEvent("Harvester" + name + " made a mistake picking cherries!");
            } else {
                new_batch->addEvent("Harvester" + name + " collected clean cherries!");
            }

            EventLog::getInstance().log(getEntityId(),
                "Harvested " + std::to_string(new_batch->getWeight()) + "kg (Batch: " + new_batch->getId() + ")");
        }

        // Depleting Worker's Energy
        work(delta);

        return new_batch;
    }

    void Harvester::logEvent(EventLog &log) {
        // TODO: Add a singleton event logger
    }

}