#include "utils/logger.hpp"

Logger::Logger(const std::string& log_root_dir) {
    namespace fs = std::filesystem;

    // 生成基于时间戳的子目录
    std::string time_str = timestamp(true);
    log_directory = log_root_dir + "/" + time_str;

    // 创建目录
    fs::create_directories(log_directory);

    // 构建日志文件路径
    log_filename = time_str + ".log";
    std::string log_path = log_directory + "/" + log_filename;

    // 打开日志文件
    logfile.open(log_path, std::ios::app);
}

Logger::~Logger() {
    if (logfile.is_open()) {
        logfile.close();
    }
}

std::string Logger::timestamp(bool for_path) {
    std::time_t now = std::time(nullptr);
    std::tm* tm = std::localtime(&now);
    char buf[64];

    if (for_path) {
        // 用于路径：2025-10-25_20-45-33
        std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", tm);
    } else {
        // 用于日志行：2025-10-25 20:45:33
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm);
    }

    return std::string(buf);
}

void Logger::log_config_yaml(const std::string& config_yaml) {
    std::ostringstream oss;
    oss << "[" << timestamp(false) << "] [CONFIG]" << std::endl;
    oss << config_yaml << std::endl;

    std::cout << oss.str();
    if (logfile.is_open()) {
        logfile << oss.str() << std::endl;
    }
}
