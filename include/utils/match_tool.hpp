#pragma once
#include <string>

/**
 * @brief 计算两个 DNA 序列之间共有的 k-mer 数量。
 *
 * @param seq1 序列1
 * @param seq2 序列2
 * @param k k-mer 的长度
 * @return int 匹配到的共有 k-mer 数量
 */
int calculate_kmer_matches(const std::string& seq1, const std::string& seq2, int k);
