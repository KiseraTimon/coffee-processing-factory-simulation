#pragma once
#include <string>
#include <chrono>
#include <utility>

namespace FactorySim {
    struct PackageUnit {
        std::string package_id;
        std::string batch_id;
        float net_weight_g;
        std::string lot_code;
        bool seal_ok;
        bool label_ok;
        std::chrono::system_clock::time_point packaging_date;

        PackageUnit(
            std::string p_id,
            std::string b_id,
            float weight,
            std::string lot,
            bool seal,
            bool label)
            :
        package_id(std::move(p_id)),
        batch_id(std::move(b_id)),
        net_weight_g(weight),
        lot_code(std::move(lot)),
        seal_ok(seal),
        label_ok(label),
        packaging_date(std::chrono::system_clock::now()) {}
    };
}