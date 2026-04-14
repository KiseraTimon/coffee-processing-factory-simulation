#include "../../include/Core/Utils.h"

namespace FactorySim {
    float Utils::fillRandom(float min, float max) {
        static std::mt19937 gen(std::random_device{}());

        std::uniform_real_distribution<float> dis(min, max);

        return dis(gen);
    }

}