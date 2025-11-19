#include "utils/sequence_tool.hpp"
#include <string>
#include <algorithm>

std::string reverse_complement(const std::string& seq) {
    // Assume A = 0, C = 1, G = 2, T = 3
    std::string rc(seq);
    std::reverse(rc.begin(), rc.end());
    for (char& c : rc) {
      c = 3 - c;
    }
    return rc;
}