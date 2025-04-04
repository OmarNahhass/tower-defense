#ifndef LOG_FILE_H
#define LOG_FILE_H

#include <iostream>
#include <fstream>


extern std::ofstream logFile;


void initializeLogFile(const std::string& filename);


void log(const std::string& message);


void closeLog();

#endif // LOG_H
