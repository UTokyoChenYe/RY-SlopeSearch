#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <map>
#include <functional>  // for std::reference_wrapper

// === Basic ===
// inline to avoid multiple definitions
inline const std::vector<std::string> basic_patterns = {"r", "y"};

// === RY rule: starts with RY ===
inline const std::vector<std::string> ry_patterns = {
    "ry"
};

// === RR rule ===
inline const std::vector<std::string> rr_patterns = {
    "rr"
};

// === RY 4-6 ===
inline const std::vector<std::string> ry_4_6_patterns = {
    "rrrrry", "rryrry", "rryryy", "ryrrrr",
    "ryrrry", "ryryry", "ryyrrr", "ryyrry",
    "ryyryr", "ryyryy", "ryyyry", "ryyyyy",
    "yryrry", "yyyrrr", "yyyrry", "yyyyry"
};

// === RY 4-9 ===
inline const std::vector<std::string> ry_4_9_patterns = {
    "rrrrrrrry", "rrrrrryry", "rrrrryrrr", "rrrrryrry",
    "rrrrryyrr", "rrrrryyry", "rrrrryyyr", "rrrrryyyy",
    "rrryryrrr", "rrryryrry", "rrryryyrr", "rrryryyry",
    "rrryryyyr", "rrryryyyy", "rryrrrrrr", "rryrrrrry",
    "rryrrryry", "rryrryrrr", "rryrryrry", "rryrryryr",
    "rryrryyrr", "rryrryyry", "rryrryyyy", "rryryryry",
    "rryyryrrr", "rryyryrry", "rryyryyry", "rryyryyyy",
    "rryyyyrrr", "rryyyyrry", "rryyyyryr", "rryyyyyrr",
    "ryrrrryrr", "ryrrrryry", "ryrrrryyr", "ryrrrryyy",
    "ryrrryrrr", "ryrrryrry", "ryrrryyrr", "ryrrryyry",
    "ryrrryyyr", "ryrrryyyy", "ryrryryyr", "ryrryryyy",
    "ryrryyyrr", "ryrryyyry", "ryryryrrr", "ryryryrry",
    "ryryryyrr", "ryryryyry", "ryryryyyr", "ryryryyyy",
    "ryyrrrrrr", "ryyrrrrry", "ryyrrrryr", "ryyrrryrr",
    "ryyrrryry", "ryyrrryyr", "ryyrrryyy", "ryyrryrrr",
    "ryyrryrry", "ryyrryryr", "ryyrryyrr", "ryyrryyry",
    "ryyrryyyr", "ryyrryyyy", "ryyryryrr", "ryyryryry",
    "ryyryryyr", "ryyryryyy", "ryyryyrrr", "ryyryyrry",
    "ryyryyyrr", "ryyryyyry", "ryyyryrrr", "ryyyryrry",
    "ryyyryyrr", "ryyyryyry", "ryyyryyyr", "ryyyryyyy",
    "ryyyyryyr", "ryyyyryyy", "ryyyyyryr", "ryyyyyyrr",
    "ryyyyyyyy", "yryrrrrrr", "yryrrrrry", "yryrrryry",
    "yryrryrrr", "yryrryrry", "yryrryryr", "yryrryyrr",
    "yryrryyry", "yryrryyyy", "yryyryrrr", "yryyryrry",
    "yryyryyry", "yryyryyyy", "yryyyyrrr", "yryyyyrry",
    "yryyyyryr", "yryyyyyrr", "yyrrrryyr", "yyrrrryyy",
    "yyrryryyr", "yyrryryyy", "yyyrrrrrr", "yyyrrrrry",
    "yyyrrrryr", "yyyrrryrr", "yyyrrryry", "yyyrrryyr",
    "yyyrrryyy", "yyyrryrrr", "yyyrryrry", "yyyrryryr",
    "yyyrryyrr", "yyyrryyry", "yyyrryyyr", "yyyrryyyy",
    "yyyryryrr", "yyyryryry", "yyyryryyr", "yyyryryyy",
    "yyyyyryyr", "yyyyyryyy", "yyyyyyryr", "yyyyyyyrr"
};

// === RY 4-push ===
inline const std::vector<std::string> ry_4_push_patterns = {
    "rrrrryrrr", "rrrrryrry", "rrrrryryr", "rrrrryryy",
    "rrrrryyrr", "rrrrryyry", "rrrrryyyy", "rrrryyyrr",
    "rrrryyyry", "rryrrrrry", "rryrryrrr", "rryrryrry",
    "rryrryryr", "rryryrrrr", "rryryrrry", "rryryrryr",
    "rryryrryy", "rryryryry", "rryryyrrr", "rryryyrry",
    "rryryyryr", "rryryyryy", "rryryyyrr", "rryryyyry",
    "rryryyyyr", "rryryyyyy", "rryyyyrrr", "rryyyyrry",
    "rryyyyryr", "rryyyyryy", "ryrrrrrrr", "ryrrrrrry",
    "ryrrrryrr", "ryrrrryry", "ryrrrryyr", "ryrrryrrr",
    "ryrrryrry", "ryrrryryr", "ryrrryryy", "ryrrryyrr",
    "ryrrryyry", "ryrrryyyy", "ryrryyrrr", "ryrryyrry",
    "ryrryyryr", "ryrryyryy", "ryrryyyrr", "ryrryyyry",
    "ryrryyyyy", "ryryryrrr", "ryryryrry", "ryryryyrr",
    "ryryryyry", "ryryryyyy", "ryyrrrrrr", "ryyrrrrry",
    "ryyrrryry", "ryyrryrrr", "ryyrryrry", "ryyrryryr",
    "ryyrryryy", "ryyrryyrr", "ryyrryyry", "ryyrryyyy",
    "ryyryrrrr", "ryyryrrry", "ryyryrryy", "ryyryryry",
    "ryyryyrrr", "ryyryyrry", "ryyryyryr", "ryyryyryy",
    "ryyryyyrr", "ryyryyyry", "ryyryyyyy", "ryyyyyrrr",
    "ryyyyyrry", "ryyyyyryr", "ryyyyyryy", "ryyyyyyrr",
    "ryyyyyyry", "yrrrryyyy", "yrrryyyrr", "yrrryyyry",
    "yryryyyrr", "yryryyyry", "yyrrrryrr", "yyrrrryry",
    "yyrrrryyr", "yyrrryrrr", "yyrrryrry", "yyrrryyrr",
    "yyrrryyry", "yyrrryyyy", "yyrryyyrr", "yyrryyyry",
    "yyryrryrr", "yyryrryry", "yyryryrrr", "yyryryrry",
    "yyryryyrr", "yyryryyry", "yyryryyyy", "yyryyyyrr",
    "yyryyyyry", "yyyrrrrrr", "yyyrrrrry", "yyyrrryry",
    "yyyrryrrr", "yyyrryrry", "yyyrryryr", "yyyrryryy",
    "yyyrryyrr", "yyyrryyry", "yyyrryyyy", "yyyryrrrr",
    "yyyryrrry", "yyyryrryy", "yyyryryry", "yyyryyrrr",
    "yyyryyrry", "yyyryyryr", "yyyryyryy", "yyyryyyrr",
    "yyyryyyry", "yyyryyyyy", "yyyyyyyrr", "yyyyyyyry"
};

// === RY 4-pull ===
inline const std::vector<std::string> ry_4_pull_patterns = {
    "rrrrrrrrr", "rrrrrryrr", "rrrrrryry", "rrrrrryyr",
    "rrrrrryyy", "rrryryrrr", "rrryryyrr", "rrryryyry",
    "rrryryyyr", "rrryryyyy", "rryrrrrrr", "rryrrryrr",
    "rryrrryry", "rryrrryyr", "rryrryrrr", "rryrryrry",
    "rryrryryr", "rryrryyrr", "rryrryyry", "rryrryyyr",
    "rryrryyyy", "rryryryyr", "rryryryyy", "rryyryrrr",
    "rryyryyrr", "rryyryyry", "rryyryyyr", "rryyryyyy",
    "rryyyryrr", "rryyyyrrr", "rryyyyyrr", "rryyyyyyr",
    "ryrrrryrr", "ryrrrryry", "ryrrrryyr", "ryrrrryyy",
    "ryrrryyyr", "ryrrryyyy", "ryrryryyr", "ryrryryyy",
    "ryryrryrr", "ryryrryry", "ryryrryyr", "ryryrryyy",
    "ryryryrrr", "ryryryrry", "ryryryryr", "ryyrrrrrr",
    "ryyrrrrry", "ryyrrryrr", "ryyrrryry", "ryyrrryyr",
    "ryyrrryyy", "ryyrryrrr", "ryyrryrry", "ryyrryryr",
    "ryyrryyrr", "ryyrryyry", "ryyrryyyr", "ryyrryyyy",
    "ryyryryrr", "ryyryryry", "ryyryryyr", "ryyryryyy",
    "ryyyrrrrr", "ryyyrrrry", "ryyyrryrr", "ryyyrryry",
    "ryyyrryyr", "ryyyrryyy", "ryyyryryr", "ryyyryyrr",
    "ryyyryyry", "ryyyryyyr", "ryyyryyyy", "ryyyyryrr",
    "ryyyyryry", "ryyyyryyr", "ryyyyryyy", "ryyyyyyyr",
    "yrrrrryrr", "yrrrrryry", "yrrrrryyr", "yrrrrryyy",
    "yrryryrrr", "yryrrrrrr", "yryrrryrr", "yryrrryry",
    "yryrrryyr", "yryryryyr", "yryryryyy", "yryyryrrr",
    "yryyryyrr", "yryyryyry", "yryyryyyr", "yryyryyyy",
    "yryyyryrr", "yryyyyrrr", "yryyyyyrr", "yryyyyyyr",
    "yyrrrryrr", "yyrrrryry", "yyrrrryyr", "yyrrrryyy",
    "yyrryryyr", "yyrryryyy", "yyryrryrr", "yyryrryry",
    "yyryrryyr", "yyryrryyy", "yyryryrrr", "yyyrrryrr",
    "yyyrrryry", "yyyrrryyr", "yyyrrryyy", "yyyryryyr",
    "yyyryryyy", "yyyyrrrrr", "yyyyrryrr", "yyyyrryry",
    "yyyyrryyr", "yyyyrryyy", "yyyyyryrr", "yyyyyryry",
    "yyyyyryyr", "yyyyyryyy", "yyyyyyyyr", "yyyyyyyyy"
};

// === RY 16 ===
inline const std::vector<std::string> ry_16_patterns = {
"rryryrrrrrr", "rryryrrrryr", "rryryrrryrr", "rryryrryrrr", "rryryrryrry", "rryryryrrrr", "rryryryrryr", "rryryryryrr", "rryryryyrrr", "rryryryyrry",
"rryryyrrrrr", "rryryyrrryr", "rryryyrryrr", "rryryyryrry", "rryryyyrrrr", "rryryyyrryr", "rryryyyryrr", "rryryyyyrrr", "rryryyyyrry", "rryyrrrrrrr",
"rryyrrrrrry", "rryyrrrrryr", "rryyrrrryrr", "rryyrrryrrr", "rryyrrryrry", "rryyrryrrrr", "rryyrryrrry", "rryyrryrryr", "rryyryrrrrr", "rryyryrrrry",
"rryyryrrryr", "rryyryrryrr", "rryyryryrrr", "rryyryryrry", "rryyryryyrr", "rryyryyrrrr", "rryyryyrrry", "rryyryyrryr", "rryyryyyrrr", "rryyryyyrry",
"rryyryyyyrr", "rryyyrrrrrr", "rryyyrrrrry", "rryyyrrrryr", "rryyyrrryrr", "rryyyrryrrr", "rryyyrryrry", "rryyyryrrrr", "rryyyryrrry", "rryyyryrryr",
"rryyyryyrrr", "rryyyryyrry", "rryyyryyyrr", "rryyyyrrrrr", "rryyyyrrrry", "rryyyyrrryr", "rryyyyrryrr", "rryyyyryrrr", "rryyyyryrry", "rryyyyryyrr",
"rryyyyyrrrr", "rryyyyyrrry", "rryyyyyrryr", "rryyyyyryrr", "rryyyyyyrry", "ryryryryyrr", "ryryryyyrrr", "ryryryyyrry", "ryryryyyyrr", "ryryyryrrrr",
"ryryyryrrry", "ryryyryryrr", "ryryyryyrrr", "ryryyryyrry", "ryryyryyyrr", "ryryyyryyrr", "ryryyyyryrr", "ryryyyyyrrr", "ryryyyyyrry", "ryyryyryrrr",
"ryyryyryrry", "ryyryyyryrr", "ryyyryryrrr", "ryyyryryrry", "ryyyryryyrr", "ryyyryyryrr", "ryyyyryryrr", "ryyyyyryyrr", "ryyyyyyrrrr", "ryyyyyyrrry",
"ryyyyyyryrr", "ryyyyyyyrrr", "ryyyyyyyrry", "ryyyyyyyyrr", "yryryryryrr", "yryryyryrry", "yryryyyryrr", "yryyryryyrr", "yryyryyyyrr", "yryyyryyyrr",
"yryyyyryyrr", "yryyyyyryrr", "yryyyyyyrry", "yyryryryrrr", "yyryryryrry", "yyryryryyrr", "yyryryyyrrr", "yyryryyyrry", "yyryryyyyrr", "yyryyryryrr",
"yyryyryyrrr", "yyryyryyrry", "yyryyryyyrr", "yyryyyryyrr", "yyryyyyryrr", "yyryyyyyrrr", "yyryyyyyrry", "yyyryyyryrr", "yyyryyyyrrr", "yyyryyyyrry",
"yyyyryryyrr", "yyyyryyryrr", "yyyyryyyrrr", "yyyyryyyrry", "yyyyyryryrr", "yyyyyyryyrr", "yyyyyyyryrr", "yyyyyyyyyrr"
};

// === RY 32 ===
inline const std::vector<std::string> ry_32_patterns = {
"rrrrrrrryyyr", "rrrrrrrryyyy", "rrrrrryrryyy", "rrrrrryryyyr", "rrrrryrrryyy", "rrrrryryyyyr", "rrrrryryyyyy", "rrrrryyryyyr", "rrrrryyryyyy", "rrrryryrryyy",
"rrrryryryyyr", "rrrryryryyyy", "rrrryryyryyy", "rrrryyrryyyr", "rrrryyrryyyy", "rrrryyryryyy", "rrryrrrryyyr", "rrryrrrryyyy", "rrryrryryyyr", "rrryrryryyyy",
"rrryyrrrryyy", "rrryyrrryyyr", "rrryyryrryyy", "rrryyryyryyy", "rryrrrrrryyy", "rryrrrrryyyr", "rryrrryryyyr", "rryrrryryyyy", "rryrrryyryyy", "rryrryrrryyy",
"rryrryrryyyr", "rryrryrryyyy", "rryrryyrryyy", "rryrryyryyyr", "rryrryyryyyy", "rryryrrrryyy", "rryryrrryyyr", "rryryrrryyyy", "rryryrryryyy", "rryryryrryyy",
"rryryryryyyr", "rryryryryyyy", "rryryyrrryyy", "rryryyrryyyr", "rryryyrryyyy", "rryyrrrrryyy", "rryyrrryryyy", "rryyrrryyyyr", "rryyrrryyyyy", "rryyrryryyyr",
"rryyrryryyyy", "rryyryryryyy", "rryyryyrryyy", "ryrrrrrrryyy", "ryrrrrryyyyr", "ryrrrrryyyyy", "ryrrrryrryyy", "ryrrrryryyyr", "ryrrrryryyyy", "ryrrrryyryyy",
"ryrrryrrryyy", "ryrrryrryyyr", "ryrrryrryyyy", "ryrrryryryyy", "ryrrryyrryyy", "ryrryrrrryyy", "ryrryrryryyy", "ryrryryrryyy", "ryrryryryyyr", "ryrryryryyyy",
"ryrryryyryyy", "ryrryyryryyy", "ryryrrryryyy", "ryryrryrryyy", "ryryrryyryyy", "ryryryrrryyy", "ryryryryryyy", "ryryryyrryyy", "ryryryyryyyr", "ryryryyryyyy",
"ryryyrrrryyy", "ryryyrryryyy", "ryryyryrryyy", "ryryyryryyyr", "ryryyryryyyy", "ryryyryyryyy", "ryyrrrrrryyy", "ryyrrrryryyy", "ryyrrryrryyy", "ryyrrryyryyy",
"ryyrryrrryyy", "ryyrryrryyyr", "ryyrryrryyyy", "ryyrryryryyy", "ryyrryyrryyy", "ryyrryyryyyr", "ryyrryyryyyy", "ryyryrrrryyy", "ryyryrrryyyr", "ryyryrrryyyy",
"ryyryrryryyy", "ryyryryrryyy", "ryyryryyryyy", "ryyryyrrryyy", "ryyryyryryyy", "yrrrrryrryyy", "yrrrrryryyyr", "yrrrryrrryyy", "yrrryryrryyy", "yrrryryyryyy",
"yrrryyryryyy", "yrryyrrrryyy", "yrryyrrryyyr", "yrryyryrryyy", "yrryyryyryyy", "yryrrrrrryyy", "yryrrrrryyyr", "yryrrryyryyy", "yryrryrrryyy", "yryrryyrryyy",
"yryryrrrryyy", "yryryrryryyy", "yryryryrryyy", "yryryyrrryyy", "yryyrrrrryyy", "yryyrrryryyy", "yryyryryryyy", "yryyryyrryyy"
};

// === RY 64 ===
inline const std::vector<std::string> ry_64_patterns = {
"rrrrrrrrrryyy", "rrrrrrrryryyy", "rrrrrryrryyyy", "rrrrrryryryyy", "rrrrrryyryyyy", "rrrrryrrrryyy", "rrrrryyrrryyy", "rrrrryyrryyyy", "rrrrryyryryyy", "rrrryrrrrryyy",
"rrrryrrryryyy", "rrrryrryrryyy", "rrrryrryryyyy", "rrrryryrrryyy", "rrrryryyryyyy", "rrrryyrrrryyy", "rrrryyrryryyy", "rrrryyryrryyy", "rrryrrryrryyy", "rrryrrryyryyy",
"rrryrryryryyy", "rrryrryyrryyy", "rrryrryyryyyy", "rrryryrryryyy", "rrryryryrryyy", "rrryryryryyyy", "rrryryryyryyy", "rrryyryryryyy", "rryrrrryryyyy", "rryrrrryyryyy",
"rryrrryryryyy", "rryrryrrrryyy", "rryrryrrryyyy", "rryryrrrrryyy", "rryryrrrryyyy", "rryryrrryryyy", "rryryrryrryyy", "rryryyrrryyyy", "rryryyrryyyyy", "rryryyryrryyy",
"rryryyryryyyy", "rryryyryyryyy", "rryyrrrryryyy", "rryyrrryryyyy", "rryyrrryyryyy", "rryyrryrrryyy", "rryyrryrryyyy", "rryyryrrrryyy", "rryyryryrryyy", "rryyryryyryyy",
"ryrrrrrrrryyy", "ryrrrrrrryyyy", "ryrrrrrryryyy", "ryrrrrryrryyy", "ryrrrrryryyyy", "ryrrrrryyryyy", "ryrrrryrryyyy", "ryrrrryryryyy", "ryrrrryyrryyy", "ryrrryrrrryyy",
"ryrrryrrryyyy", "ryrrryrryryyy", "ryrrryryrryyy", "ryrrryyrrryyy", "ryrrryyrryyyy", "ryrrryyryryyy", "ryrryrrrrryyy", "ryrryrrryryyy", "ryrryrryryyyy", "ryrryrryyryyy",
"ryrryryrrryyy", "ryrryryrryyyy", "ryrryryryryyy", "ryrryryyryyyy", "ryrryyrrrryyy", "ryrryyrrryyyy", "ryrryyrryryyy", "ryrryyryrryyy", "ryrryyryryyyy", "ryrryyryyryyy",
"ryryrrrrrryyy", "ryryrrrryryyy", "ryryrrryrryyy", "ryryrrryyryyy", "ryryrryrrryyy", "ryryrryryryyy", "ryryrryyrryyy", "ryryryrrryyyy", "ryryryryrryyy", "ryryryryryyyy",
"ryryryryyryyy", "ryryryyrrryyy", "ryryryyrryyyy", "ryryryyryryyy", "ryryyrrrryyyy", "ryryyrrryryyy", "ryryyrryrryyy", "ryryyrryyryyy", "ryryyryrrryyy", "ryryyryyrryyy",
"ryyrrrrrrryyy", "ryyrrrrrryyyy", "ryyrrrrryryyy", "ryyrrrrryyyyy", "ryyrrrryyryyy", "ryyrrryrrryyy", "ryyrrryrryyyy", "ryyrrryryryyy", "ryyrrryyrryyy", "ryyrryrrrryyy",
"ryyrryrryryyy", "ryyrryryrryyy", "ryyrryryryyyy", "ryyrryryyryyy", "ryyrryyrryyyy", "ryyrryyryryyy", "ryyryrrrrryyy", "ryyryrrryryyy", "ryyryrryrryyy", "ryyryrryryyyy",
"ryyryrryyryyy", "ryyryryrrryyy", "ryyryryryryyy", "ryyryyrrrryyy", "ryyryyrryryyy", "ryyryyryrryyy", "ryyryyryryyyy", "ryyryyryyryyy" 
};

// === RY 128 ===
inline const std::vector<std::string> ry_128_patterns = {
"rrrrrrryyryy", "rryrryyyyyyy", "rrrrrryyyryy", "rryrrryyyyyy", "rrrrryryyryy", "rryrryryyyyy", "rrrrryyryryy", "rryryrryyyyy", "rrrrryyyyryy", "rryrrrryyyyy",
"rrrryryyyryy", "rryrrryryyyy", "rrrryyyrryyy", "rrryyrrryyyy", "rrrryyyryryy", "rryryrrryyyy", "rrryrrryyryy", "rryrryyyryyy", "rrryryryyryy", "rryrryryryyy",
"rrryryyrryyy", "rrryyrryryyy", "rrryryyryryy", "rryryrryryyy", "rrryyrryyryy", "rryrryyrryyy", "rrryyryryryy", "rryryryrryyy", "rryrrrryyryy", "rryrryyyyryy",
"rryrryyryryy", "rryryrryyryy"
};


// mapping of sampling methods to their corresponding patterns
// inline to avoid multiple definitions
inline const std::map<std::string, std::reference_wrapper<const std::vector<std::string>>> kmer_sampling_methods = {
    {"basic_kmer_matches", std::cref(basic_patterns)},
    {"start_ry_matches", std::cref(ry_patterns)},
    {"start_rr_matches", std::cref(rr_patterns)},
    {"start_ry_4_6_matches", std::cref(ry_4_6_patterns)},
    {"start_ry_4_9_matches", std::cref(ry_4_9_patterns)},
    {"start_ry_4_push_matches", std::cref(ry_4_push_patterns)},
    {"start_ry_4_pull_matches", std::cref(ry_4_pull_patterns)},
    {"start_ry_16_matches", std::cref(ry_16_patterns)},
    {"start_ry_32_matches", std::cref(ry_32_patterns)},
    {"start_ry_64_matches", std::cref(ry_64_patterns)},
    {"start_ry_128_matches", std::cref(ry_128_patterns)},
};

// get the pattern set of the specified sampling method
inline const std::vector<std::string>& get_patterns(const std::string& method) {
    auto it = kmer_sampling_methods.find(method);
    if (it == kmer_sampling_methods.end())
        throw std::runtime_error("Unknown RY sampling method: " + method);
    return it->second.get();
}

// get the length of the pattern of the specified sampling method
inline int get_pattern_length(const std::string& method) {
    const auto& patterns = get_patterns(method);
    if (patterns.empty())
        throw std::runtime_error("Pattern vector is empty for method: " + method);
    return static_cast<int>(patterns.front().size());
}

extern const std::map<std::string, std::reference_wrapper<const std::vector<std::string>>> kmer_sampling_methods;