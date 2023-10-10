#include <fstream>
#include <iostream>

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

    std::string levelStr;
    switch (level) {
        case LogLevel::INFO:
            levelStr = "[INFO]";
            break;
        case LogLevel::WARNING:
            levelStr = "[WARNING]";
            break;
        case LogLevel::ERROR:
            levelStr = "[ERROR]";
            break;
        default:
            levelStr = "[UNKNOWN]";
            break;
    }

    logFile << levelStr << " " << message << "\n";
    logFile.close();
}
