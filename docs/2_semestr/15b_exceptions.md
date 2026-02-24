# Лекція 15b: Обробка виключень — try, catch, throw

[← Лекція 15](15_rule_of_three.md) | [Index](index.md) | [Далі: Лекція 16 →](16_inheritance_polymorphism.md)

## Мета

Зрозуміти механізм обробки виключень у C++ як спосіб відокремити **логіку програми** від **обробки помилок**. Навчитися використовувати `try`, `catch`, `throw`. Зрозуміти ієрархію стандартних виключень та RAII-сумісність.

## Експрес-опитування

1. Як повідомити про помилку у функції, яка повертає `int`? Яка проблема з цим підходом?
2. Що станеться із локальними змінними у функції, якщо викидається виключення?
3. Чи можна перехопити виключення, яке виникло у глибині стека викликів?

<details markdown="1">
<summary>Інженерна відповідь</summary>

1. Повертати "магічне" число (-1, INT_MIN). Проблема — кожен виклик треба перевіряти, легко забути. Код засмічується перевірками.
2. Деструктори викликаються автоматично — **stack unwinding**. Ось чому RAII так важливий: `std::fstream` закриває файл, `unique_ptr` звільняє пам'ять.
3. **Так.** Виключення "піднімається" вгору по стеку викликів до першого відповідного `catch`.

</details>

---

## Частина 1: Проблема — як сигналізувати про помилки?

### Старий підхід: коди повернення

```cpp
// Проблема: потрібно перевіряти кожен виклик
int readFile(const std::string& path, std::string& content) {
    // ... 
    return -1; // помилка відкриття
    return -2; // помилка читання
    return 0;  // успіх
}

int parseData(const std::string& data, Config& cfg) {
    return -1; // некоректний формат
    return 0;
}

// Використання — код засмічується перевірками
int main() {
    std::string content;
    if (readFile("config.txt", content) != 0) {
        // handle error
        return 1;
    }
    Config cfg;
    if (parseData(content, cfg) != 0) {
        // handle error
        return 1;
    }
    // ...
}
```

**Проблеми:**
- Легко **забути** перевірити код помилки
- Неможливо повернути і значення, і код помилки одночасно
- Логіка програми _перемішана_ з обробкою помилок
- Конструктори не мають значення повернення — не можуть сигналізувати про помилку

### Новий підхід: виключення

```cpp
std::string readFile(const std::string& path) {
    // Просто кидаємо — виклик зупиняється негайно
    if (!fileExists(path))
        throw std::runtime_error("File not found: " + path);
    // ...
    return content;
}

int main() {
    try {
        // Чистий код без нескінченних if-ів
        auto content = readFile("config.txt");
        auto cfg = parseData(content);
        run(cfg);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
```

---

## Частина 2: Синтаксис — try, catch, throw

### Базова конструкція

```
try {
    // Код, який може "впасти"
} catch (Тип виключення) {
    // Обробник — виконується якщо wpalo виключення цього типу
}
```

### Приклад: валідація вхідних даних

```cpp
#include <stdexcept>
#include <string>

double divide(double a, double b) {
    if (b == 0.0)
        throw std::invalid_argument("Division by zero");
    return a / b;
}

int main() {
    try {
        double result = divide(10.0, 0.0);  // кидає!
        std::cout << result;                 // не виконується
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught: " << e.what(); // "Caught: Division by zero"
    }
    std::cout << "Program continues\n"; // виконується після catch
}
```

### Кілька catch-блоків

```cpp
void process(int value) {
    if (value < 0)
        throw std::underflow_error("Value is negative");
    if (value > 1000)
        throw std::overflow_error("Value too large");
    if (value == 42)
        throw std::string("The answer!"); // будь-який тип!
}

try {
    process(someValue);
} catch (const std::underflow_error& e) {
    std::cerr << "Underflow: " << e.what();
} catch (const std::overflow_error& e) {
    std::cerr << "Overflow: " << e.what();
} catch (const std::string& msg) {
    std::cerr << "String exception: " << msg;
} catch (...) {
    // Перехоплює БУДЬ-ЯКЕ виключення
    std::cerr << "Unknown exception!";
}
```

> **`catch (...)`** — "catch-all" блок, завжди ставиться останнім.

---

## Частина 3: Ієрархія стандартних виключень

```
std::exception
├── std::logic_error          — помилки логіки програми (можна виявити статично)
│   ├── std::invalid_argument  — некоректний аргумент
│   ├── std::out_of_range      — індекс поза межами
│   ├── std::length_error      — перевищення максимального розміру
│   └── std::domain_error      — математично некоректна операція
│
└── std::runtime_error        — помилки під час виконання (зовнішні)
    ├── std::overflow_error    — арифметичне переповнення
    ├── std::underflow_error   — арифметичне зменшення
    ├── std::range_error       — результат поза діапазоном
    └── std::system_error      — помилки ОС (файли, мережа)
```

Перехоплення базового класу — ловить всі нащадки:

```cpp
try {
    vec.at(100); // кидає std::out_of_range
} catch (const std::logic_error& e) {
    // Перехопить out_of_range, invalid_argument, тощо
    std::cerr << e.what();
}

try {
    // ...
} catch (const std::exception& e) {
    // Перехопить БУДЬ-ЯКЕ стандартне виключення
    std::cerr << "std exception: " << e.what();
}
```

---

## Частина 4: Власні класи виключень

```cpp
#include <stdexcept>

// Власне виключення — наслідуємо від std::exception або нащадків
class DatabaseError : public std::runtime_error {
public:
    int errorCode;

    DatabaseError(const std::string& msg, int code)
        : std::runtime_error(msg), errorCode(code) {}
};

class ConnectionError : public DatabaseError {
public:
    std::string host;

    ConnectionError(const std::string& host, int code)
        : DatabaseError("Cannot connect to " + host, code), host(host) {}
};

// Використання:
try {
    throw ConnectionError("db.example.com", 503);
} catch (const ConnectionError& e) {
    std::cerr << e.what() << " (host: " << e.host << ")\n";
} catch (const DatabaseError& e) {
    std::cerr << "DB error " << e.errorCode << ": " << e.what() << "\n";
} catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
}
```

---

## Частина 5: Stack Unwinding та RAII

**Stack unwinding** — автоматичний виклик деструкторів всіх локальних об'єктів при розкрутці стека через виключення.

```cpp
#include <fstream>
#include <memory>

void riskyOperation() {
    // RAII — деструктор закриє файл автоматично, навіть якщо кинуто виключення
    std::fstream file("data.txt", std::ios::in);

    // RAII — unique_ptr звільнить пам'ять
    auto buffer = std::make_unique<int[]>(1024);

    if (someCondition())
        throw std::runtime_error("operation failed");

    // Деструктори file і buffer викликаються АВТОМАТИЧНО
    // незалежно від того, чи кинуто виключення
}

int main() {
    try {
        riskyOperation();
    } catch (const std::exception& e) {
        // file вже закрито, memory вже звільнено -- БЕЗ ВИТОКІВ
        std::cerr << e.what();
    }
}
```

> [!IMPORTANT]
> RAII + виключення = надійне керування ресурсами. Ніколи не використовуйте голі `new`/`delete` у коді з виключеннями — гарантований витік пам'яті або подвійне звільнення.

**Небезпечний код (без RAII):**

```cpp
void dangerous() {
    int* p = new int[100]; // виділили пам'ять
    doSomething();         // якщо кине — p НЕ БУДЕ ЗВІЛЬНЕНО!
    delete[] p;            // може не виконатись!
}
```

**Безпечний код (RAII):**

```cpp
void safe() {
    auto p = std::make_unique<int[]>(100); // RAII
    doSomething(); // якщо кине — деструктор unique_ptr звільнить пам'ять
}
```

---

## Частина 6: noexcept та специфікатори виключень

`noexcept` — гарантія компілятору, що функція **не кидає виключень**:

```cpp
// Гарантуємо: ця функція ніколи не кидає
int add(int a, int b) noexcept {
    return a + b;
}

// Компілятор може оптимізувати виклик noexcept функцій
// (не генерує код для stack unwinding)
```

> Переміщуючі конструктори (`move constructor`) і `swap` майже завжди позначають `noexcept` — це дозволяє `std::vector` безпечно переалокувати пам'ять.

```cpp
class MyClass {
public:
    MyClass(MyClass&& other) noexcept; // vector може використати move, не copy
    void swap(MyClass& other) noexcept;
};
```

---

## Порівняльна таблиця: коди vs виключення

| Критерій | Коди повернення | Виключення |
|---------|----------------|-----------|
| **Ігнорування помилки** | Легко забути перевірку | Неможливо ігнорувати |
| **Конструктори** | ❌ Немає повернення | ✅ Можна кидати |
| **Читабельність** | Засмічується if-ами | Чиста логіка |
| **Продуктивність** | O(1) — без накладних витрат | Накладні витрати при кидку |
| **Коли використовувати** | Hot path, передбачені стани | Виняткові, непередбачені ситуації |

> **Правило:** Виключення — для **виняткових** ситуацій. Якщо подія очікувана і часта (наприклад, "файл не знайдено" в звичайному пошуку) — краще повертати `std::optional` або `bool`.

---

## Контрольні питання

1. Чому конструктори не можуть повернути код помилки, і як вирішити це виключеннями?

<details markdown="1">
<summary>Відповідь</summary>

Конструктор не має типу повернення — він завжди повертає новий об'єкт. Якщо ресурс недоступний (файл, пам'ять, мережа), єдиний спосіб сигналізувати — кинути виключення. Об'єкт у "нажиттєздатному" стані просто не буде створено, а пам'ять для часткового об'єкта автоматично звільниться.

</details>

2. Що таке stack unwinding і як воно пов'язане з RAII?

<details markdown="1">
<summary>Відповідь</summary>

Stack unwinding — автоматичний виклик деструкторів всіх локальних об'єктів у фреймах стека між місцем `throw` і місцем `catch`. RAII гарантує, що всі ресурси (файли, пам'ять, м'ютекси) будуть звільнені деструкторами навіть при виключенні, без будь-якого додаткового коду очищення.

</details>

3. Яка різниця між `std::logic_error` та `std::runtime_error`?

<details markdown="1">
<summary>Відповідь</summary>

- **`std::logic_error`** — помилки в логіці програми, які теоретично можна виявити до запуску (некоректні аргументи, порушення передумов). Свідчать про баг у коді.
- **`std::runtime_error`** — помилки, які виникають під час виконання через зовнішні причини (файл не знайдено, мережа недоступна, переповнення). Їх неможливо передбачити статично.

</details>

4. Навіщо позначати move-конструктор як `noexcept`?

<details markdown="1">
<summary>Відповідь</summary>

`std::vector` при переалокації (збільшенні розміру) мусить вибрати: використати move або copy для переміщення елементів. Якщо move-конструктор **не** `noexcept`, vector змушений використовувати copy (безпечніше при виключеннях). Якщо **є** `noexcept` — vector використовує ефективний move. Тому `noexcept` на move-конструкторі — це not just стиль, а реальна оптимізація.

</details>
