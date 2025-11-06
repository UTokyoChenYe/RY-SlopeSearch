#include "utils/sequence_tool.hpp"
#include <string>
#include <algorithm>

// std::string reverse_complement(const std::string& seq) {
//     std::string rc(seq);
//     std::reverse(rc.begin(), rc.end());
//     for (char& c : rc) {
//         switch (c) {
//             case 'A': c = 'T'; break;
//             case 'T': c = 'A'; break;
//             case 'C': c = 'G'; break;
//             case 'G': c = 'C'; break;
//             default: break;
//         }
//     }
//     return rc;
// }

std::string reverse_complement(const std::string& seq) {
    // Assume A = 0, C = 1, G = 2, T = 3
    std::string rc(seq);
    std::reverse(rc.begin(), rc.end());
    for (char& c : rc) {
      c = 3 - c;
    }
    return rc;
}