#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>

enum class LogLevel { 
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    Logger(const std::string& filePath);
    ~Logger();

    void log(LogLevel level, const std::string& message);

private:
    std::string filePath_;
};

#endif /* LOGGER_HPP_ */
