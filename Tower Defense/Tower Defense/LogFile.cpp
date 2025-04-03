#include "logFile.h"

std::ofstream logFile;  

void initializeLogFile(const std::string& filename) {
    logFile.open(filename, std::ios::trunc);
    if (!logFile) {
        std::cerr << "Error opening log file: " << filename << std::endl;
    }
}

void log(const std::string& message) {
    std::cout << message << std::endl; // Print to console
    if (logFile) {
        logFile << message << std::endl; // Write to file
    }
}

void closeLog() {
    if (logFile) {
        logFile.close();
    }
}
