#include "logFile.h"

std::ofstream logFile;  


/*
Create and open new .txt file
*/
void initializeLogFile(const std::string& filename) {
    logFile.open(filename, std::ios::trunc);

    if (!logFile) {
        std::cerr << "Error opening log file: " << filename << std::endl;
    }
}

/*
Log new line into .txt file
*/
void log(const std::string& message) {
    std::cout << message << std::endl; // Print to console

    if (logFile) {
        logFile << message << std::endl; // Write to file
    }
}

/*
Close .txt file when done 
*/
void closeLog() {
    if (logFile) {
        logFile.close();
    }
}
