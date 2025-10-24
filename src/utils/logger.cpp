#include "utils/logger.hpp"
#include <iomanip>

Logger::Logger(const std::string& log_dir) {
    std::string filename = log_dir + "/RY_SlopeSearch.log";
    logfile.open(filename, std::ios::app);
}

Logger::~Logger() {
    if (logfile.is_open()) logfile.close();
}

std::string Logger::timestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* tm = std::localtime(&now);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm);
    return buf;
}

template<typename T>
void Logger::write(const std::string& level, const T& msg) {
    std::string logline = "[" + timestamp() + "] [" + level + "] " + msg;
    std::cout << logline << std::endl;
    if (logfile.is_open()) logfile << logline << std::endl;
}

template void Logger::write<std::string>(const std::string&, const std::string&);
