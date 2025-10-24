#include "utils/config.hpp"
#include <yaml-cpp/yaml.h>

Config load_config(const std::string& config_path) {
    YAML::Node config = YAML::LoadFile(config_path);
    Config cfg;
    cfg.datasets_directory = config["dataset"]["datasets_directory"].as<std::string>();
    cfg.use_one_to_one_matching = config["parameters"]["using_one_to_one_matching"].as<bool>();
    cfg.use_background_matches = config["parameters"]["using_background_matches"].as<bool>();
    cfg.use_all_points_for_fitting = config["parameters"]["using_all_points_for_fitting"].as<bool>();
    cfg.sampling_method = config["sampling_method"].as<std::string>();
    cfg.output_directory = config["output_directory"].as<std::string>();
    return cfg;
}