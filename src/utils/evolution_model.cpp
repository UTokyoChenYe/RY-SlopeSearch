#include "utils/evolution_model.hpp"
#include <cmath>
#include <iostream>

float estimate_jukes_cantor_distance(float p_hat) {
    if (p_hat >= 1.0f) {
        std::cerr << "p_hat >= 1, adjusted to 0.999 to prevent log(0)" << std::endl;
        p_hat = 0.999f;
    }
    try {
        float distance = -0.75f * std::log(1 - (4.0f / 3.0f) * (1 - p_hat));
        return std::max(0.0f, distance);
    } catch (...) {
        std::cerr << "Error calculating Jukes-Cantor distance" << std::endl;
        return 0.0f;
    }
}
