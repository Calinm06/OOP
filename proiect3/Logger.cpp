#include "Logger.h"

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::inregistreaza(const std::string& s) {
    log.push_back(s);
}

void Logger::afiseazaLog() {
    std::cout << "Loggerul are " << log.size() << " componente\n";
    for (const auto& s : log)
        std::cout << "-> " << s << "\n";
}
