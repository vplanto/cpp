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
1.  **Поле:** `std::ofstream file;` (приватне).
2.  **Конструктор:** Приймає ім'я файлу. Відкриває його в режимі додавання (`std::ios::app`), щоб не стирати стару історію.
    * *Перевірка:* Якщо файл не відкрився — вивести помилку в `cerr`.
3.  **Деструктор:** Якщо файл відкритий — закрити його і вивести в консоль повідомлення `[Logger] File closed cleanly.`.
4.  **Метод `log(string message)`:** Дописує повідомлення у файл + додає перехід на новий рядок.

```cpp
#include <iostream>
#include <fstream>
#include <string>

class TransactionLogger {
private:
    std::ofstream file; // Ресурс

public:
    // Ctor: Resource Acquisition
    TransactionLogger(std::string filename) {
        // ios::app - append mode (дописувати в кінець)
        file.open(filename, std::ios::app);
        
        if (!file.is_open()) {
            std::cerr << "[Error] Critical: Cannot open log file!\n";
        } else {
            std::cout << "[Logger] System started. Writing to " << filename << "\n";
        }
    }

    // Dtor: Resource Release
    ~TransactionLogger() {
        if (file.is_open()) {
            file.close();
            // Цей вивід потрібен тільки для навчання, щоб ви бачили момент смерті
            std::cout << "[Logger] Buffer flushed. File closed cleanly.\n";
        }
    }

    void log(std::string message) {
        if (file.is_open()) {
            file << message << "\n";
        }
    }
};

```

---

## Завдання 2: Інтеграція з `BankAccount`

Поверніться до вашого класу `BankAccount` з минулого практикуму.
Ми не будемо пхати логер всередину банку (поки що), ми використаємо його ззовні.

**Сценарій:**

1. Створіть `TransactionLogger` у `main`.
2. Виконайте операції з банком.
3. Запишіть результат у лог.

```cpp
// Приклад оновленого BankAccount (фрагмент)
class BankAccount {
    // ... (код з p09) ...
    std::string getAccountNumber() const { return accountNumber; }
};

int main() {
    // 1. Створюємо логер. Файл відкривається ТУТ.
    TransactionLogger logger("bank_history.txt");

    BankAccount acc("UA007", "James Bond", 1000);

    // 2. Симуляція роботи
    acc.deposit(500);
    logger.log("[Transaction] UA007: Deposit +500. Result: Success.");

    if (acc.withdraw(2000)) {
        logger.log("[Transaction] UA007: Withdraw -2000. Result: Success.");
    } else {
        logger.log("[Transaction] UA007: Withdraw -2000. Result: Fail (Insufficient Funds).");
    }

    // 3. Кінець функції main.
    // ТУТ автоматично викличеться ~TransactionLogger().
    // Файл закриється сам.
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
        tempLog.log("I am alive!");
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
