#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

namespace FactorySim {
    template <typename T>
    class ThreadSafeQueue {
    private:
        std::queue<T> queue;
        std::mutex mutex;
        std::condition_variable cond_var;

    public:
        void push(T item) {
            std::lock_guard<std::mutex> lock(mutex);
            queue.push(std::move(item));
            cond_var.notify_one();
        }

        std::optional<T> try_pop() {
            std::lock_guard<std::mutex> lock(mutex);
            if (queue.empty()) {
                return std::nullopt;
            }
            T item = std::move(queue.front());
            queue.pop();
            return item;
        }

        bool empty() {
            std::lock_guard<std::mutex> lock(mutex);
            return queue.empty();
        }
    };
}