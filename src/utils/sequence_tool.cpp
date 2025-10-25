#include "utils/sequence_tool.hpp"
#include <string>
#include <algorithm>

std::string reverse_complement(const std::string& seq) {
    std::string rc(seq);
    std::reverse(rc.begin(), rc.end());
    for (char& c : rc) {
        switch (c) {
            case 'A': c = 'T'; break;
            case 'T': c = 'A'; break;
            case 'C': c = 'G'; break;
            case 'G': c = 'C'; break;
            default: break;
        }
    }
    return rc;
}

std::string to_ry(const std::string& sequence) {
    std::string result = sequence;
    for (char& c : result) {
        if (c == 'A' || c == 'G') c = 'r';
        else if (c == 'C' || c == 'T') c = 'y';
    }
    return result;
}