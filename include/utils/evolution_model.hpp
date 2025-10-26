#pragma once
#include "utils/logger.hpp"

/**
 * @brief estimate Jukes-Cantor distance based on matching probability
 *
 * d = -3/4 * log(1 - 4/3 * (1 - p_hat))
 *
 * @param p_hat estimated matching probability
 * @param logger logger
 * @return float estimated evolutionary distance (non-negative)
 */
float estimate_jukes_cantor_distance(float p_hat, Logger& logger);
