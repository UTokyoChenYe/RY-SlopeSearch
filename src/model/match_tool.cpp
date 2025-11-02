#include "model/match_tool.hpp"
#include "utils/sequence_tool.hpp"
#include "model/ry_sampling_word_sets.hpp"
#include "utils/dna_kmer_cache.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

// global cache object
ThreadSafeDnaKmerCache g_dna_kmer_cache;

// extract k-mers with specified pattern
std::vector<size_t> extract_kmers_with_pattern(const std::vector<std::string>& sequences, int k, const std::string& method) {
    const auto& patterns_vec = get_patterns(method);
    int pattern_length = get_pattern_length(method);
    std::set<std::string> patterns(patterns_vec.begin(), patterns_vec.end());

    std::vector<size_t> result;

    // map the DNA k-mer to a number
    char dna_kmer_to_num[128] = {0};
    dna_kmer_to_num['A'] = 0;
    dna_kmer_to_num['C'] = 1;
    dna_kmer_to_num['G'] = 2;
    dna_kmer_to_num['T'] = 3;
    
    // patterns lookup table
    size_t table_size = 1 << pattern_length; // 2^pattern_length
    std::vector<char> table(table_size);
    for (const auto& pattern : patterns) {
        size_t pattern_num = 0;
        for (auto j : pattern) {
            pattern_num = pattern_num * 2 + (j == 'y');
        }
        table[pattern_num] = 1;
    }

    for (const auto& seq : sequences) {
        size_t pattern_num = 0;
        for (size_t i = 0; i + k <= seq.size(); ++i) {
            pattern_num = pattern_num * 2 + (seq[i] == 'C' || seq[i] == 'T');
            if (i < pattern_length - 1) continue;
            pattern_num = pattern_num & (table_size - 1);
            if (table[pattern_num]) {
                size_t dna_kmer_num = 0;
                for (size_t j = 0; j < k; ++j) {
                    dna_kmer_num = dna_kmer_num * 4 + dna_kmer_to_num[seq[i - pattern_length + 1 + j]];
                }
                result.emplace_back(dna_kmer_num);
            }
        }
    }
    return result;
}

// calculate k-mer matches based on specified method
int calculate_kmer_matches(const std::string& seq1_in, const std::string& seq2_in, int k, bool use_one_to_one, const std::string& method) {

    std::vector<std::string> seq1_list = { seq1_in };
    std::vector<std::string> seq2_list = { seq2_in };

    size_t seq_hash1 = std::hash<std::string>()(seq1_in);
    size_t seq_hash2 = std::hash<std::string>()(seq2_in);

    // calculate combined hash of two lists as key
    DnaKmerCache key1{ seq_hash1, k, method };
    DnaKmerCache key2{ seq_hash2, k, method };

    std::vector<size_t> kmer_list1, kmer_list2;

    // thread-safe query cache
    if (!g_dna_kmer_cache.try_get(key1, kmer_list1)) {
        kmer_list1 = extract_kmers_with_pattern(seq1_list, k, method);
        g_dna_kmer_cache.set(key1, kmer_list1);
    }

    if (!g_dna_kmer_cache.try_get(key2, kmer_list2)) {
        kmer_list2 = extract_kmers_with_pattern(seq2_list, k, method);
        g_dna_kmer_cache.set(key2, kmer_list2);
    }

    // calculate k-mer counts
    std::unordered_map<size_t, int> kmer_count1, kmer_count2;
    for (const auto& kmer : kmer_list1) ++kmer_count1[kmer];
    for (const auto& kmer : kmer_list2) ++kmer_count2[kmer];

    int matches = 0;
    for (const auto& [kmer, count1] : kmer_count1) {
        auto it = kmer_count2.find(kmer);
        if (it != kmer_count2.end()) {
            if (use_one_to_one) {
                matches += std::min(count1, it->second);
            } else {
                matches += count1 * it->second;
            }
        }
    }

    return matches;
}

