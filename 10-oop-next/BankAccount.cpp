#include <iostream>
#include <string>
#include "TransactionLogger.h"

class BankAccount {
private:
    std::string accountNumber;
    double balance;

public:
    BankAccount(std::string acc, std::string owner, double initial) 
        : accountNumber(acc), balance(initial) {}

    void deposit(double amount, TransactionLogger& logger) {
        balance += amount;
        logger.log("INFO", "[Deposit] " + accountNumber + ": +" + std::to_string(amount));
    }

    bool withdraw(double amount, TransactionLogger& logger) {
        if (balance >= amount) {
            balance -= amount;
            logger.log("INFO", "[Withdraw] " + accountNumber + ": -" + std::to_string(amount));
            return true;
        }
        logger.log("DEBUG", "[Withdraw Fail] " + accountNumber + ": Insufficient funds for -" + std::to_string(amount));
        return false;
    }
};

void testScope() {
    std::cout << "--- Start Scope ---\n";
    {
        TransactionLogger tempLog("temp.txt");
        tempLog.log("DEBUG", "I am alive!");
    } // <--- Тут tempLog помирає. Має спрацювати деструктор.
    std::cout << "--- End Scope ---\n";
}

int main() {
    // 1. Створюємо логер.
    TransactionLogger logger("bank_history.txt");

    BankAccount acc("UA007", "James Bond", 1000);

    // 2. Викликаємо методи, передаючи логер
    acc.deposit(500, logger);
    acc.withdraw(2000, logger);

    // 3. Тест Scope
    testScope();

    // 4. Кінець main — файл закриється деструктором logger.
    return 0;
}
