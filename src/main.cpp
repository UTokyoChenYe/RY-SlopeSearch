#include "utils/logger.hpp"
#include "utils/config.hpp"
#include "model/F_k_function.hpp"
#include "utils/evolution_model.hpp"

#include <seqan3/io/sequence_file/all.hpp>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    // ==== 解析命令行参数 ====
    std::string config_path;
    bool config_found = false;

    for (int i = 0; i < argc; ++i) {
        if (std::string(argv[i]) == "--config") {
            config_path = argv[i + 1];
            config_found = true;
            break;
        }
    }
    if (!config_found) {
        std::cerr << "Error: --config option is required" << std::endl;
        return 1;
    }

    // === 加载配置+初始化日志 ===
    Config cfg = load_config(config_path);
    Logger logger(cfg.output_directory);
    logger.info("Program started");
    std::cout << "Log directory: " << logger.get_log_directory() << std::endl;
    std::cout << "Log file: " << logger.get_log_filename() << std::endl;

    // === 记录 config 文件内容 ===
    std::ifstream config_file(config_path);
    if (config_file) {
        std::stringstream buffer;
        buffer << config_file.rdbuf();
        logger.log_config_yaml(buffer.str());
    }

    // === 遍历所有 .fasta 文件 ===
    for (const auto& entry : fs::directory_iterator(cfg.datasets_directory)) {
        if (entry.path().extension() == ".fasta") {
            logger.info("Processing file: " + entry.path().string());
            try {
                seqan3::sequence_file_input fasta(entry.path());
                std::vector<std::string> seqs;
                for (auto& record : fasta) {
                    seqs.emplace_back(std::string(
                        (record.sequence() | seqan3::views::to_char).begin(),
                        (record.sequence() | seqan3::views::to_char).end()
                    ));
                }

                if (seqs.size() >= 2) {
                    FKFunction fk(seqs[0], seqs[1], cfg, logger);
                    double p_hat = fk.calculate_p_hat();

                    // === Jukes-Cantor 距离计算 ===
                    float distance = estimate_jukes_cantor_distance(static_cast<float>(p_hat), logger);
                } else {
                    logger.warn("File " + entry.path().string() + " has fewer than 2 sequences.");
                }
            } catch (const std::exception& e) {
                logger.error("Error processing file " + entry.path().string() + ": " + e.what());
            }
        }
    }

    logger.info("Program finished");
    return 0;
}

