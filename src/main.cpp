#include "utils/logger.hpp"
#include "utils/config.hpp"
#include "model/F_k_function.hpp"
#include <seqan3/io/sequence_file/all.hpp>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    Config cfg = load_config("../configs/test_config.yaml");
    Logger logger(cfg.output_directory);
    logger.info("Program started");

    // 遍历所有 fasta 文件
    for (auto& entry : fs::directory_iterator(cfg.datasets_directory)) {
        if (entry.path().extension() == ".fasta") {
            seqan3::sequence_file_input fasta(entry.path());
            std::vector<std::string> seqs;
            for (auto& record : fasta)
                seqs.push_back(std::string(record.sequence() | seqan3::views::to_char));

            if (seqs.size() >= 2) {
                FKFunction fk(seqs[0], seqs[1], cfg, logger);
                double p_hat = fk.calculate_p_hat();
                logger.info("Estimated distance (Jukes-Cantor): " + std::to_string(-0.75 * std::log(1 - 4.0/3.0 * (1 - p_hat))));
            }
        }
    }

    logger.info("Program finished");
    return 0;
}
