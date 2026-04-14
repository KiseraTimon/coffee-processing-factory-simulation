#include "../../include/Quality/QualityInspector.h"
#include "../../include/Core/Utils.h"

namespace FactorySim {
    QualityInspector::QualityInspector(
        std::string id,
        std::string name,
        float speed,
        float false_positive_rate,
        float false_negative_rate)
            :
    Worker(id, name, WorkerRole::GRADER, Utils::fillRandom(0.0f, 1.0f)),
    certificate(Certificate::NONE),
    inspection_speed(speed),
    false_positive_rate(false_positive_rate),
    false_negative_rate(false_negative_rate)
    {}

    GradeResult QualityInspector::inspect(const Batch& batch, std::mt19937& rng) {
        // Fatigue Penalty
        float fatigue_penalty = 1.0f + (fatigue * 0.5f);
        float current_fp = false_positive_rate * fatigue_penalty;
        float current_fn = false_negative_rate * fatigue_penalty;

        // Batch True State (20% contamination or above is a bad batch)
        bool is_bad_batch = batch.getContamination() > 0.20f;

        // Human Error Probabilities
        std::uniform_real_distribution<float> err_prob(0.0f, 1.0f);
        bool reject_batch = is_bad_batch;

        if ((is_bad_batch && err_prob(rng)) < current_fn) {
            reject_batch = false;
        }
        else if ((is_bad_batch && err_prob(rng)) < current_fp) {
            reject_batch = true;
        }

        // Results
        GradeResult result;
        result.batch_id = batch.getId();
        result.inspector_id = this->getEntityId();
        result.defects_per_kg = batch.getContamination() * 100.0f; // Temporary conversion
        result.quality_score = batch.getRipeness() * 100.0f;    // Temporary conversion

        if (reject_batch) {
            result.grade = CoffeeGrade::BELOW_GRADE;
            result.disposition = Disposition::REJECTED;
        }
        else {
            result.grade = CoffeeGrade::AA; // Assuming highest grade; to implement multi-grading later
            result.disposition = Disposition::ACCEPTED;
        }

        // Fatigue Simulation
        float time_taken_mins = batch.getWeight() / inspection_speed;
        work(time_taken_mins / 60.0f);

        return result;
    }

    void QualityInspector::work(float dt) {
        accumulateFatigue(dt);
    }

    void QualityInspector::logEvent(EventLog &log) {
        //
    }

}