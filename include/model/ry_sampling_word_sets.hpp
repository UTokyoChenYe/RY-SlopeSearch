#pragma once

#include <vector>
#include <string>

// === Basic ===
const std::vector<std::string> basic_patterns = {"r", "y"};

// === RY rule: starts with RY ===
const std::vector<std::string> ry_patterns = {
    "ry"
};

// === RR rule ===
const std::vector<std::string> rr_patterns = {
    "rr"
};

// === RY 4-6 ===
const std::vector<std::string> ry_4_6_patterns = {
    "rrrrry", "rryrry", "rryryy", "ryrrrr",
    "ryrrry", "ryryry", "ryyrrr", "ryyrry",
    "ryyryr", "ryyryy", "ryyyry", "ryyyyy",
    "yryrry", "yyyrrr", "yyyrry", "yyyyry"
};

// === RY 4-9 ===
const std::vector<std::string> ry_4_9_patterns = {
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
const std::vector<std::string> ry_4_push_patterns = {
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
const std::vector<std::string> ry_4_pull_patterns = {
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
