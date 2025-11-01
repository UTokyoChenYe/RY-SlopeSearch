#include "utils/logger.hpp"
#include "utils/config.hpp"
#include "model/F_k_function.hpp"
#include "utils/evolution_model.hpp"
#include "utils/file_system.hpp"
#include "utils/progress_bar.hpp"

#include <fstream>
#include <sstream>
#include <tuple>
#include <vector>
#include <string>
#include <set>
#include <iomanip>
#include <chrono>
#include <omp.h>

int main(int argc, char** argv) {
    // === parse command line arguments ===
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

    // === load config ===
    Config cfg = load_config(config_path);
    Logger logger(cfg.output_directory);
    logger.info("Program started");
    logger.info("Config file loaded from: " + config_path);
    std::string output_dir = logger.get_log_directory();
    logger.info("Output directory: " + output_dir);
    logger.info("Output file: " + logger.get_log_filename());

    // === start logging performance info ===
    std::string thread_log_path = output_dir + "/performance_info.log";
    std::ofstream thread_log(thread_log_path);
    if (!thread_log) {
        logger.error("Failed to open performance info log file: " + thread_log_path);
        return 1;
    }

    // use set to store unique thread IDs
    std::set<int> used_thread_ids;
    #pragma omp parallel
    {
        #pragma omp critical
        used_thread_ids.insert(omp_get_thread_num());
    }

    // === record YAML config content to log ===
    std::string config_log_path = output_dir + "/config_used.yaml"; 
    std::ifstream config_file(config_path);
    if (config_file) {
        std::ofstream config_log(config_log_path);  // or use better path control way
        if (config_log) {
            config_log << config_file.rdbuf();
            config_log.close();
        } else {
            logger.warn("Failed to open config_used.yaml for writing.");
        }
    } else {
        logger.warn("Failed to open config file: " + config_path);
    }

    // === load sequences ===
    logger.info("Loading sequences from directory: " + cfg.datasets_directory);
    auto [names, sequences] = load_sequences_from_multiple_files(cfg.datasets_directory);
    size_t N = sequences.size();

    if (N == 0) {
        logger.error("No sequences found in directory: " + cfg.datasets_directory);
        return 1;
    }

    logger.info("Loaded " + std::to_string(N) + " sequences");

    // === compute distance matrix ===
    logger.info("Computing pairwise distances...");
    
    std::vector<std::vector<float>> distance_matrix(N, std::vector<float>(N, 0.0f));

    ProgressBar progress_bar(static_cast<size_t>(N * (N - 1) / 2), "Computing pairwise distances", cfg.use_progress_bar);
    progress_bar.start();
    auto start_time = std::chrono::high_resolution_clock::now();  // start timing

    #pragma omp parallel for schedule(dynamic) collapse(1) if(cfg.use_openmp)  // OpenMP control
    for (size_t i = 0; i < N; ++i) {
        // === print thread info ===
        int thread_id = omp_get_thread_num();
        int thread_count = omp_get_num_threads();

        #pragma omp critical(logger_write_critical)
        {
            logger.info("OpenMP thread ID: " + std::to_string(thread_id) +
                        " / total threads: " + std::to_string(thread_count));
            used_thread_ids.insert(thread_id);
        }

        for (size_t j = i + 1; j < N; ++j) {  // only compute upper triangle part
            FKFunction fk(sequences[i], sequences[j], cfg, logger);
            double p_hat = fk.calculate_p_hat();

            // === draw Fk function ===
            if (cfg.draw_F_k_function) {
                std::string pair_name = "seq_" + names[i] + "_vs_seq_" + names[j];
                std::string fk_csv_path = output_dir + "/" + pair_name + "_Fk.csv";
                std::ofstream fk_out(fk_csv_path);
                if (!fk_out) {
                    logger.error("Failed to write Fk CSV file: " + fk_csv_path);
                    continue;
                } else {
                    fk_out << "k,Fk,log_Fk\n";
                    for (size_t idx = 0; idx < fk.k_vals.size(); ++idx) {
                        fk_out << fk.k_vals[idx] << "," << fk.Fk[idx] << "," << fk.Fk_log[idx] << "\n";
                    }
                    fk_out.close();
                    logger.info("Saved Fk curve to: " + fk_csv_path);
                }
            }

            // === compute evolutionary distance ===
            float distance = estimate_jukes_cantor_distance(static_cast<float>(p_hat), logger);
            
            #pragma omp critical(distance_matrix_write_critical) // when multiple threads write to 2D array, need to protect or avoid data conflict
            {
                distance_matrix[i][j] = distance;
                distance_matrix[j][i] = distance;  // symmetric assignment
            }
            progress_bar.increment();
        }
    }

    progress_bar.finish();

    auto end_time = std::chrono::high_resolution_clock::now();  // end timing
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    thread_log << "Distance matrix computation took "
           << duration.count() << " milliseconds\n";
    thread_log << "Unique OpenMP threads used: " << used_thread_ids.size() << "\n";
    thread_log << "Thread IDs: ";
    for (int tid : used_thread_ids) {
        thread_log << tid << " ";
    }
    thread_log << "\n";
    thread_log.close();  // close log

    // logger.info("Distance matrix computation took " + std::to_string(duration.count()) + " milliseconds");

    // === save PHYLIP file ===
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

