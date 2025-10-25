#include "utils/logger.hpp"
#include "utils/config.hpp"
#include "model/F_k_function.hpp"
#include "utils/evolution_model.hpp"
#include "utils/file_system.hpp"

#include <fstream>
#include <sstream>
#include <tuple>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>

int main(int argc, char** argv) {
    // === 解析命令行参数 ===
    std::string config_path;
    for (int i = 0; i < argc - 1; ++i) {
        if (std::string(argv[i]) == "--config") {
            config_path = argv[i + 1];
        }
    }
    if (config_path.empty()) {
        std::cerr << "Usage: " << argv[0] << " --config path_to_config.yaml\n";
        return 1;
    }

    // === 加载配置 ===
    Config cfg = load_config(config_path);
    Logger logger(cfg.output_directory);
    logger.info("Program started");
    logger.info("Config file loaded from: " + config_path);
    std::string output_dir = logger.get_log_directory();
    logger.info("Output directory: " + output_dir);
    logger.info("Output file: " + logger.get_log_filename());

    // === 记录 YAML config 内容到 log ===
    {
        std::ifstream config_file(config_path);
        if (config_file) {
            std::stringstream buffer;
            buffer << config_file.rdbuf();
            logger.log_config_yaml(buffer.str());
        }
    }

    // === 加载序列 ===
    logger.info("Loading sequences from directory: " + cfg.datasets_directory);
    auto [names, sequences] = load_sequences_from_multiple_files(cfg.datasets_directory);
    size_t N = sequences.size();

    if (N == 0) {
        logger.error("No sequences found in directory: " + cfg.datasets_directory);
        return 1;
    }

    logger.info("Loaded " + std::to_string(N) + " sequences");

    // === 计算距离矩阵 ===
    logger.info("Computing pairwise distances...");
    std::vector<std::vector<float>> distance_matrix(N, std::vector<float>(N, 0.0f));

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = i + 1; j < N; ++j) {  // 只计算上三角部分
            FKFunction fk(sequences[i], sequences[j], cfg, logger);
            double p_hat = fk.calculate_p_hat();
            float distance = estimate_jukes_cantor_distance(static_cast<float>(p_hat), logger);
    
            distance_matrix[i][j] = distance;
            distance_matrix[j][i] = distance;  // 对称赋值
        }
    }

    // === 保存 PHYLIP 文件 ===
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream time_ss;
    time_ss << std::put_time(std::localtime(&now_c), "%Y%m%d_%H%M%S");
    std::string timestamp = time_ss.str();

    std::string phylip_path = output_dir + "/distance_matrix_" + timestamp + ".phy";
    std::ofstream phy_out(phylip_path);
    if (!phy_out) {
        logger.error("Failed to write PHYLIP file to: " + phylip_path);
        return 1;
    }

    phy_out << N << "\n";
    for (size_t i = 0; i < N; ++i) {
        std::string name = names[i].substr(0, 10);
        name.resize(10, ' ');  // PHYLIP name field fixed width
        phy_out << name;

        for (size_t j = 0; j < N; ++j) {
            phy_out << std::fixed << std::setprecision(6) << " " << distance_matrix[i][j];
        }
        phy_out << "\n";
    }

    logger.info("PHYLIP file saved to: " + phylip_path);
    logger.info("Program finished successfully.");
    return 0;
}

