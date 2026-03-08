---
title: Лекція 14 — RAII, Анатомія методів, Структура проекту
---

# Лекція 14: Життєвий цикл (RAII), Анатомія методів та Структура проекту

[← Лекція 13](13_oop_philosophy.md) | [Index](index.md) | [Далі: Лекція 15 →](15_rule_of_three.md)


## Мета
Ми навчилися створювати об'єкти (L13). Тепер ми навчимося:
1.  **Автоматизувати їх смерть** (RAII) — головна фішка C++.
2.  **Розуміти магію методів** (що таке `this` насправді).
3.  **Організовувати код** (Header vs Implementation).

## Експрес-опитування

1.  Якщо ми робимо `return` посеред функції (наприклад, через помилку), чи видалиться локальна змінна (об'єкт на стеку), яка була створена *до* `return`?
2.  Що насправді означає `const` після назви методу: `void get() const`?

<details markdown="1">
<summary>Інженерна відповідь</summary>

1.  **Так!** C++ гарантує виклик деструкторів для всіх стекових об'єктів при виході з їхньої області видимості. Це база RAII.
2.  Це обіцянка компілятору (і користувачу): "Цей метод **не змінює** інваріант об'єкта" (read-only доступ).

</details>

---

## Частина 1: RAII — Ресурс як Об'єкт

Минулого разу ми говорили про Деструктор. Тепер час зрозуміти найважливішу ідіому C++: **RAII** (Resource Acquisition Is Initialization).

### Проблема: "Забудькуватий програміст"
У C (і в старому стилі) ми керували ресурсами вручну:
```cpp
void badCode() {
    FILE* f = fopen("secret.txt", "r"); // (1) Відкрили
    // ... 100 рядків коду ...
    if (error) return; // ЗАБУЛИ fclose(f)! Ресурс "потік" назавжди.
    fclose(f); // (2) Закрили (якщо пощастить дійти сюди)
}

```

### Рішення: RAII (SBRM)

Ми прив'язуємо життя ресурсу (файлу, пам'яті, з'єднання з БД) до життя об'єкта на стеку.

1. **Constructor:** Захоплює ресурс.
2. **Destructor:** Звільняє ресурс.

```cpp
class FileHandler {
    FILE* f;
public:
    FileHandler(const char* name) { 
        f = fopen(name, "r"); 
        // Якщо файл не знайдено, варто опрацювати помилку
        if (!f) {
            std::cerr << "File not found\n";
            // exit(1) або інша обробка помилок
        }
    }
    
    // Деструктор завжди викликається при виході з scope
    ~FileHandler() { 
        if (f) {
            fclose(f); 
            std::cout << "File closed automatically.\n";
        }
    }
};

void goodCode() {
    FileHandler fh("secret.txt"); // Відкрився
    if (true) return; // fh знищується тут, файл закривається САМ.
}

```

> **Правило:** Ніколи не пишіть `delete` або `close()` вручну в бізнес-логіці. Загорніть це в клас.

### Що компілятор генерує за нас?

Навіть якщо ви напишете абсолютно порожній клас:
```cpp
class Empty {};
```
Компілятор C++ автоматично "мовчки" згенерує для нього наступні методи (якщо ви не визначите їх самостійно і якщо це не заборонено іншими правилами):
1. **Default Constructor** (`Empty()`)
2. **Copy Constructor** (`Empty(const Empty&)`)
3. **Copy Assignment Operator** (`Empty& operator=(const Empty&)`)
4. **Destructor** (`~Empty()`)
5. *Move Constructor* (`Empty(Empty&&)`) — у C++11 і вище
6. *Move Assignment Operator* (`Empty& operator=(Empty&&)`) — у C++11 і вище

З цими методами ми більш детально розберемося у наступній лекції (Правило Трьох).

## Частина 2: Анатомія методу (`this`)

Студенти часто думають, що методи живуть *всередині* об'єкта.
Насправді, об'єкт у пам'яті — це **тільки дані** (`struct` fields). Методи живуть у секції коду (Text Segment) і вони **спільні** для всіх об'єктів класу.

Як же метод знає, з яким саме об'єктом він працює?
Через прихований аргумент **`this`**.

### Що бачите ви:

```cpp
class Point { 
    int x;
public:
    void setX(int val) { 
        x = val; // Як він знає, чий це x?
    }
};

Point p1, p2;
p1.setX(10);

```

### Що бачить компілятор (Under the hood):

```cpp
// Метод перетворюється на глобальну функцію
void Point_setX(Point* const this, int val) {
    this->x = val;
}

// Виклик перетворюється на:
Point_setX(&p1, 10);

```

**`this`** — це вказівник на поточний об'єкт, для якого викликано метод.
Він потрібен, коли:

1. Ім'я аргументу збігається з полем (`this->x = x`).
2. Треба повернути посилання на самого себе (`return *this` — побачимо в Operator Overloading).

---

## Частина 3: Const Correctness (Захист Інваріанта)

Якщо ми передаємо об'єкт у функцію як `const Date& d`, ми обіцяємо не змінювати його. Але як компілятор дізнається, які методи змінюють об'єкт, а які — ні?

Ми маємо явно помітити методи як "безпечні" (`const`).

```cpp
class Date {
    int day;
public:
    int getDay() const { // Read-only метод
        // day = 5; // error: assignment of member 'Date::day' in read-only object
        return day;
    }

    void setDay(int d) { // Mutating метод (без const)
        day = d;
    }
};

void printDate(const Date& d) {
    cout << d.getDay(); // ОК: викликаємо const метод
    // d.setDay(10);    // error: passing 'const Date' as 'this' argument discards qualifiers
}

```

> **💡 Exact Compiler Error Messages:**
>
> - Спроба змінити член в const методі: `error: assignment of member 'ClassName::memberName' in read-only object`
> - Спроба викликати non-const метод на const об'єкті: `error: passing 'const ClassName' as 'this' argument discards qualifiers`
>
> Ці повідомлення з'являться при компіляції і допоможуть зрозуміти, що саме порушено. Запам'ятайте їх для дебагу власного коду!

**Best Practice:** Якщо метод не змінює поля класу — **зобов'язаний** бути `const`.

---

## Частина 4: Структура проекту (.h vs .cpp)

Досі ми писали все в одному файлі. У реальних проектах ми розділяємо **Інтерфейс** (Declaration) та **Реалізацію** (Definition).

### Що таке інтерфейс та контракт?

* **Інтерфейс** (переважно оголошується в `.h` файлі) — це сукупність публічних методів та типів класу, доступних іншим частинам програми. Він визначає, *що* об'єкт вміє робити.
* **Контракт** — це угода між розробником класу та його споживачем (іншим програмістом). Інтерфейс виступає чітким контрактом: він гарантує наявність певних методів, їхні параметри та результати використання. Користувачу цього контракту не потрібно знати, *як* він реалізований під капотом (у `.cpp` файлі), достатньо виконувати правила його виклику.

### Чому? (Separation of Concerns)

1. **Швидкість збірки:** Якщо ви змінили логіку в `.cpp`, перекомпілюється лише один файл.
2. **API Design:** Користувач вашого класу читає `.h` файл як документацію. Йому не треба бачити "кишки" (реалізацію).

Схема файлів:

**1. `BankAccount.h` (ЩО робить клас)**

```cpp
#pragma once

class BankAccount {
    double balance;
public:
    BankAccount(double start);
    void deposit(double amount);
};
```

### Header Guards — Both Syntaxes

Обов'язково використовуємо **Include Guards**, щоб уникнути дублювання коду при повторному `#include`. Існує **два способи**:

**Method 1: Standard C++ (#ifndef guards)**

```cpp
// logger.h
#ifndef LOGGER_H
#define LOGGER_H

class Logger {
public:
    void log(const std::string& msg);
};

#endif  // LOGGER_H
```

**Method 2: Modern (#pragma once)**

```cpp
// logger.h
#pragma once

class Logger {
public:
    void log(const std::string& msg);
};
```

**Порівняння:**

<table>
<thead>
<tr><th>Характеристика</th><th><code>#ifndef</code> Guards</th><th><code>#pragma once</code></th></tr>
</thead>
<tbody>
<tr><td><strong>Стандарт C++</strong></td><td>Офіційна частина стандарту</td><td>Compiler extension (non-standard)</td></tr>
<tr><td><strong>Підтримка</strong></td><td>100% компіляторів</td><td>~99.9% (GCC, Clang, MSVC, ICC)</td></tr>
<tr><td><strong>Ризик конфліктів</strong></td><td>Можливий (якщо два файли мають однакові імена макросів)</td><td>Немає (based on file identity)</td></tr>
<tr><td><strong>Читабельність</strong></td><td>Більше тексту (3 рядки)</td><td>Компактніше (1 рядок)</td></tr>
<tr><td><strong>Performance</strong></td><td>Трохи повільніше (парсинг макросів)</td><td>Швидше (compiler може кешувати)</td></tr>
</tbody>
</table>

**Коли використовувати кожен:**

- **`#pragma once`**: Для сучасних проектів (2015+), де ви контролюєте компілятор
- **`#ifndef`**: Для legacy/portable code, стандартна освіта, або якщо ви пишете бібліотеку для широкого використання

> **💡 Case Study: Лінус Торвальдс та Ядро Linux**
>
> Незважаючи на те, що `#pragma once` коротший і зручніший, у вихідному коді Ядра Linux (Linux Kernel) він **не використовується**. Лінус Торвальдс та інші мейнтейнери ядра суворо дотримуються класичних `#ifndef` include guards. 
> 
> **Чому?** Ядро Linux має компілюватися на величезній кількості різних архітектур (від суперкомп'ютерів до розумних чайників) та всілякими, навіть старими або екзотичними компіляторами. Оскільки `#pragma once` формально не є частиною стандарту мови (це compiler extension), покладатись на нього в такому фундаментальному проекті — ризик. Це класичний приклад того, коли **стовідсоткова портативність та надійність** стають важливішими за зручність написання одного рядка коду замість трьох.

**Типова помилка (без guards):**

```cpp
// point.h (БЕЗ guards)
class Point { int x, y; };

// main.cpp
#include "point.h"
#include "geometry.h"  // Ця геометрія також робить #include "point.h"

// error: redefinition of 'class Point'
```

**З guards:**

```cpp
#pragma once  // або #ifndef POINT_H

class Point { int x, y; };
```

Тепер компілятор включить `point.h` тільки один раз, навіть якщо він `#include` його багато разів.

---

## Частина 5: Coupling & Cohesion (Архітектурна хвилинка)

Це дві фундаментальні метрики якості архітектури програмного забезпечення (або архітектури коду загалом). Ми завжди прагнемо до **High Cohesion** (висока зв'язність всередині модулів) та **Low Coupling** (низька залежність між модулями/класами).

### Приклад (Погано): High Coupling + Low Cohesion

Клас робить забагато різних речей (Low Cohesion) і занадто сильно знає про деталі інших систем (High Coupling). Це так званий антипатерн "God Object".

```cpp
// ❌ ПОГАНО: Клас перевантажений обов'язками
class UserAccount {
public:
    void registerUser(string name) {
        // 1. Бізнес-логіка (зберігає стан)
        userName = name;
        
        // 2. High Coupling із базою даних (жорстко зав'язаний на SQL)
        Database::runQuery("INSERT INTO users VALUES ('" + name + "')");
        
        // 3. Low Cohesion (відправка пошти взагалі не стосується "акаунту")
        SMTPServer emailServer("smtp.google.com");
        emailServer.sendAuth(adminLogin, adminPass);
        emailServer.send(name + "@mail.com", "Welcome!");
    }
private:
    string userName;
};
```

* **Проблема 1 (Coupling):** Якщо ми змінимо базу даних (наприклад, на NoSQL) або змінимо спосіб сповіщення (замість Email будемо слати в Telegram), нам доведеться змінювати код класу `UserAccount`.
* **Проблема 2 (Cohesion):** Знання про імейл-сервери порушують логіку класу користувача. `UserAccount` має займатися лише даними користувача.
* **Проблема 3 (Тестування):** Неможливо протестувати логіку цього методу (наприклад, валідацію нікнейму), не відправляючи при цьому реальних імейлів та не підключаючись до справжньої бази.

### Виправлення (Добре): Low Coupling + High Cohesion

Ми розділяємо обов'язки (Single Responsibility Principle) та послаблюємо зв'язки за допомогою інтерфейсів.

```cpp
// ✅ ДОБРЕ: Кожен клас робить тільки одну річ (High Cohesion)

// 1. Відповідає тільки за сповіщення
class INotifier { // Інтерфейс зменшує Coupling
public:
    virtual void sendWelcomeMessage(string user) = 0;
};

// 2. Відповідає тільки за роботу з даними
class IUserRepository {
public:
    virtual void saveUser(string name) = 0;
};

// 3. UserAccount тепер фокусується ТІЛЬКИ на своїх бізнес-правилах
class UserAccount {
    IUserRepository& db;
    INotifier& notifier;
    string userName;

public:
    // Залежності передаються ззовні (Dependency Injection)
    UserAccount(IUserRepository& repo, INotifier& notif) 
        : db(repo), notifier(notif) {}

    void registerUser(string name) {
        userName = name;
        db.saveUser(name);         // Не знає про SQL, знає лише про контракт!
        notifier.sendWelcomeMessage(name); // Не знає про SMTP
    }
};
```

* **Чому це краще?** Якщо завтра ми захочемо записувати користувачів не в БД, а у `.txt` файл, код `UserAccount` **взагалі не зміниться**. Ми просто напишемо новий малий клас для запису в файл (який реалізує `IUserRepository`) і передамо його під час створення акаунту. Це і є магія Low Coupling.

---

## Практичне застосування

**Див.:** [Практикум 10: RAII Logger](p10_raii_logger.md) — застосування RAII для автоматичного управління файлами.

## Контрольні питання

1. В чому різниця між `delete` та Деструктором?
2. Ви написали метод `int getAge() { return age; }`. Чому на Code Review вам зроблять зауваження? (Підказка: `const`).
3. Навіщо ми пишемо `MyClass::` перед назвою методу в `.cpp` файлі?
4. Що таке `#pragma once` і навіщо воно треба? 

<details markdown="1">
<summary>Відповіді</summary>

1. `delete` — це оператор, який звільняє пам'ять. Деструктор — це метод, який готує об'єкт до видалення (закриває файли тощо). `delete` автоматично викликає Деструктор.
2. Метод, що тільки читає дані, має бути позначений як `const`: `int getAge() const`.
3. Щоб сказати компілятору, що ця функція належить саме класу `MyClass`, а не є глобальною. Це оператор розширення області видимості (Scope Resolution).
4. Це захист від повторного включення (Include Guard). Якщо файл `.h` підключено двічі, це запобігає помилці дублювання оголошень.

</details>
