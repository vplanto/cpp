# Практикум 9: Проектуємо "Monobank Lite" (Вступ в ООП)

← [Index](index.md)

**Теорія:** [Лекція 13: ООП Філософія](13_oop_philosophy.md)

---


## Роль: Backend Architect

Ми більше не пишемо "лаби". Ми пишемо бізнес-логіку.
Ваша задача — створити ядро банківської системи. Головна вимога замовника — **безпека даних**. Ніхто не повинен мати можливості змінити баланс користувача, просто написавши `acc.balance += 1000000`.

## Code Style Convention (Стандарт коду)

З цього моменту ми вводимо суворі правила іменування. Код, що порушує ці правила, не приймається.

1.  **Classes (Типи даних) — це Іменники (Nouns).**
    * Використовуємо **PascalCase** (Велика літера на початку кожного слова).
    * *Good:* `BankAccount`, `User`, `TransactionManager`.
    * *Bad:* `bank_account` (Python style), `ManageMoney` (це дієслово), `bankaccount` (нечитабельно).

2.  **Methods (Дії) — це Дієслова (Verbs).**
    * Використовуємо **camelCase** (маленька перша, далі великі).
    * Метод має відповідати на питання "Що зробити?".
    * *Good:* `deposit()`, `withdraw()`, `calculateInterest()`, `isValid()`.
    * *Bad:* `Deposit()` (C# style), `money()` (це іменник), `do_it()` (незрозуміло).

3.  **Fields (Змінні класу) — camelCase.**
    * Приватні поля часто починають з `m_` (member) або `_`, але ми будемо використовувати чистий `camelCase`, щоб не плутати вас.
    * *Good:* `balance`, `accountNumber`.

---

## Завдання 1: The Broken Struct (Як не треба)

Створіть файл `main.cpp`. Напишіть структуру, яка імітує рахунок, і зламайте її інваріант.

```cpp
#include <iostream>
#include <string>

// BAD DESIGN: Struct with public data
struct BadAccount {
    std::string owner;
    double balance;
};

void testBadAccount() {
    BadAccount acc;
    acc.owner = "Musk";
    acc.balance = 100;
    
    // КАТАСТРОФА: Прямий доступ до даних
    acc.balance = -9999999; 
    
    std::cout << "Hacked Balance: " << acc.balance << std::endl;
}

```

*Запустіть, переконайтесь, що система дозволяє від'ємний баланс без кредитного ліміту.*

---

## Завдання 2: The Fortress (Інкапсуляція)

Перепишіть це, використовуючи `class`.

**Вимоги:**

1. Клас `BankAccount`.
2. Поля `accountNumber` (string), `ownerName` (string), `balance` (double) — у секції **private**.
3. **Конструктор:** приймає номер, ім'я та початковий баланс.
* *Валідація:* Якщо початковий баланс < 0, встановити його в 0.



```cpp
class BankAccount {
private:
    std::string accountNumber;
    std::string ownerName;
    double balance;

public:
    // Constructor (Nouns setup Nouns)
    BankAccount(std::string accNum, std::string name, double initialBalance) {
        accountNumber = accNum;
        ownerName = name;
        
        if (initialBalance < 0) {
            std::cerr << "Warning: Initial balance cannot be negative. Setting to 0.\n";
            balance = 0;
        } else {
            balance = initialBalance;
        }
    }
    
    // Getters (Read-only access)
    // const означає, що метод НЕ змінює об'єкт
    double getBalance() const { 
        return balance; 
    }
    
    std::string getOwner() const {
        return ownerName;
    }
};

```

---

## Завдання 3: Business Logic (Verbs in Action)

Додайте методи для керування грошима. Пам'ятайте про інваріант: **гроші не беруться з повітря**.

1. **`void deposit(double amount)`**
* Логіка: `amount` має бути > 0. Інакше ігноруємо (або виводимо помилку).


2. **`bool withdraw(double amount)`**
* Логіка: `amount` має бути > 0. `amount` має бути <= `balance`.
* Повертає `true`, якщо успішно зняли, `false` — якщо недостатньо коштів.


3. **`void printInfo() const`**
* Виводить красиво: "Account: UA123... | Owner: Musk | Balance: 100$"



**Перевірка в `main()`:**

```cpp
int main() {
    BankAccount myAcc("UA555", "Vitaliy", 1000);
    
    myAcc.deposit(500); // Balance: 1500
    myAcc.deposit(-100); // Error!
    
    if (myAcc.withdraw(2000)) {
        std::cout << "Success!\n";
    } else {
        std::cout << "Insufficient funds!\n"; // Має спрацювати це
    }
    
    myAcc.printInfo();
    return 0;
}

```

---

## Завдання із зірочкою: PIN Code Security

Додайте ще один рівень захисту.

1. Додайте приватне поле `int pinCode`.
2. Додайте `pinCode` у конструктор.
3. Змініть метод `withdraw`: `bool withdraw(double amount, int enteredPin)`.
* Якщо PIN неправильний — відхилити транзакцію і вивести "Security Alert".

---

## Definition of Done (Критерії прийому)

1. У коді немає жодного `struct`. Тільки `class`.
2. У `main` неможливо написати `myAcc.balance = ...`.
3. Імена класів — з великої літери, методи — дієслова з маленької.
4. Спроба зняти більше, ніж є, не ламає програму.
