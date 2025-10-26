#pragma once
#include <string>

struct Config {
    std::string datasets_directory;
    bool use_one_to_one_matching;
    bool use_background_matches;
    bool use_openmp;
    bool draw_F_k_function;
    int draw_k_max;
    std::string sampling_method;
    std::string output_directory;
};

Config load_config(const std::string& config_path);