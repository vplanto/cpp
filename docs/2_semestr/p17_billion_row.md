---
title: "Практикум 17 — 1 Billion Row"
semester: 2
type: lab
hours: 2
prerequisites: ["24_performance_deep_dive"]
---

> **Дисклеймер / Disclaimer**  
> Авторська декларація: Базовий контент, концепцію та архітектуру цього курсу розроблено автором на основі власних лекцій та презентацій. Інструменти штучного інтелекту (LLM) використано виключно як технічний засіб для конвертації форматів (Slides → Markdown) та розгортання текстових тез. Увесь підсумковий текст, архітектурні схеми та код повністю вичитано, верифіковано та затверджено автором.

# Практикум 17: 1 Billion Row Challenge — Екстремальна оптимізація

← [Index](index.md)

**Теорія:** [Лекція 24: Performance Deep Dive](24_performance_deep_dive.md)

---

## Роль: Performance Engineer

Ви — Backend Engineer у погодному стартапі. Ваша мережа метео станцій надсилає 10 мільйонів записів температури *щодня*. Ваш поточний скрипт обробляє це за 15 секунд. Це занадто довго для real-time дашборду.

**Задача:** Прискорити обробку даних у **10-50 разів** шляхом послідовних оптимізацій.

**Правило інженерії:** *"Make it work, make it right, make it fast"* — ви вже вмієте "work", сьогодні час для "fast".

---

## Частина 0: Налаштування середовища (для початківців)

### Крок 1: Структура проекту

Створіть папку та файли:

```bash
mkdir billion_row_challenge
cd billion_row_challenge
touch generator.cpp baseline.cpp timer.h Makefile
```

**Результат:**
```
billion_row_challenge/
├── Makefile           # Автоматизація компіляції
├── timer.h            # Клас для вимірювання часу
├── generator.cpp      # Генератор тестових даних
├── baseline.cpp       # V0: Наївна реалізація
├── opt1_stringview.cpp   # V1: String view
├── opt2_intmath.cpp      # V2: Integer math
└── measurements.txt   # (буде згенеровано)
```

### Крок 2: Створіть timer.h

```cpp
// timer.h
#pragma once
#include <chrono>
#include <iostream>
#include <string>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::string name;

public:
    Timer(const std::string& n = "Timer") : name(n) {
        start = std::chrono::high_resolution_clock::now();
    }
    
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "[" << name << "] " << ms.count() << " ms\\n";
    }
};
```

### Крок 3: Створіть Makefile

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Debug build
debug: CXXFLAGS += -g -O0
debug: baseline

# Release build (для вимірювань!)
release: CXXFLAGS += -O3 -march=native  
release: baseline

baseline: baseline.cpp timer.h
\t$(CXX) $(CXXFLAGS) baseline.cpp -o baseline

generator: generator.cpp
\t$(CXX) $(CXXFLAGS) generator.cpp -o generator

clean:
\trm -f baseline generator opt1 opt2 measurements.txt

.PHONY: debug release clean
```

**Використання:**
```bash
make release      # Компіляція з оптимізаціями
./baseline        # Запуск

make clean        # Очистити
```

### Крок 4: Git для відстеження прогресу

```bash
git init
git add .
git commit -m "Initial setup"
```

**Після кожної оптимізації:**
```bash
git add baseline.cpp
git commit -m "V1: string_view, 5.2s (2.9x faster)"
```

---

## Частина 1: Генератор даних

### Завдання

Згенерувати файл `measurements.txt` з 10 мільйонів рядків формату:
```
StationName;Temperature
Kyiv;12.5
Lviv;-3.2
Odesa;15.7
```

### Код generator.cpp

```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iomanip>

int main() {
    const int N_ROWS = 10'000'000;  // 10 мільйонів
    
    std::vector<std::string> stations = {
        "Kyiv", "Lviv", "Odesa", "Kharkiv", "Dnipro",
        "London", "Paris", "Berlin", "Tokyo", "NewYork"
    };
    
    std::ofstream file("measurements.txt");
    std::mt19937 rng(42);  // Seed для повторюваності
    std::uniform_int_distribution<int> dist_station(0, stations.size() - 1);
    std::uniform_real_distribution<float> dist_temp(-99.9, 99.9);
    
    std::cout << "Generating " << N_ROWS << " rows...\\n";
    
    for (int i = 0; i < N_ROWS; ++i) {
        file << stations[dist_station(rng)] << ";"
             << std::fixed << std::setprecision(1) << dist_temp(rng) << '\\n';
    }
    
    std::cout << "Done! File size: ~" << (N_ROWS * 20 / 1024 / 1024) << " MB\\n";
    return 0;
}
```

### Компіляція та запуск

```bash
make generator
./generator
```

**Результат:** Файл `measurements.txt` (~200 MB).

---

## Частина 2: Baseline — як пише Junior

### Завдання

Для кожної станції знайти min/max/avg температуру.

### Код baseline.cpp

```cpp
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <limits>
#include "timer.h"

struct Stats {
    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::lowest();
    double sum = 0;
    int count = 0;
    
    void update(double temp) {
        if (temp < min) min = temp;
        if (temp > max) max = temp;
        sum += temp;
        count++;
    }
    
    double avg() const { return sum / count; }
};

int main() {
    Timer total("Total");
    
    std::map<std::string, Stats> data;
    std::ifstream file("measurements.txt");
    std::string line;
    
    {
        Timer parse("Parsing");
        while (std::getline(file, line)) {
            size_t pos = line.find(';');
            std::string station = line.substr(0, pos);        // Копіювання!
            double temp = std::stof(line.substr(pos + 1));   // Повільний парсинг!
            
            data[station].update(temp);
        }
    }
    
    // Вивід результатів
    std::cout << "\\nResults:\\n";
    for (const auto& [station, stats] : data) {
        std::cout << station << ": min=" << stats.min 
                  << ", max=" << stats.max 
                  << ", avg=" << stats.avg() << "\\n";
    }
    
    return 0;
}
```

### Компіляція та вимірювання

```bash
make release
time ./baseline
```

**Очікуваний час:** ~10-15 секунд (залежно від CPU).

**Запишіть свій результат:**
```bash
echo "Baseline: 15.0s" >> results.txt
git add baseline.cpp results.txt
git commit -m "Baseline: 15.0s"
```

### Проблеми коду

1. **Copy Hell:** `substr()` створює нові `std::string` (виділення пам'яті)
2. **Slow Parsing:** `std::stof()` використовує locale та винятки
3. **Map Overhead:** `std::map` (дерево) повільніший за hash table

---

## Частина 3: Оптимізація 1 — String View (Zero Copy)

> **💡 Modern C++ Feature: std::string_view (C++17)**
>
> До C++17 для передачі рядків без копіювання використовували `const std::string&`. Але це мало обмеження:
> - Працює тільки з `std::string`
> - Не можна створити "вікно" у частину рядка без `substr()` (яке копіює!)
>
> **std::string_view** вирішує ці проблеми:
> ```cpp
> // Що це?
> class string_view {
>     const char* ptr;   // Вказівник на дані
>     size_t len;        // Довжина
> };
> ```
>
> **Розмір:** Всього 16 байт (вказівник + число) проти тисяч байт для копіювання рядка!
>
> **Використання:**
> ```cpp
> std::string str = "Hello, World!";
> std::string_view full(str);           // Вся строка
> std::string_view part(str.data(), 5); // "Hello" — 0 копіювань!
> ```
>
> **⚠️ ВАЖЛИВО — Lifetime:**
> `string_view` НЕ володіє даними, тільки вказує на них. Якщо оригінальні дані знищено — маємо dangling pointer!
>
> ```cpp
> std::string_view danger;
> {
>     std::string temp = "Temporary";
>     danger = temp;  // Ок поки temp живе
> }  // temp знищено!
> // danger тепер вказує на знищену пам'ять — ❌ УБ (Undefined Behavior)
> ```
>
> **Коли безпечно:**
> - Данні з `std::string`, що живе довше
> - Literal strings (`"hello"` — живуть вічно)
> - Буфер, який ми контролюємо
>
> **Компіляція:**
> ```bash
> g++ -std=c++17 ...  # Потрібен C++17!
> ```

### Ідея

`std::string_view` — це "погляд" на пам'ять без копіювання даних.

**Замість:**
```cpp
std::string name = line.substr(0, pos);  // Allocation + Copy
```

**Використати:**
```cpp
std::string_view name(line.data(), pos);  // Тільки вказівник + довжина
```

### Код opt1_stringview.cpp

```cpp
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <string_view>
#include <limits>
#include "timer.h"

struct Stats {
    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::lowest();
    double sum = 0;
    int count = 0;
    
    void update(double temp) {
        if (temp < min) min = temp;
        if (temp > max) max = temp;
        sum += temp;
        count++;
    }
    
    double avg() const { return sum / count; }
};

int main() {
    Timer total("Total");
    
    // Використовуємо unordered_map замість map
    std::unordered_map<std::string, Stats> data;
    std::ifstream file("measurements.txt");
    std::string line;
    
    {
        Timer parse("Parsing");
        while (std::getline(file, line)) {
            size_t pos = line.find(';');
            
            // String view замість substr
            std::string_view station_view(line.data(), pos);
            std::string_view temp_view(line.data() + pos + 1, line.size() - pos - 1);
            
            // Конвертуємо для використання як ключ map
            std::string station(station_view);
            double temp = std::stof(std::string(temp_view));  // Поки ще повільно
            
            data[station].update(temp);
        }
    }
    
    std::cout << "\\nStations processed: " << data.size() << "\\n";
    
    return 0;
}
```

### Компіляція

```bash
g++ -std=c++17 -O3 -march=native opt1_stringview.cpp -o opt1
time ./opt1
```

**Очікуване прискорення:** ~2-3x (тепер ~5-7 секунд).

```bash
echo "Opt1 (string_view): 5.2s (2.9x)" >> results.txt
git add opt1_stringview.cpp results.txt
git commit -m "Opt1: string_view, 5.2s (2.9x faster)"
```

---

## Частина 4: Оптимізація 2 — Integer Math

### Ідея

Температури мають лише 1 знак після коми: `23.5`, `-10.2`.

**Замість `float`:**
```
Зберігаємо 23.5 як int: 235
Зберігаємо -10.2 як int: -102
```

Парсинг стає простим: ігноруємо крапку, читаємо як ціле число.

### Функція парсингу

```cpp
// Швидкий парсинг температури (без stof!)
int parse_temp_int(std::string_view s) {
    int result = 0;
    bool negative = false;
    
    for (char c : s) {
        if (c == '-') {
            negative = true;
        } else if (c == '.') {
            continue;  // Просто пропускаємо крапку
        } else if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        }
    }
    
    return negative ? -result : result;
}
```

### Код opt2_intmath.cpp

```cpp
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <string_view>
#include <limits>
#include "timer.h"

struct Stats {
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::lowest();
    long long sum = 0;  // long long для уникнення переповнення
    int count = 0;
    
    void update(int temp) {
        if (temp < min) min = temp;
        if (temp > max) max = temp;
        sum += temp;
        count++;
    }
    
    double avg() const { return sum / 10.0 / count; }  // Ділимо на 10 тут
};

int parse_temp_int(std::string_view s) {
    int result = 0;
    bool negative = false;
    
    for (char c : s) {
        if (c == '-') negative = true;
        else if (c == '.') continue;
        else if (c >= '0' && c <= '9') result = result * 10 + (c - '0');
    }
    
    return negative ? -result : result;
}

int main() {
    Timer total("Total");
    
    std::unordered_map<std::string, Stats> data;
    std::ifstream file("measurements.txt");
    std::string line;
    
    {
        Timer parse("Parsing");
        while (std::getline(file, line)) {
            size_t pos = line.find(';');
            
            std::string_view station_view(line.data(), pos);
            std::string_view temp_view(line.data() + pos + 1, line.size() - pos - 1);
            
            std::string station(station_view);
            int temp = parse_temp_int(temp_view);  // Швидкий парсинг!
            
            data[station].update(temp);
        }
    }
    
    // Вивід результатів
    std::cout << "\\nResults:\\n";
    for (const auto& [station, stats] : data) {
        std::cout << station << ": min=" << (stats.min / 10.0)
                  << ", max=" << (stats.max / 10.0)
                  << ", avg=" << stats.avg() << "\\n";
    }
    
    return 0;
}
```

### Компіляція

```bash
g++ -std=c++17 -O3 -march=native opt2_intmath.cpp -o opt2
time ./opt2
```

**Очікуване прискорення:** ~8-15x від baseline (~1-2 секунди).

```bash
echo "Opt2 (integer math): 1.8s (8.3x)" >> results.txt
git commit -am "Opt2: integer math, 1.8s (8.3x faster)"
```

---

## Частина 5: Аналіз результатів

### Ваша таблиця

| Метод | Час (сек) | Speedup |
|-------|-----------|---------|
| Baseline (getline + string + stof) | 15.0s | 1.0x |
| Opt1: string_view + unordered_map | 5.2s | 2.9x |
| Opt2: integer math parsing | 1.8s | 8.3x |
| **Target** | <1.0s | >15x |

### Що далі? (Бонус)

1. **Memory Mapping (`mmap`):** Замість `getline`, відобразити файл у пам'ять
2. **Parallel Processing:** Розділити файл на чанки і обробити в кількох потоках
3. **SIMD Instructions:** Використати векторні інструкції CPU

---

## Контрольні питання

1. Чому `string_view` швидший за `string`?

<details markdown="1">
<summary>Відповідь</summary>

`string_view` не виділяє пам'ять і не копіює дані — він просто зберігає вказівник на існуючі дані і їх довжину. Це O(1) операція замість O(N) копіювання.

</details>

2. Як працює парсинг `-10.5` у integer math?

<details markdown="1">
<summary>Відповідь</summary>

```
Символи: - 1 0 . 5
1. Бачимо '-' → negative = true
2. Бачимо '1' → result = 0*10 + 1 = 1
3. Бачимо '0' → result = 1*10 + 0 = 10
4. Бачимо '.' → skip
5. Бачимо '5' → result = 10*10 + 5 = 105
6. Повертаємо: -105 (це -10.5 в integer representation)
```

</details>

3. Чому `unordered_map` швидший за `map`?

<details markdown="1">
<summary>Відповідь</summary>

- `map` — дерево (O(log N) для insert/find)
- `unordered_map` — хеш-таблиця (O(1) в середньому)

Для 10 станцій різниця мала, але для тисяч станцій — критична.

</details>

4. Що ще можна оптимізувати?

<details markdown="1">
<parameter name="Summary">Відповідь

## Джерела

- [Реєстр технічних джерел](../sources.md) — ISO/IEC 14882:2020, cppreference.com
