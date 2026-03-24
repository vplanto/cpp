#ifndef TRANSACTION_LOGGER_H
#define TRANSACTION_LOGGER_H

#include <fstream>
#include <string>

class TransactionLogger {
private:
    std::ofstream file;

public:
    TransactionLogger(std::string filename);
    ~TransactionLogger();

    TransactionLogger(const TransactionLogger&) = delete;
    TransactionLogger& operator=(const TransactionLogger&) = delete;
    void log(std::string level, std::string message);
};

#endif
