# Практикум 10: RAII та Logger — "Чорний ящик" для банку

← [Index](index.md)

**Теорія:** [Лекція 14: RAII](14_raii_lifecycle.md)

---


## Роль: Systems Engineer

Бізнес-вимога: *"Жодна копійка не має зникнути безслідно"*.
Ваша задача — розробити систему логування транзакцій. Якщо сервер впаде, ми маємо знати, хто і скільки грошей зняв.

Ми використовуємо ідіому **RAII**:
1.  **Конструктор** відкриває файл.
2.  **Деструктор** закриває файл.
Ви не маєте права забути закрити файл.

---

## Експрес-опитування (Warm-up)

1.  Що станеться з об'єктом, створеним на стеку (всередині `{...}`), коли програма вийде за межі цих дужок?
2.  Який метод викликається автоматично при знищенні об'єкта?
3.  Чому в деструкторі не можна кидати `exception` (виключення)?

<details markdown="1">
<summary>Інженерна довідка</summary>

1.  Він буде знищений. Пам'ять звільниться.
2.  Деструктор (`~ClassName`).
3.  Бо якщо деструктор викликано через інший exception (Stack Unwinding), другий exception призведе до негайного краху програми (`std::terminate`).

</details>

---

## Завдання 1: Клас `TransactionLogger`

Створіть клас, який бере на себе всю брудну роботу з файлами.

**Вимоги:**
1.  **Розділення коду:** Проєкт має бути розділений на заголовочний файл (`TransactionLogger.h`) та файл реалізації (`TransactionLogger.cpp`).
2.  **Поле:** `std::ofstream file;` (приватне).
3.  **Конструктор:** Приймає ім'я файлу. Відкриває його в режимі додавання (`std::ios::app`), щоб не стирати стару історію.
    * *Перевірка:* Якщо файл не відкрився — вивести помилку в `cerr`.
4.  **Деструктор:** Якщо файл відкритий — закрити його і вивести в консоль повідомлення `[Logger] File closed cleanly.`.
5.  **Метод `log(string level, string message)`:** Приймає статус логу (наприклад, "INFO", "DEBUG", "ERROR") та саме повідомлення. Записує у файл у форматі `[LEVEL] Message`.

### Референсне рішення

**TransactionLogger.h**
```cpp
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
```

**TransactionLogger.cpp**
```cpp
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
```

---

## Завдання 2: Інтеграція з `BankAccount`

Поверніться до вашого класу `BankAccount` з минулого практикуму.
Ми не будемо додавати логер всередину банку як поле (це вимагало б додаткових знань), ми передамо його в методи як інструмент.

**Сценарій:**

1. Оновіть методи `deposit` та `withdraw`, щоб вони приймали посилання на логер: `void deposit(double amount, TransactionLogger& logger)`.
2. У `main` створіть логер один раз і передавайте його в методи банку.

```cpp
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

int main() {
    // 1. Створюємо логер.
    TransactionLogger logger("bank_history.txt");

    BankAccount acc("UA007", "James Bond", 1000);

    // 2. Викликаємо методи, передаючи логер
    acc.deposit(500, logger);
    acc.withdraw(2000, logger);

    // 3. Кінець main — файл закриється деструктором logger.
    return 0;
}
```

---

## Завдання 3: Scope Test (Перевірка RAII)

Доведіть, що файл закривається, навіть якщо ми не дійшли до кінця `main`.

Зробіть штучний блок коду:

```cpp
void testScope() {
    std::cout << "--- Start Scope ---\n";
    {
        TransactionLogger tempLog("temp.txt");
        tempLog.log("DEBUG", "I am alive!");
    } // <--- Тут tempLog помирає. Має спрацювати деструктор.
    std::cout << "--- End Scope ---\n";
}

```

**Очікуваний вивід:**

```text
--- Start Scope ---
[Logger] System started...
--- End Scope ---
[Logger] Buffer flushed. File closed cleanly. (ЦЕ МАЄ БУТИ ПЕРЕД "End Scope"!)

```

---

## Завдання із зірочкою: Time Stamping

Метод `log("Deposit")` — це нудно.
Зробіть так, щоб метод `log` автоматично додавав час.

Вам знадобиться `<ctime>`. Оскільки робота з часом у C++ до C++20 трохи страшна, ось готовий сніпет (або використайте це як привід погуглити):

```cpp
#include <ctime>

// Вставте це всередину методу log
time_t now = time(0);
char* dt = ctime(&now); // Конвертує час у рядок типу "Tue Dec 10..."
// Увага: ctime додає \n в кінці, його треба прибрати, якщо заважає.

```

---

## Definition of Done

1. У проекті є файл `transaction.log` (або подібний).
2. Якщо запустити програму 3 рази, нові логи додаються в кінець, а не перетирають старі.
3. Ви бачите повідомлення деструктора в консолі.
4. Код відповідає конвенції (PascalCase для класів, camelCase для методів).
5. Використано розділення на заголовочний файл (`.h`) та файл реалізації (`.cpp`).

---

## Контрольні питання

1. Розшифруйте абревіатуру RAII. Поясніть своїми словами, яку проблему вона вирішує.
2. Якщо відкрити файл у конструкторі і програма «впаде» через виключення після конструктора — чи закриється файл? Чому?
3. Чим режим `std::ios::app` відрізняється від режиму за замовчуванням при відкритті файлу?
4. Чому `std::ofstream` є приватним полем класу, а не локальною змінною в конструкторі?

<details markdown="1">
<summary>Відповіді для самоперевірки</summary>

1. **Resource Acquisition Is Initialization** — «захоплення ресурсу є ініціалізацією». Вирішує проблему забутого звільнення ресурсів: деструктор гарантовано викличеться при виході зі scope (навіть при виключенні), тому ресурс завжди буде звільнено.
2. Так, файл закриється. Коли стек «розмотується» (stack unwinding) через виключення, деструктор `TransactionLogger` викликається автоматично, і він закриває файл. У цьому і сила RAII.
3. `std::ios::app` (append) відкриває файл і переміщує вказівник запису в **кінець** файлу — нові дані додаються після наявних. Режим за замовчуванням перезаписує файл з початку.
4. Бо поле живе стільки, скільки живе об'єкт класу. Якби `ofstream` був локальною змінною конструктора, він знищився б після виходу з конструктора, закривши файл — і метод `log()` вже не зміг би записувати.

</details>
