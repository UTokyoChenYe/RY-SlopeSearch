#pragma once
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

#include "model/KmerCount.hpp"

/**
 * @brief extract k-mers with specified pattern (prefix-aligned + rolling version)
 *
 * @param seq_list list of DNA sequences
 * @param k_min minimum k-mer length
 * @param k_max maximum k-mer length
 * @param dna_kmer_to_num mapping of DNA k-mer to number
 * @param pattern_length length of pattern
 * @param table lookup table for pattern
 * @return vector of k-mer lists
 */
std::vector<std::vector<size_t>> extract_kmers_with_pattern(
    const std::vector<std::string>& seq_list, 
    int k_min, 
    int k_max, 
    char* dna_kmer_to_num, 
    int pattern_length, 
    std::vector<char>& table);


/**
 * @brief calculate k-mer matches based on specified method
 *
 * @param kmer_counts1 vector of k-mer counts for sequence 1
 * @param kmer_counts2 vector of k-mer counts for sequence 2
 * @param use_one_to_one whether to use one-to-one matching
 * @return int number of k-mer matches
 */
 int calculate_kmer_matches(
    const std::vector<KmerCount> &kmer_counts1, 
    const std::vector<KmerCount> &kmer_counts2, 
    bool use_one_to_one);

int calculate_kmer_matches_parallel(
    const std::vector<KmerCount>& A,
    const std::vector<KmerCount>& B,
    bool use_one_to_one);