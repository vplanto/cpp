> **Дисклеймер / Disclaimer**  
> Авторська декларація: Базовий контент, концепцію та архітектуру цього курсу розроблено автором на основі власних лекцій та презентацій. Інструменти штучного інтелекту (LLM) використано виключно як технічний засіб для конвертації форматів (Slides → Markdown) та розгортання текстових тез. Увесь підсумковий текст, архітектурні схеми та код повністю вичитано, верифіковано та затверджено автором.

# Практикум ?: Performance Engineering — "1 Billion Row Challenge" (Lite)
Source https://itnext.io/daily-bit-e-of-c-optimizing-code-to-run-87x-faster-7ef0b5bc64a1

← [Index](index.md)

**Теорія:** [Лекція 19: Performance Engineering](19_complexity_profiling.md)

---

## Наш "продукт" сьогодні

Сьогодні ми не пишемо нову функціональність. Ми робимо існуючу — **швидкою**.
В інженерії є правило: *"Make it work, make it right, make it fast"*. Ви вже вмієте робити "work". Сьогодні час для "fast".

**Легенда:** Ви — Backend Engineer у погодному стартапі. Ваша мережа метеостанцій надсилає 10 мільйонів записів температури щодня. Ваш поточний скрипт обробляє це 2 хвилини. Це занадто довго.
**Задача:** Прискорити обробку даних у **10-50 разів**.

## Експрес-опитування

1.  Скільки часу (приблизно) займає виділення пам'яті (`new`/`malloc`)? Це "дешева" чи "дорога" операція?
2.  Що швидше процесор обробляє: `int` чи `float`?
3.  Якщо у нас є файл на 1 ГБ, чи обов'язково завантажувати його весь у RAM, щоб прочитати?

<details markdown="1">
<summary>Відповіді (Інженерний погляд)</summary>

1.  **Дорога.** Це системний виклик до ОС. Якщо робити це мільйон разів у циклі — програма "помирає".
2.  **Int значно швидше.** Операції з плаваючою крапкою складніші для CPU, плюс можливі помилки точності.
3.  **Ні.** Ми можемо читати шматками (буферизація) або відобразити файл у пам'ять (Memory Mapping).

</details>

---

## Частина 0: Генератор даних (Setup)

Нам потрібні дані. Багато даних. Створіть файл `generator.cpp` і згенеруйте тестовий файл `measurements.txt` на 10 млн рядків.

Формат: `StationName;Temperature` (наприклад: `Kyiv;12.5`).

<details markdown="1">
<summary>Код генератора (Copy/Paste)</summary>

```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iomanip>

int main() {
    const int N_ROWS = 10'000'000; // 10 мільйонів
    std::vector<std::string> stations = {"Kyiv", "Lviv", "Odesa", "Kharkiv", "Dnipro", "London", "Paris", "Berlin", "Tokyo", "NewYork"};
    
    std::ofstream file("measurements.txt");
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist_station(0, stations.size() - 1);
    std::uniform_real_distribution<float> dist_temp(-99.9, 99.9);

    std::cout << "Generating " << N_ROWS << " rows..." << std::endl;
    for(int i = 0; i < N_ROWS; ++i) {
        file << stations[dist_station(rng)] << ";" 
             << std::fixed << std::setprecision(1) << dist_temp(rng) << "\n";
    }
    std::cout << "Done!" << std::endl;
    return 0;
}

```

</details>

---

## Частина 1: The Baseline (Як пише Junior)

Напишемо стандартне рішення: `ifstream`, `std::string`, `std::map`.
Ми використовуємо `Timer` (див. попередні лекції) для заміру.

**Проблеми цього коду:**

1. **Allocation Hell:** Кожен `getline` створює нову `std::string` (виділяє пам'ять).
2. **Copy Hell:** Ми копіюємо дані з файлу в буфер, з буфера в string, зі string у map.
3. **Float Parsing:** `std::stof` — це повільно.

> ⏱ **Завдання:** Запустіть, запишіть час виконання. Це ваш Baseline. (Наприклад: 15.4 сек).

---

## Частина 2: Оптимізація пам'яті (Zero Copy & StringView)

Найшвидший код — той, який не виконується. Найшвидша алокація пам'яті — та, якої не було.

Ми замінимо `std::string` на `std::string_view`.
`string_view` — це просто "погляд" на пам'ять. Він не володіє даними, він просто знає "початок" і "довжину".

**Але є нюанс:** Щоб використовувати `string_view`, дані мусять жити десь у пам'яті. Ми не можемо читати по одному рядку. Ми мусимо прочитати **великий блок** (Chunk) у пам'ять і "нарізати" його через `string_view`.

### Алгоритм "Chunk Reader":

1. Виділити великий буфер (наприклад, 1 МБ) -> `std::vector<char> buffer(1024*1024)`.
2. Читаємо шматок файлу: `file.read(buffer.data(), buffer.size())`.
3. Проходимо по буферу, шукаємо `\n`.
4. Створюємо `string_view` замість копіювання.

<details markdown="1">
<summary>Підказка: Як працює string_view</summary>

```cpp
// BAD (Allocation + Copy)
std::string name = line.substr(0, pos); 

// GOOD (Zero Copy)
// name_view просто вказує на ті ж байти, що і buffer
std::string_view name_view(buffer.data() + start, length); 

```

</details>

---

## Частина 3: Математика фіксованої крапки (Integer Math)

Подивіться на наші температури: `-10.5`, `23.1`. У них завжди 1 знак після коми.
Комп'ютеру важко працювати з `float`. Але йому дуже легко працювати з `int`.

**Ідея:** Зберігати `23.1` як `231`.
Коли ми читаємо число:

1. Ігноруємо крапку `.`
2. Читаємо як ціле число.
3. В кінці просто ділимо на 10 (тільки при виводі!).

**Ваше завдання:** Написати функцію `int parse_temp(string_view s)`, яка вручну перетворює текст на `int`, ігноруючи крапку. Не використовуйте `std::stof` або `stringstream`.

```cpp
// Приклад логіки
// Text: "12.3" -> Int: 123
int custom_atoi(const char* p, const char* end) {
    int res = 0;
    bool neg = (*p == '-');
    if (neg) p++;
    for (; p != end; ++p) {
        if (*p == '.') continue; // Skip dot
        res = res * 10 + (*p - '0');
    }
    return neg ? -res : res;
}

```

---

## Частина 4: Фінальний бій (Map vs Unordered Map)

У нас обмежена кількість станцій (~10-100 унікальних).

1. Спробуйте `std::map` (дерево).
2. Спробуйте `std::unordered_map` (хеш-таблиця).
3. **Бонус для профі:** Оскільки назви станцій повторюються, чи можемо ми уникнути зберігання `std::string` як ключа? (Підказка: Perfect Hashing або просто масив, якщо індекси станцій відомі).

---

## Контрольні результати (KPI)

Ви маєте заповнити цю таблицю своїми даними:

| Метод | Час (сек) | Speedup (X разів) |
| --- | --- | --- |
| Baseline (getline + string + stof) | 15.0s | 1x |
| Optimization 1 (string_view) | ... | ... |
| Optimization 2 (Integer math) | ... | ... |
| **Target** | **< 1.0s** | **> 15x** |

## 🤔 Давайте поміркуємо

1. Чому ми не використали `mmap`? У яких випадках `mmap` буде небезпечним? (Підказка: 32-бітні системи або файли більші за RAM).
2. Чому, коли ми замінили `float` на `int`, програма прискорилась? Справа тільки в математиці, чи ще й в парсингу тексту?
---

## Джерела

- [Реєстр технічних джерел](../sources.md) — ISO/IEC 14882:2020, cppreference.com
