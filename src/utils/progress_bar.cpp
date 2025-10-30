#include "utils/progress_bar.hpp"
#include <iostream>
#include <iomanip>
#include <thread>

ProgressBar::ProgressBar(size_t total_steps, const std::string& title, bool enabled)
    : total_steps(total_steps), current_steps(0), title(title), enabled(enabled) {}

void ProgressBar::start() {
    if (!enabled) return;
    start_time = std::chrono::steady_clock::now();
    display();
}

void ProgressBar::increment() {
    if (!enabled) return;
    std::lock_guard<std::mutex> lock(mutex);
    ++current_steps;
    display();
}

void ProgressBar::finish() {
    if (!enabled) return;
    std::lock_guard<std::mutex> lock(mutex);
    current_steps = total_steps;
    display();
    std::cout << std::endl;
}

void ProgressBar::display() {
    if (!enabled) return;

    constexpr int bar_width = 50;
    float progress = static_cast<float>(current_steps) / total_steps;
    int pos = static_cast<int>(bar_width * progress);

    auto now = std::chrono::steady_clock::now();
    double elapsed_sec = std::chrono::duration<double>(now - start_time).count();

    std::cout << "\r[" << title << "] [";
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }

    std::cout << "] " << std::fixed << std::setprecision(1)
              << (progress * 100.0) << "% ("
              << current_steps << "/" << total_steps << ") "
              << std::setprecision(2) << elapsed_sec << "s elapsed" << std::endl;
}
