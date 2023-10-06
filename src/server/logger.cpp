#include "logger.hpp"
#include <ctime>

Logger::Logger(const std::string& filename) {
    log_file.open(filename, std::ios::out | std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

Logger::~Logger() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void Logger::Log(LogLevel level, const std::string& message) {
    if (!log_file.is_open()) {
        std::cerr << "Log file is not open." << std::endl;
        return;
    }

    // Get the log timestamp
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Get log level string
    std::string log_level_str;
    switch (level) {
        case LogLevel::INFO:
            log_level_str = "INFO";
            break;
        case LogLevel::WARNING:
            log_level_str = "WARNING";
            break;
        case LogLevel::ERROR:
            log_level_str = "ERROR";
            break;
    }

    // Write log messages to file
    log_file << "[" << timestamp << "] [" << log_level_str << "] " << message << std::endl;
}
