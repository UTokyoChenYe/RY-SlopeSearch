#include "model/match_tool.hpp"
#include "model/KmerCount.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>


// extract k-mers with specified pattern (prefix-aligned + rolling version)
std::vector<std::vector<size_t>> extract_kmers_with_pattern(
    const std::vector<std::string>& seq_list, 
    int k_min, 
    int k_max, 
    char* dna_kmer_to_num, 
    int pattern_length, 
    std::vector<char>& table) {

    // initialize result vector
    std::vector<std::vector<size_t>> result(k_max - k_min + 1);

    // calculate table size
    size_t table_size = 1ULL << pattern_length; // 2^pattern_length

    for (const auto& seq : seq_list) {
        size_t pattern_num = 0;
        for (size_t i = 0; i < seq.size(); ++i) {
            pattern_num = pattern_num * 2 + (seq[i] & 1);
            if (i < pattern_length - 1) continue;
            pattern_num = pattern_num & (table_size - 1);
            if (table[pattern_num]) {
                size_t dna_kmer_num = 0;
                for (size_t k = 1; k <= k_max; ++k) {
    		        if (i - pattern_length + k >= seq.size()) break;
                    dna_kmer_num = dna_kmer_num * 4 + seq[i - pattern_length + k];
                    if (k >= k_min) {
                        result[k - k_min].emplace_back(dna_kmer_num);
                    }
                }
            }
        }
    }
    return result;
}


// calculate k-mer matches based on specified method
int calculate_kmer_matches(
    const std::vector<KmerCount> &kmer_counts1, 
    const std::vector<KmerCount> &kmer_counts2, 
    bool use_one_to_one) {

    int matches = 0;
    size_t pos1 = 0;
    size_t pos2 = 0;

    while (pos1 < kmer_counts1.size() && pos2 < kmer_counts2.size()) {
        size_t kmer1 = kmer_counts1[pos1].kmer;
        int count1 = kmer_counts1[pos1].count;
        size_t kmer2 = kmer_counts2[pos2].kmer;
        int count2 = kmer_counts2[pos2].count;

        if (kmer1 == kmer2) {
            if (use_one_to_one) {
                matches += std::min(count1, count2);
            } else {
                matches += count1 * count2;
            }
        }

        if (kmer1 <= kmer2) ++pos1;
        if (kmer2 <= kmer1) ++pos2;
    }
    // for (const auto& [kmer, count1] : kmer_count1) {
    //     auto it = kmer_count2.find(kmer);
    //     if (it != kmer_count2.end()) {
    //         if (use_one_to_one) {
    //             matches += std::min(count1, it->second);
    //         } else {
    //             matches += count1 * it->second;
    //         }
    //     }
    // }
    return matches;
}

