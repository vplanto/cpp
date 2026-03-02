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

Це важливі метрики якості коду.

* **Cohesion (Зчеплення всередині):** Наскільки методи класу стосуються однієї теми.
* *Good:* Клас `BankAccount` робить тільки фінансові операції.
* *Bad:* Клас `BankAccount` також вміє надсилати Email і друкувати PDF (God Object).

* **Coupling (Залежність між класами):** Наскільки сильно класи "знають" один про одного.
* *Meta:* Ми прагнемо до **High Cohesion** та **Low Coupling**. Розділення на `.h` та `.cpp` допомагає зменшити Coupling.

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
