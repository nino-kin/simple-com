#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <string>

enum class LogLevel { INFO, WARNING, ERROR };

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();

    void Log(LogLevel level, const std::string& message);

private:
    std::ofstream log_file;
};

#endif /* LOGGER_H_ */
