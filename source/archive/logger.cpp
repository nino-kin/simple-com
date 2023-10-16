#include <fstream>
#include <iostream>
#include <ctime>

#include "spdlog/spdlog.h"

#include "logger.hpp"

Logger::Logger(const std::string& filePath) : filePath_(filePath) {}

Logger::~Logger() {}

void Logger::log(LogLevel level, const std::string& message) {
    std::ofstream logFile(filePath_, std::ios::app);

    if (!logFile.is_open()) {
        spdlog::error("Error opening log file.");
        return;
    }

    // Get the log timestamp
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    std::string log_level_str;
    switch (level) {
        case LogLevel::INFO:
            log_level_str = "[INFO]";
            break;
        case LogLevel::WARNING:
            log_level_str = "[WARNING]";
            break;
        case LogLevel::ERROR:
            log_level_str = "[ERROR]";
            break;
        default:
            log_level_str = "[UNKNOWN]";
            break;
    }

    logFile << log_level_str << " " << message << "\n";
    logFile.close();
}
