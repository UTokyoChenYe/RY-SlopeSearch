#pragma once

#include <mutex>
#include <string>
#include <chrono>

class ProgressBar {
public:
    ProgressBar(size_t total_steps, const std::string& title = "", bool enabled = true);
    void start();
    void increment();
    void finish();

private:
    void display();

    size_t total_steps;
    size_t current_steps;
    std::string title;
    bool enabled;

    std::mutex mutex;
    std::chrono::time_point<std::chrono::steady_clock> start_time;
};
