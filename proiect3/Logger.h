#pragma once
#include <iostream>
#include <string>
#include <vector>

class Logger {
private:
    std::vector<std::string>log;
    Logger() = default;
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance();
    void inregistreaza(const std::string& s);
    void afiseazaLog();
};

