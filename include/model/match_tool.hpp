#pragma once
#include <string>
#include <functional>
#include <vector>
#include <map>

/**
 * @brief calculate the number of common k-mers between two DNA sequences
 *
 * @param seq1 sequence 1
 * @param seq2 sequence 2
 * @param k length of k-mer
 * @return int number of common k-mers
 */
int calculate_kmer_matches(const std::string& seq1, const std::string& seq2, int k, bool use_one_to_one_matching, const std::string& sampling_method, char* dna_kmer_to_num, int pattern_length, std::vector<char>& table);