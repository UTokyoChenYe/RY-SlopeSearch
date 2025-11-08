#include "model/match_tool.hpp"
#include "model/KmerCount.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <omp.h>

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


//calculate k-mer matches based on specified method
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
    return matches;
}


struct Range {
    uint64_t start;
    uint64_t end;
};

int calculate_kmer_matches_parallel(
    const std::vector<KmerCount>& A,
    const std::vector<KmerCount>& B,
    bool use_one_to_one)
{
    size_t n1 = A.size();
    size_t n2 = B.size();
    int num_threads = omp_get_max_threads();

    // === 1. 计算范围分割 ===
    std::vector<Range> ranges;
    ranges.reserve(num_threads);
    uint64_t min_k = std::min(A.front().kmer, B.front().kmer);
    uint64_t max_k = std::max(A.back().kmer, B.back().kmer);
    uint64_t step = (max_k - min_k + num_threads - 1) / num_threads;
    for (int t = 0; t < num_threads; ++t) {
        ranges.push_back({min_k + t * step, min_k + (t + 1) * step});
    }

    // === 2. 每个线程处理一个区间 ===
    std::vector<int> thread_matches(num_threads, 0);

    #pragma omp parallel for num_threads(num_threads) schedule(static)
    for (int t = 0; t < num_threads; ++t) {
        auto [start, end] = ranges[t];
        // 二分查找起始位置（保证线程边界准确）
        auto it1 = std::lower_bound(A.begin(), A.end(), start,
            [](const KmerCount& x, uint64_t val){ return x.kmer < val; });
        auto it2 = std::lower_bound(B.begin(), B.end(), start,
            [](const KmerCount& x, uint64_t val){ return x.kmer < val; });

        auto end1 = std::lower_bound(A.begin(), A.end(), end,
            [](const KmerCount& x, uint64_t val){ return x.kmer < val; });
        auto end2 = std::lower_bound(B.begin(), B.end(), end,
            [](const KmerCount& x, uint64_t val){ return x.kmer < val; });

        size_t i = it1 - A.begin();
        size_t j = it2 - B.begin();
        size_t e1 = end1 - A.begin();
        size_t e2 = end2 - B.begin();

        int local_matches = 0;

        while (i < e1 && j < e2) {
            uint64_t k1 = A[i].kmer;
            uint64_t k2 = B[j].kmer;
            if (k1 == k2) {
                local_matches += use_one_to_one
                    ? std::min(A[i].count, B[j].count)
                    : A[i].count * B[j].count;
            }
            i += (k1 <= k2);
            j += (k2 <= k1);
        }
        thread_matches[t] = local_matches;
    }

    // === 3. 汇总 ===
    int total_matches = 0;
    for (auto v : thread_matches) total_matches += v;
    return total_matches;
}