#pragma once
#include <string>
#include <vector>
#include "utils/logger.hpp"
#include "utils/config.hpp"

class FKFunction {
public:
    FKFunction(const std::string& seq1, const std::string& seq2, char* dna_kmer_to_num, int pattern_length, std::vector<char>& table, const Config& cfg, Logger& logger);
    double calculate_p_hat();
    void compute_fk();
    const std::vector<double>& get_FkLog() const { return Fk_log; }
    std::vector<int> k_vals;
    std::vector<double> Fk;
    std::vector<double> Fk_log;

private:
    std::string seq1, seq2;
    int L1, L2;
    int k_min, k_max;
    int pattern_length;
    char* dna_kmer_to_num;
    std::vector<char> table;
    double L_avg;
    Config cfg;
    Logger& logger;
};
