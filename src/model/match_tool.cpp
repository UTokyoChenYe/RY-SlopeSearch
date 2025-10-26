#include "model/match_tool.hpp"
#include "utils/sequence_tool.hpp"
#include "model/ry_sampling_word_sets.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <stdexcept>
#include <map>
#include <functional>  // for std::reference_wrapper

// mapping of sampling methods to their corresponding patterns
const std::map<std::string, std::reference_wrapper<const std::vector<std::string>>> kmer_sampling_methods = {
    {"basic_kmer_matches", std::cref(basic_patterns)},
    {"start_ry_matches", std::cref(ry_patterns)},
    {"start_rr_matches", std::cref(rr_patterns)},
    {"start_ry_4_6_matches", std::cref(ry_4_6_patterns)},
    {"start_ry_4_9_matches", std::cref(ry_4_9_patterns)},
    {"start_ry_4_push_matches", std::cref(ry_4_push_patterns)},
    {"start_ry_4_pull_matches", std::cref(ry_4_pull_patterns)},
};

// extract k-mers with specified pattern
std::vector<std::string> extract_kmers_with_pattern(const std::vector<std::string>& sequences, int k, const std::string& method) {
    std::set<std::string> patterns;
    int pattern_length = 0;

    auto it = kmer_sampling_methods.find(method);
    if (it != kmer_sampling_methods.end()) {
        const auto& vec = it->second.get();
        patterns = std::set<std::string>(vec.begin(), vec.end());
        if (!patterns.empty()) {
            pattern_length = patterns.begin()->size();
        } else {
            throw std::runtime_error("Pattern vector is empty for method: " + method);
        }
    } else {
        throw std::runtime_error("Unknown RY sampling method: " + method);
    }

    std::vector<std::string> result;

    for (const auto& seq : sequences) {
        std::string ry_seq = to_ry(seq);
        for (size_t i = 0; i + k <= seq.size() && i + pattern_length <= ry_seq.size(); ++i) {
            std::string ry_prefix = ry_seq.substr(i, pattern_length);
            if (patterns.count(ry_prefix)) {
                result.emplace_back(seq.substr(i, k));
            }
        }
    }

    return result;
}

// calculate k-mer matches based on specified method
int calculate_kmer_matches(const std::string& seq1_in, const std::string& seq2_in, int k, bool use_one_to_one, const std::string& method) {
    std::vector<std::string> seq1_list = { seq1_in };
    std::vector<std::string> seq2_list = { seq2_in };

    auto kmer_list1 = extract_kmers_with_pattern(seq1_list, k, method);
    auto kmer_list2 = extract_kmers_with_pattern(seq2_list, k, method);

    std::unordered_map<std::string, int> kmer_count1, kmer_count2;
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

