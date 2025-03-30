#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <mutex>
#include <string>

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << message << std::endl;
    }

private:
    Logger() = default;
    std::mutex mtx;
};

#endif // LOGGER_HPP