---
title: "Лекція 24 — Performance Deep Dive"
semester: 2
type: lecture
hours: 2
prerequisites: ["19_complexity_profiling"]
---

> **Дисклеймер / Disclaimer**  
> Авторська декларація: Базовий контент, концепцію та архітектуру цього курсу розроблено автором на основі власних лекцій та презентацій. Інструменти штучного інтелекту (LLM) використано виключно як технічний засіб для конвертації форматів (Slides → Markdown) та розгортання текстових тез. Увесь підсумковий текст, архітектурні схеми та код повністю вичитано, верифіковано та затверджено автором.

# Лекція 24: Performance Deep Dive — Профілювання та Оптимізація

[← Лекція 23](23_optimization_dp.md) | [Index](index.md)

## Мета

Навчитися **вимірювати** продуктивність коду, знаходити вузькі місця та оптимізувати їх. Розуміти, як залізо (CPU, кеш, пам'ять) впливає на швидкість програм. Вміти використовувати інструменти профілювання.

## Експрес-опитування

1. Що швидше: прочитати 1 МБ даних послідовно чи прочитати 1 МБ даних стрибками по 4 байти у випадкових місцях?
2. Якщо ваша програма працює 10 секунд, але ви не знаєте, де саме вона витрачає час, що робити першим?
3. Чи варто оптимізувати код до того, як ви виміряли його швидкість?

<details markdown="1">
<summary>Інженерна відповідь</summary>

1. **Послідовно у ~100 разів швидше.** CPU передбачає послідовне читання і завантажує дані в кеш наперед (prefetching). Випадковий доступ викликає cache misses.
2. **Виміряти час виконання кожної функції** за допомогою профайлера (perf, gprof). Оптимізувати треба тільки найповільніші 20% коду (Pareto principle).
3. **Ні.** "Premature optimization is the root of all evil" (Knuth). Спочатку напишіть код, що працює. Потім виміряйте. Потім оптимізуйте тільки там, де це дійсно потрібно.

</details>

---

## Частина 1: Реальність заліза — Memory Hierarchy

### Що студенти думають:
```
CPU ←→ RAM
```

### Що насправді:
```
CPU ←→ Registers ←→ L1 Cache ←→ L2 Cache ←→ L3 Cache ←→ RAM ←→ Disk
```

### Аналогія відстаней (Human Scale)

Якщо **1 CPU цикл (0.3 нс) = 1 секунда** життя людини:

| Подія | Реальний час | Людський масштаб |
|-------|--------------|------------------|
| **1 CPU Cycle** | 0.3 ns | **1 секунда** |
| **L1 Cache** | 1 ns | **3 секунди** (взяти книгу зі столу) |
| **L2 Cache** | 4 ns | **12 секунд** (дійти до полиці) |
| **L3 Cache** | 10 ns | **30 секунд** (спуститися сходами) |
| **RAM Access** | 100 ns | **5 хвилин** (сходити за кавою) |
| **SSD Read** | 100 μs | **4 дні** (поїздка Київ-Одеса) |
| **HDD Read** | 10 ms | **1 рік** (піша подорож навколо світу) |

**Висновок:** Кожен раз, коли CPU чекає дані з RAM, він "піде пити каву на 5 хвилин". Ось чому `std::vector` (суцільна пам'ять) майже завжди швидший за `std::list` (розкидані вузли).

---

## Частина 2: Вимірювання — Timer Class (для початківців)

### Крок 1: Створіть timer.h

```cpp
// timer.h - Клас для вимірювання часу виконання коду
#pragma once
#include <chrono>
#include <iostream>
#include <string>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::string name;

public:
    // Конструктор: запам'ятовує час початку
    Timer(const std::string& timer_name = "Timer") : name(timer_name) {
        start_time = std::chrono::high_resolution_clock::now();
    }
    
    // Деструктор: автоматично виводить час виконання
    ~Timer() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        std::cout << "[" << name << "] " << duration.count() << " ms\\n";
    }
    
    // Ручне вимірювання без автовиводу
    long long elapsed_ms() const {
        auto current = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            current - start_time).count();
    }
};
```

### Крок 2: Використання

```cpp
#include "timer.h"
#include <vector>

int main() {
    {
        Timer t("Vector fill");
        std::vector<int> vec;
        for (int i = 0; i < 10'000'000; i++) {
            vec.push_back(i);
        }
    } // Автоматично виведе: [Vector fill] 250 ms
    
    {
        Timer t("Vector with reserve");
        std::vector<int> vec;
        vec.reserve(10'000'000); // Резервуємо пам'ять заздалегідь
        for (int i = 0; i < 10'000'000; i++) {
            vec.push_back(i);
        }
    } // [Vector with reserve] 80 ms — 3x швидше!
}
```

**Чому швидше з `reserve()`?** Без резервування вектор періодично перевиділяє пам'ять і копіює всі елементи. З `reserve()` пам'ять виділяється один раз.

---

## Частина 3: Compiler Flags — Турбо для вашого коду

### Що таке compiler flags?

Це інструкції компілятору, **як** перетворювати ваш код у машинний код.

### Основні прапорці оптимізації

```bash
# 1. Debug build (без оптимізацій, зручно для налагодження)
g++ -g -O0 my_program.cpp -o my_program_debug

# 2. Release build (максимальна швидкість)
g++ -O3 -march=native my_program.cpp -o my_program_fast

# 3. З попередженнями (рекомендовано завжди)
g++ -Wall -Wextra -O3 my_program.cpp -o my_program
```

### Таблиця прапорців

| Прапорець | Що робить | Коли використовувати |
|-----------|-----------|---------------------|
| `-g` | Додає debug символи | Розробка, налагодження з gdb |
| `-O0` | Без оптимізацій | Debug (передбачувана поведінка) |
| `-O1` | Базова оптимізація | Перший крок оптимізації |
| `-O2` | Рекомендована оптимізація | **Production builds** |
| `-O3` | Агресивна оптимізація | Performance-critical код |
| `-march=native` | Використовує інструкції вашого CPU | Максимальна швидкість |
| `-Wall -Wextra` | Увімкнути попередження | **Завжди** |
| `-std=c++17` | Стандарт C++ | Залежно від проекту |

### Приклад різниці

```cpp
#include "timer.h"
#include <cmath>

int main() {
    Timer t;
    double sum = 0;
    for (int i = 0; i < 100'000'000; i++) {
        sum += std::sqrt(i);
    }
}
```

**Результати:**
- Компіляція з `-O0`: **5000 ms**
- Компіляція з `-O3`: **800 ms** (6x швидше!)
- Компіляція з `-O3 -march=native`: **600 ms** (8x швидше!)

---

## Частина 4: Makefile для початківців

### Крок 1: Створіть файл Makefile

```makefile
# Компілятор
CXX = g++

# Прапорці для всіх збірок
CXXFLAGS = -std=c++17 -Wall -Wextra

# Вихідний файл
TARGET = program

# Debug збірка
debug: CXXFLAGS += -g -O0
debug: $(TARGET)

# Release збірка
release: CXXFLAGS += -O3 -march=native
release: $(TARGET)

# Компіляція
$(TARGET): main.cpp
\t$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

# Очищення
clean:
\trm -f $(TARGET)

.PHONY: debug release clean
```

### Крок 2: Використання

```bash
# Debug збірка (для розробки)
make debug
./program

# Release збірка (для вимірювань)
make release
./program

# Очистити
make clean
```

---

## Частина 5: Profiling з perf (Linux)

### Що таке perf?

`perf` — це профайлер від Linux Kernel, який показує, де ваша програма витрачає час.

### Встановлення

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install linux-tools-common linux-tools-generic
```

**WSL2:**
```bash
# perf має обмеження на WSL2
# Альтернатива: використовуйте std::chrono або Docker
```

**Docker (рекомендовано для однакового середовища):**
```bash
docker run -it --privileged ubuntu:22.04 /bin/bash
apt-get update && apt-get install -y build-essential linux-tools-generic
```

### Використання perf

#### Сценарій 1: Загальна статистика

```bash
# Компілюємо з оптимізаціями
g++ -O3 -g my_program.cpp -o my_program

# Запускаємо з perf
perf stat -d ./my_program
```

**Що дивитися у виводі:**
- **task-clock**: Скільки часу CPU працював (ms)
- **instructions**: Скільки інструкцій виконано
- **IPC (instructions per cycle)**: Якщо < 1.0 → CPU чекає пам'ять
- **L1-dcache-load-misses**: Промахи кешу (чим менше, тим краще)

#### Сценарій 2: Які функції повільні?

```bash
# Записуємо профіль
perf record -g ./my_program

# Дивимося звіт
perf report
```

**Вивід покаже:**
```
Overhead  Command  Shared Object     Symbol
  45.00%  program  program           [.] std::vector::push_back
  30.00%  program  program           [.] compute_sum
  15.00%  program  libc.so.6         [.] malloc
```

**Інтерпретація:** 45% часу йде на `push_back` → треба використати `reserve()`.

---

## Частина 6: Performance Anti-Patterns

### 1. Copy Hell (зайві копіювання)

**BAD:**
```cpp
void process(std::string data) {  // Копіюємо всю строку!
    // ...
}

std::string big_text = load_file();  // 10 MB
process(big_text);  // Копіювання 10 MB
```

**GOOD:**
```cpp
void process(const std::string& data) {  // Передаємо по посиланню
    // ...
}

// Або ще краще (C++17):
void process(std::string_view data) {  // Без копіювання взагалі
    // ...
}
```

> **💡 Modern C++ Note: std::string_view (C++17)**
>
> `std::string_view` — це легка обгортка навколо послідовності символів (pointer + length).
> 
> **Чим відрізняється від `const std::string&`:**
> - `const std::string&` — посилання на існуючий `std::string` об'єкт
> - `std::string_view` — може вказувати на **будь-яку** послідовність символів: `std::string`, C-string, частину буфера
>
> **Переваги:**
> ```cpp
> std::string str = "Hello, World!";
> std::string_view view1 = str;           // OK
> std::string_view view2 = "C-string";    // OK
> std::string_view view3(str.data(), 5);  // "Hello" — жодного копіювання!
> ```
>
> **Обережно! Lifetime:**
> ```cpp
> std::string_view get_view() {
>     std::string temp = "Danger!";
>     return temp;  // ❌ Dangling pointer! temp знищено
> }
> ```
>
> **Коли використовувати:**
> - Функції, що читають рядки (не модифікують)
> - Парсинг (створення "вікон" у великий буфер)
> - Performance-critical код (уникаємо копіювання)
>
> **Не використовувати:**
> - Якщо треба зберігати рядок (використайте `std::string`)
> - Якщо lifetime даних неочевидний

### 2. Allocation Hell (виділення пам'яті у циклі)

**BAD:**
```cpp
for (int i = 0; i < 1000; i++) {
    std::vector<int> temp;  // Виділяємо пам'ять 1000 разів!
    temp.push_back(i);
}
```

**GOOD:**
```cpp
std::vector<int> temp;
temp.reserve(1000);  // Виділяємо один раз

for (int i = 0; i < 1000; i++) {
    temp.clear();  // Очищаємо, але не звільняємо пам'ять
    temp.push_back(i);
}
```

### 3. IO Hell (flush на кожен рядок)

**BAD:**
```cpp
for (int i = 0; i < 1'000'000; i++) {
    std::cout << i << std::endl;  // endl робить flush → повільно!
}
```

**GOOD:**
```cpp
for (int i = 0; i < 1'000'000; i++) {
    std::cout << i << '\\n';  // Просто новий рядок
}
// Flush відбудеться автоматично в кінці
```

---

## Частина 7: Workflow оптимізації

1. **Make it work** — спочатку напишіть код, що працює правильно
2. **Measure** — виміряйте з Timer або perf
3. **Find bottleneck** — знайдіть найповільніше місце (80/20 rule)
4. **Optimize** — оптимізуйте тільки це місце
5. **Verify** — виміряйте знову, перевірте, що не зламали функціональність
6. **Repeat** — якщо треба, повторіть

**Золоте правило:** Не оптимізуйте те, що ви не виміряли!

---

## Практичне застосування

**Див.:** [Практикум 17: 1 Billion Row Challenge](p17_billion_row.md) — екстремальна оптимізація обробки даних (прискорення у 50+ разів).

---

## Контрольні питання

1. Чому `std::vector` зазвичай швидший за `std::list`, навіть коли треба вставляти елементи в середину?

<details markdown="1">
<summary>Відповідь</summary>

**Cache locality.** `std::vector` тримає всі дані поруч у пам'яті → CPU завантажує їх великими блоками (cache lines) → швидко. `std::list` розкидує вузли по всій купі → кожен `node->next` може викликати cache miss → повільно. Навіть з урахуванням зсувів елементів, `vector` часто перемагає завдяки кешу.

</details>

2. Ви компілюєте програму з `-O0` і вона працює 10 секунд. З `-O3` вона працює 2 секунди. Чому таке прискорення?

<details markdown="1">
<summary>Відповідь</summary>

Компілятор з `-O3` робить:
- **Loop unrolling** (розгортання циклів)
- **Inline функцій** (вбудовування малих функцій)
- **Vectorization** (SIMD інструкції для паралельної обробки)
- **Dead code elimination** (видалення невикористаного коду)

Це може дати прискорення до 10x для обчислювально-інтенсивного коду.

</details>

3. Як дізнатися, яка функція у вашій програмі найповільніша?

<details markdown="1">
<summary>Відповідь</summary>

Використати профайлер:
```bash
perf record -g ./my_program
perf report
```

Альтернативно, можна вручну обгорнути кожну функцію у Timer, але це трудомістко.

</details>

4. Чому `reserve()` для `std::vector` може прискорити код у кілька разів?

<details markdown="1">
<summary>Відповідь</summary>

Без `reserve()`, коли вектор переповнюється, він:
1. Виділяє новий блок пам'яті (зазвичай x2)
2. Копіює ВСІ елементи туди
3. Видаляє старий блок

Для 1 мільйона елементів це може статися ~20 разів. З `reserve(1'000'000)` виділення відбувається **один раз**.

</details>
---

## Джерела

- [Реєстр технічних джерел](../sources.md) — ISO/IEC 14882:2020, cppreference.com
