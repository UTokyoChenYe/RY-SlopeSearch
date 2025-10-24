#include "utils/match_tool.hpp"
#include "utils/sequence_tool.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int calculate_kmer_matches(const std::string& seq1, const std::string& seq2, int k) {
    std::unordered_map<std::string, int> kmer_count1;
    std::unordered_map<std::string, int> kmer_count2;

    for (size_t i = 0; i + k <= seq1.size(); ++i) {
        std::string kmer = seq1.substr(i, k);
        ++kmer_count1[kmer];
    }

    for (size_t i = 0; i + k <= seq2.size(); ++i) {
        std::string kmer = seq2.substr(i, k);
        ++kmer_count2[kmer];
    }

    int matches = 0;
    for (const auto& [kmer, count1] : kmer_count1) {
        auto it = kmer_count2.find(kmer);
        if (it != kmer_count2.end()) {
            matches += std::min(count1, it->second);
        }
    }
    return matches;
}