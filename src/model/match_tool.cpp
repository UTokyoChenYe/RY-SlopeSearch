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

// // extract k-mers with specified pattern
// std::vector<size_t> extract_kmers_with_pattern(const std::vector<std::string>& sequences, int k, const std::string& method) {
//     const auto& patterns_vec = get_patterns(method);
//     int pattern_length = get_pattern_length(method);
//     std::set<std::string> patterns(patterns_vec.begin(), patterns_vec.end());

//     std::vector<size_t> result;

//     // map the DNA k-mer to a number
//     char dna_kmer_to_num[128] = {0};
//     dna_kmer_to_num['A'] = 0;
//     dna_kmer_to_num['C'] = 1;
//     dna_kmer_to_num['G'] = 2;
//     dna_kmer_to_num['T'] = 3;
    
//     // patterns lookup table
//     size_t table_size = 1 << pattern_length; // 2^pattern_length
//     std::vector<char> table(table_size);
//     for (const auto& pattern : patterns) {
//         size_t pattern_num = 0;
//         for (auto j : pattern) {
//             pattern_num = pattern_num * 2 + (j == 'y');
//         }
//         table[pattern_num] = 1;
//     }

//     for (const auto& seq : sequences) {
//         size_t pattern_num = 0;
//         for (size_t i = 0; i + k <= seq.size(); ++i) {
//             pattern_num = pattern_num * 2 + (seq[i] == 'C' || seq[i] == 'T');
//             if (i < pattern_length - 1) continue; // skip the first pattern_length - 1 characters， warm up the cache
//             pattern_num = pattern_num & (table_size - 1); //choose
//             if (table[pattern_num]) {
//                 size_t dna_kmer_num = 0;
//                 for (size_t j = 0; j < k; ++j) {
//                     dna_kmer_num = dna_kmer_num * 4 + dna_kmer_to_num[seq[i - pattern_length + 1 + j]];
//                 }
//                 result.emplace_back(dna_kmer_num);
//             }
//         }
//     }
//     return result;
// }

// extract k-mers with specified pattern (prefix-aligned + rolling version)
std::vector<size_t> extract_kmers_with_pattern(const std::vector<std::string>& sequences, int k, char* dna_kmer_to_num, int pattern_length, std::vector<char>& table) {
    // const auto& patterns_vec = get_patterns(method);
    // int pattern_length = get_pattern_length(method);
    // std::set<std::string> patterns(patterns_vec.begin(), patterns_vec.end());

    std::vector<size_t> result;
    size_t table_size = 1ULL << pattern_length; // 2^pattern_length

    // // map the DNA k-mer to a number
    // char dna_kmer_to_num[128] = {0};
    // dna_kmer_to_num['A'] = 0;
    // dna_kmer_to_num['C'] = 1;
    // dna_kmer_to_num['G'] = 2;
    // dna_kmer_to_num['T'] = 3;

    // // pattern lookup table
    // size_t table_size = 1ULL << pattern_length; // 2^pattern_length
    // std::vector<char> table(table_size, 0);
    // for (const auto& pattern : patterns) {
    //     size_t pattern_num = 0;
    //     for (char j : pattern) {
    //         pattern_num = (pattern_num << 1) + (j == 'y');
    //     }
    //     table[pattern_num] = 1;
    // }

    // for each sequence
    // for (const auto& seq : sequences) {
    //     if (seq.size() < static_cast<size_t>(k)) continue;

    //     // initialize the first pattern window [0, pattern_length)
    //     size_t pattern_num = 0;
    //     for (int t = 0; t < pattern_length; ++t) {
    //         pattern_num = (pattern_num << 1) + (seq[t] == 'C' || seq[t] == 'T');
    //     }

    //     // check prefix window starting at i = 0
    //     if (table[pattern_num]) {
    //         size_t dna_kmer_num = 0;
    //         for (int j = 0; j < k; ++j)
    //             dna_kmer_num = dna_kmer_num * 4 + dna_kmer_to_num[seq[j]];
    //         result.emplace_back(dna_kmer_num);
    //     }

    //     // now roll forward: remove the leftmost bit, add new rightmost base
    //     size_t mask = table_size - 1;
    //     size_t highest_bit_value = 1ULL << (pattern_length - 1); // 100...0

    //     for (size_t i = 1; i + k <= seq.size(); ++i) {
    //         // remove the old leftmost bit and add new rightmost bit
    //         int old_bit = (seq[i - 1] == 'C' || seq[i - 1] == 'T');
    //         int new_bit = (seq[i + pattern_length - 1] == 'C' || seq[i + pattern_length - 1] == 'T');
    //         pattern_num = ((pattern_num - (old_bit * highest_bit_value)) << 1) + new_bit;
    //         pattern_num &= mask; // keep pattern_length bits only

    //         if (table[pattern_num]) {
    //             size_t dna_kmer_num = 0;
    //             for (size_t j = 0; j < static_cast<size_t>(k); ++j)
    //                 dna_kmer_num = dna_kmer_num * 4 + dna_kmer_to_num[seq[i + j]];
    //             result.emplace_back(dna_kmer_num);
    //         }
    //     }
    // }
    for (const auto& seq : sequences) {
        size_t pattern_num = 0;
        for (size_t i = 0; i + k - pattern_length < seq.size(); ++i) {
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
int calculate_kmer_matches(const std::string& seq1_in, const std::string& seq2_in, int k, bool use_one_to_one, const std::string& method, char* dna_kmer_to_num, int pattern_length, std::vector<char>& table) {
    // calculate sequence hash
    size_t ori_seq_hash1 = std::hash<std::string>()(seq1_in);
    std::string rc_seq1 = reverse_complement(seq1_in);
    size_t rc_seq_hash1 = std::hash<std::string>()(rc_seq1);
    size_t seq_hash1 = std::min(ori_seq_hash1, rc_seq_hash1); // use the smaller hash to reduce cache size

    size_t ori_seq_hash2 = std::hash<std::string>()(seq2_in);
    std::string rc_seq2 = reverse_complement(seq2_in);
    size_t rc_seq_hash2 = std::hash<std::string>()(rc_seq2);
    size_t seq_hash2 = std::min(ori_seq_hash2, rc_seq_hash2); // use the smaller hash to reduce cache size

    std::vector<std::string> seq1_list = { seq1_in, rc_seq1 };
    std::vector<std::string> seq2_list = { seq2_in, rc_seq2 };

    // calculate combined hash of two lists as key
    DnaKmerCache key1{ seq_hash1, k, method };
    DnaKmerCache key2{ seq_hash2, k, method };

    std::vector<size_t> kmer_list1, kmer_list2;

    // thread-safe query cache
    if (!g_dna_kmer_cache.try_get(key1, kmer_list1)) {
        kmer_list1 = extract_kmers_with_pattern(seq1_list, k, dna_kmer_to_num, pattern_length, table);
        g_dna_kmer_cache.set(key1, kmer_list1);
    }

    if (!g_dna_kmer_cache.try_get(key2, kmer_list2)) {
        kmer_list2 = extract_kmers_with_pattern(seq2_list, k, dna_kmer_to_num, pattern_length, table);
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

