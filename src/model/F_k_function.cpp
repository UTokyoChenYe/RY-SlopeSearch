#include "model/F_k_function.hpp"
#include "model/match_tool.hpp"
#include <cmath>
#include <numeric>

FKFunction::FKFunction(const std::string& s1, const std::string& s2, const Config& cfg, Logger& log)
    : seq1(s1), seq2(s2), cfg(cfg), logger(log) {
    L1 = seq1.size();
    L2 = seq2.size();
    L_avg = (L1 + L2) / 2.0;
    
    int pattern_length = kmer_sampling_methods.at(cfg.sampling_method).get()[0].size();

    k_min = std::max(static_cast<int>(std::ceil((std::log(L_avg) + 0.69) / 0.875)), pattern_length);
    k_max = std::max(static_cast<int>(std::floor(std::log(L_avg) / 0.634)), pattern_length);
    if (k_min < pattern_length) logger.warn("k_min < pattern_length, adjusted to pattern_length");
    logger.info("Initialized FKFunction with k range: " + std::to_string(k_min) + "-" + std::to_string(k_max));
}

void FKFunction::compute_fk() {
    for (int k = k_min; k <= k_max; ++k) {
        double matches = calculate_kmer_matches(seq1, seq2, k, cfg.use_one_to_one_matching, cfg.sampling_method);
        double background = cfg.use_background_matches ? 2 * L1 * L2 * std::pow(0.25, k) : 0.0;
        double F = matches - background;
        if (F <= 0) F = 1e-6;
        Fk.push_back(F);
        Fk_log.push_back(std::log(F));
        k_vals.push_back(k);
    }
}

double FKFunction::calculate_p_hat() {
    compute_fk();
    std::vector<double> x(k_vals.begin(), k_vals.end());
    std::vector<double> y(Fk_log.begin(), Fk_log.end());
    double n = x.size();

    double mean_x = std::accumulate(x.begin(), x.end(), 0.0) / n;
    double mean_y = std::accumulate(y.begin(), y.end(), 0.0) / n;

    double num = 0.0, den = 0.0;
    for (size_t i = 0; i < n; ++i) {
        num += (x[i] - mean_x) * (y[i] - mean_y);
        den += (x[i] - mean_x) * (x[i] - mean_x);
    }
    double slope = num / den;
    double p_hat = std::exp(slope);
    logger.info("p_hat calculated: " + std::to_string(p_hat));
    return p_hat;
}
