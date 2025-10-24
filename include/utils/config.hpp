#pragma once
#include <string>

struct Config {
    std::string datasets_directory;
    bool use_one_to_one_matching;
    bool use_background_matches;
    bool use_all_points_for_fitting;
    std::string sampling_method;
    std::string output_directory;
};

Config load_config(const std::string& config_path);