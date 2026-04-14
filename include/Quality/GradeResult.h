#pragma once
#include <string>

#include "../Core/CoreTypes.h"

namespace FactorySim {
    class GradeResult
    {
    public:
        std::string batch_id;
        CoffeeGrade grade;
        float defects_per_kg;
        float quality_score;
        Disposition disposition;
        std::string inspector_id;

        // Constructor
        GradeResult() : grade(CoffeeGrade::UNGRADED), defects_per_kg(0.0f),
                    quality_score(0.0f), disposition(Disposition::REPROCESS) {}
    };
}
