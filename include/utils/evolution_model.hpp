#pragma once

/**
 * @brief 根据匹配概率估计 Jukes-Cantor 距离
 *
 * d = -3/4 * log(1 - 4/3 * (1 - p_hat))
 *
 * @param p_hat 匹配概率估计值
 * @return float 估计的进化距离（非负）
 */
float estimate_jukes_cantor_distance(float p_hat);
