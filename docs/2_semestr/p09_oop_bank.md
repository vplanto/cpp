# Практикум 9: Проектуємо "Monobank Lite" (Вступ в ООП)

← [Index](index.md)

**Теорія:** [Лекція 13: ООП Філософія](13_oop_philosophy.md)

---


## Роль: Backend Architect

Ми більше не пишемо "лаби". Ми пишемо бізнес-логіку.
Ваша задача — створити ядро банківської системи. Головна вимога замовника — **безпека даних**. Ніхто не повинен мати можливості змінити баланс користувача, просто написавши `acc.balance += 1000000`.

## Code Style Convention (Стандарт коду)

З цього моменту ми вводимо суворі правила іменування. Код, що порушує ці правила, не приймається.

> **🏦 Реальна історія: $440M баг через назву функції — Knight Capital Group, 2012**
>
> **Контекст.** 1 серпня 2012 року компанія Knight Capital Group (один з найбільших маркет-мейкерів США) розгортала нову High-Frequency Trading систему — SMARS. Дедлайн тиснув, і в поспіху розробники зробили критичну помилку.
>
> **Що трапилось технічно.** У новому коді вони **перевикористали старий конфігураційний прапорець** з промовистою назвою `Power` (старий алгоритм «Power Peg», який давно не використовувався, але не був видалений). Під час деплою оновили 7 з 8 серверів — один залишився зі старим кодом. Коли система запустилась, цей один сервер побачив знайомий прапорець `Power` і активував старий алгоритм накопичення позицій.
>
> **45 хвилин хаосу.** Система автоматично купувала і продавала акції з такою швидкістю, що за 45 хвилин виконала **4 мільйони угод** на суму ~$7 мільярдів. Трейдери бачили проблему на екранах, але не могли зупинити систему — ніхто не знав, яку саме кнопку натиснути. Збиток — **$440 мільйонів** (весь капітал компанії за одне ранкове торгове засідання).
>
> **Наслідки.** Knight Capital збанкрутувала і була поглинута конкурентом. Пізніший аудит SEC виявив першопричину: **розробники не могли по назві `Power` відрізнити живий код від мертвого**. Якби функція називалась `powerPegLegacy_DEPRECATED` — хтось би точно помітив.
>
> Правильні назви — це не естетика. Це **безпека системи**.



1.  **Classes (Типи даних) — це Іменники (Nouns).**
    * Використовуємо **CamelCase** (велика літера на початку кожного слова, див. [C++ Naming Conventions](https://google.github.io/styleguide/cppguide.html#Type_Names)).
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
    BankAccount(std::string accNum, std::string name, double initialBalance)
        : accountNumber(accNum), ownerName(name) {  // initializer list для string
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

<details markdown="1">
<summary>💡 Референсне рішення (Завдання 3)</summary>

```cpp
    void deposit(double amount) {
        if (amount <= 0) {
            std::cerr << "Error: Deposit amount must be positive.\n";
            return;
        }
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            std::cerr << "Error: Withdrawal amount must be positive.\n";
            return false;
        }
        if (amount > balance) {
            std::cerr << "Error: Insufficient funds.\n";
            return false;
        }
        balance -= amount;
        return true;
    }

    void printInfo() const {
        std::cout << "Account: " << accountNumber
                  << " | Owner: " << ownerName
                  << " | Balance: " << balance << "$\n";
    }
```

</details>

---

## Завдання із зірочкою: PIN Code Security

Додайте ще один рівень захисту.

1. Додайте приватне поле `std::string pinCode`.
2. Додайте `pinCode` у конструктор.
3. Змініть метод `withdraw`: `bool withdraw(double amount, std::string enteredPin)`.
* Якщо PIN неправильний — відхилити транзакцію і вивести "Security Alert".

<details markdown="1">
<summary>💡 Референсне рішення (Завдання із зірочкою)</summary>

```cpp
class BankAccount {
private:
    std::string accountNumber;
    std::string ownerName;
    double balance;
    std::string pinCode;  // NEW: рядок, бо PIN може починатись з 0

public:
    BankAccount(std::string accNum, std::string name, double initialBalance, std::string pin)
        : accountNumber(accNum), ownerName(name), pinCode(pin) {
        if (initialBalance < 0) {
            std::cerr << "Warning: Initial balance cannot be negative. Setting to 0.\n";
            balance = 0;
        } else {
            balance = initialBalance;
        }
    }

    double getBalance() const { return balance; }
    std::string getOwner() const { return ownerName; }

    void deposit(double amount) {
        if (amount <= 0) {
            std::cerr << "Error: Deposit amount must be positive.\n";
            return;
        }
        balance += amount;
    }

    // CHANGED: тепер потрібен PIN
    bool withdraw(double amount, std::string enteredPin) {
        if (enteredPin != pinCode) {
            std::cerr << "Security Alert: Incorrect PIN.\n";
            return false;
        }
        if (amount <= 0) {
            std::cerr << "Error: Withdrawal amount must be positive.\n";
            return false;
        }
        if (amount > balance) {
            std::cerr << "Error: Insufficient funds.\n";
            return false;
        }
        balance -= amount;
        return true;
    }

    void printInfo() const {
        std::cout << "Account: " << accountNumber
                  << " | Owner: " << ownerName
                  << " | Balance: " << balance << "$\n";
    }
};

int main() {
    BankAccount myAcc("UA555", "Vitaliy", 1000, "4242");

    myAcc.withdraw(100, "0000");  // Security Alert!
    myAcc.withdraw(100, "4242");  // OK
    myAcc.printInfo();          // Balance: 900$
}
```

</details>

---

## Definition of Done (Критерії прийому)

1. У коді немає жодного `struct`. Тільки `class`.
2. У `main` неможливо написати `myAcc.balance = ...`.
3. Імена класів — з великої літери, методи — дієслова з маленької.
4. Спроба зняти більше, ніж є, не ламає програму.

---

## Контрольні питання

1. В чому різниця між `struct` і `class` в C++? Чому ми обираємо `class` для `BankAccount`?
2. Що таке **інваріант** класу? Назвіть два інваріанти `BankAccount` з цього практикуму.
3. Чому метод `getBalance()` оголошений з ключовим словом `const`? Що станеться, якщо прибрати `const`?
4. Чому `deposit(-100)` має бути відхилений всередині методу, а не перевірятись у `main` перед кожним викликом?

<details markdown="1">
<summary>Відповіді для самоперевірки</summary>

1. Технічно різниця одна: в `struct` всі члени `public` за замовчуванням, в `class` — `private`. Для `BankAccount` обираємо `class`, щоб явно сигналізувати: це об'єкт з інкапсуляцією, а не просто «мішок з даними».
2. Інваріанти: (а) `balance >= 0` завжди (якщо немає кредитного ліміту); (б) `balance` не може бути змінений ззовні напряму — тільки через `deposit`/`withdraw`.
3. `const` після методу гарантує, що метод не змінює стан об'єкта. Без нього компілятор заборонить викликати цей метод на константному об'єкті (`const BankAccount& acc`), і це порушить API.
4. Це принцип **єдиної відповідальності**: клас сам захищає свої інваріанти. Якщо перевірку покласти на клієнта, будь-який новий клієнт може забути її зробити — і інваріант буде зламано.

</details>

---

## 🔑 Інженерний інсайт: Клас — це контракт, а не структура

Після сьогоднішнього практикуму ви написали свій перший справжній **контракт між кодом і програмістом**.

Подумайте: коли ви передаєте `BankAccount` колезі, ви **гарантуєте** йому:
1. `balance` ніколи не буде від'ємним (інваріант).
2. Отримати баланс можна тільки через `getBalance()` (інкапсуляція).
3. Зняти гроші без PIN неможливо (безпека).

Це і є **API-контракт**. У великих системах (банки, авіація, медицина) порушення контракту — це не баг, це **аварія**.

> Хороший клас — це клас, який **важко використати помилково**.  
> — Scott Meyers, «Effective C++»

Ваш `BankAccount` вже відповідає цьому принципу.
