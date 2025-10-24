#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

class Logger {
public:
    explicit Logger(const std::string& log_dir);
    ~Logger();

    template<typename T>
    void info(const T& msg) { write("INFO", msg); }

    template<typename T>
    void warn(const T& msg) { write("WARN", msg); }

    template<typename T>
    void error(const T& msg) { write("ERROR", msg); }

private:
    std::ofstream logfile;
    std::string timestamp();
    template<typename T>
    void write(const std::string& level, const T& msg);
};
