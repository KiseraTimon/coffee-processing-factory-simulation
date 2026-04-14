#pragma once
#include <string>
#include <vector>
#include <mutex>
#include <iostream>
#include "../Core/CoreTypes.h"

namespace FactorySim {
    struct LogEntry {
        std::string entity_id;
        std::string description;
    };

    class EventLog {
    private:
        std::vector<LogEntry> entries;
        std::mutex log_mutex;

        EventLog() = default;

    public:
        EventLog(const EventLog&) = delete;
        EventLog& operator=(const EventLog&) = delete;

        static EventLog& getInstance() {
            static EventLog instance;
            return instance;
        }

        void log(const std::string& entity_id, const std::string& desc) {
            std::lock_guard<std::mutex> lock(log_mutex);
            entries.push_back({entity_id, desc});
            std::cout << "[" << entity_id << "] " << desc << "\n";
        }
    };
}