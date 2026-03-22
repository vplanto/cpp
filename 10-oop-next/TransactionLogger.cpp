#include "TransactionLogger.h"
#include <iostream>

TransactionLogger::TransactionLogger(std::string filename) {
    file.open(filename, std::ios::app);
    
    if (!file.is_open()) {
        std::cerr << "[Error] Critical: Cannot open log file!\n";
    } else {
        std::cout << "[Logger] System started. Writing to " << filename << "\n";
    }
}

TransactionLogger::~TransactionLogger() {
    if (file.is_open()) {
        file.close();
        std::cout << "[Logger] Buffer flushed. File closed cleanly.\n";
    }
}

void TransactionLogger::log(std::string level, std::string message) {
    if (file.is_open()) {
        file << "[" << level << "] " << message << "\n";
    }
}
