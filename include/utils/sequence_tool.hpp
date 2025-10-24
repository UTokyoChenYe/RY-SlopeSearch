#pragma once
#include <string>

/**
 * @brief 获取 DNA 序列的反向互补序列
 * 
 * @param seq 原始 DNA 序列（仅包含 A, T, C, G）
 * @return std::string 反向互补序列
 */
std::string reverse_complement(const std::string& seq);
