#pragma once
#include <string>

/**
 * @brief get reverse complement of DNA sequence
 * 
 * @param seq original DNA sequence (only contains A, T, C, G)
 * @return std::string reverse complement sequence
 */
std::string reverse_complement(const std::string& seq);

/**
 * @brief convert DNA sequence to RY sequence
 * 
 * @param sequence original DNA sequence
 * @return std::string RY sequence
 */
std::string to_ry(const std::string& sequence);