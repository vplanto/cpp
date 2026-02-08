# Практикум 18: Pattern Matching Algorithms — Реалізація та Порівняння

← [Index](index.md)

**Теорія:** [Лекція 25: String Algorithms](25_string_algorithms.md)

---

## Роль: Search Algorithm Engineer

Ви працюєте в компанії, яка розробляє text search engine. Вашнадача — реалізувати три класичні алгоритми пошуку патернів і порівняти їх продуктивність на різних типах даних.

---

## Частина 0: Налаштування середовища

### Структура проекту

```
pattern_matching/
├── Makefile
├── timer.h              # З попередніх практикумів
├── pattern_search.h     # Інтерфейси алгоритмів
├── naive.cpp            # Naive algorithm
├── rabin_karp.cpp       # Rabin-Karp
├── kmp.cpp              # KMP algorithm
├── benchmark.cpp        # Порівняння всіх трьох
└── test_data.txt        # Тестові дані
```

### Створіть timer.h

```cpp
// timer.h (використовуйте з попередніх практикумів)
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

---

## Частина 1: Naive Algorithm

### Завдання

Реалізувати базовий алгоритм пошуку патерна.

### Код naive.cpp

```cpp
#include <vector>
#include <string>
#include <iostream>

std::vector<int> naive_search(const std::string& text, const std::string& pattern) {
    std::vector<int> matches;
    int n = text.length();
    int m = pattern.length();
    
    // Перевіряємо кожну позицію
    for (int i = 0; i <= n - m; i++) {
        bool found = true;
        
        // Порівнюємо патерн посимвольно
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        
        if (found) {
            matches.push_back(i);
        }
    }
    
    return matches;
}

// Тестування
int main() {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABC";
    
    auto matches = naive_search(text, pattern);
    
    std::cout << "Naive Algorithm:\\n";
    std::cout << "Text: " << text << "\\n";
    std::cout << "Pattern: " << pattern << "\\n";
    std::cout << "Matches at positions: ";
    
    for (int pos : matches) {
        std::cout << pos << " ";
    }
    std::cout << "\\n";
    
    return 0;
}
```

### Компіляція та запуск

```bash
g++ -std=c++17 -O3 naive.cpp -o naive
./naive
```

**Очікуваний вивід:**
```
Naive Algorithm:
Text: ABABDABACDABABCABAB
Pattern: ABABC
Matches at positions: 10
```

---

## Частина 2: Rabin-Karp з Rolling Hash

### Завдання

Реалізувати хеш-based пошук з rolling hash оптимізацією.

### Код rabin_karp.cpp

```cpp
#include <vector>
#include <string>
#include <iostream>

const long long P = 31;
const long long M = 1e9 + 9;

long long char_value(char c) {
    return c - 'A' + 1;  // Для великих літер
}

long long compute_hash(const std::string& s) {
    long long hash_value = 0;
    long long p_pow = 1;
    
    for (char c : s) {
        hash_value = (hash_value + char_value(c) * p_pow) % M;
        p_pow = (p_pow * P) % M;
    }
    
    return hash_value;
}

std::vector<int> rabin_karp_search(const std::string& text, const std::string& pattern) {
    std::vector<int> matches;
    int n = text.length();
    int m = pattern.length();
    
    if (m > n) return matches;
    
    // Хеш патерна
    long long pattern_hash = compute_hash(pattern);
    
    // Хеш першого вікна
    std::string first_window = text.substr(0, m);
    long long window_hash = compute_hash(first_window);
    
    // Обчислити p^m для rolling hash
    long long p_pow_m = 1;
    for (int i = 0; i < m; i++) {
        p_pow_m = (p_pow_m * P) % M;
    }
    
    // Перевіряємо всі вікна
    for (int i = 0; i <= n - m; i++) {
        // Якщо хеші збіглися
        if (window_hash == pattern_hash) {
            // Перевірка на колізію
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            
            if (match) {
                matches.push_back(i);
            }
        }
        
        // Rolling hash для наступного вікна
        if (i < n - m) {
            // Видаляємо перший символ
            window_hash = (window_hash - char_value(text[i]) + M) % M;
            
            // Зсуваємо (ділимо на P)
            // Потрібен модульний обернений елемент, спрощено:
            window_hash = (window_hash * 32) % M;  // Inverse of P mod M (approximate)
            
            // Додаємо новий символ
            window_hash = (window_hash + char_value(text[i + m]) * p_pow_m) % M;
        }
    }
    
    return matches;
}

int main() {
    std::string text = "ABABDABACDA BABCABAB";
    std::string pattern = "ABABC";
    
    auto matches = rabin_karp_search(text, pattern);
    
    std::cout << "Rabin-Karp Algorithm:\\n";
    std::cout << "Matches at positions: ";
    for (int pos : matches) {
        std::cout << pos << " ";
    }
    std::cout << "\\n";
    
    return 0;
}
```

---

## Частина 3: KMP з Prefix Function

### Завдання

Реалізувати оптимальний KMP алгоритм.

### Код kmp.cpp

```cpp
#include <vector>
#include <string>
#include <iostream>

// Обчислення prefix function
std::vector<int> compute_prefix_function(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> pi(m, 0);
    
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        
        if (pattern[i] == pattern[j]) {
            j++;
        }
        
        pi[i] = j;
    }
    
    return pi;
}

// KMP search
std::vector<int> kmp_search(const std::string& text, const std::string& pattern) {
    std::vector<int> matches;
    int n = text.length();
    int m = pattern.length();
    
    // Обчислюємо prefix function
    std::vector<int> pi = compute_prefix_function(pattern);
    
    int j = 0;  // Позиція у патерні
    
    for (int i = 0; i < n; i++) {
        // Використовуємо prefix function для зсуву
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        
        if (text[i] == pattern[j]) {
            j++;
        }
        
        // Знайшли повне входження
        if (j == m) {
            matches.push_back(i - m + 1);
            j = pi[j - 1];  // Продовжуємо пошук
        }
    }
    
    return matches;
}

// Візуалізація prefix function
void print_prefix_function(const std::string& pattern) {
    std::vector<int> pi = compute_prefix_function(pattern);
    
    std::cout << "Prefix Function for pattern: " << pattern << "\\n";
    std::cout << "i:    ";
    for (int i = 0; i < pattern.length(); i++) {
        std::cout << i << " ";
    }
    std::cout << "\\n";
    
    std::cout << "char: ";
    for (char c : pattern) {
        std::cout << c << " ";
    }
    std::cout << "\\n";
    
    std::cout << "pi:   ";
    for (int val : pi) {
        std::cout << val << " ";
    }
    std::cout << "\\n\\n";
}

int main() {
    std::string pattern = "ABABC";
    
    // Візуалізація prefix function
    print_prefix_function(pattern);
    
    // Пошук
    std::string text = "ABABDABACDABABCABAB";
    auto matches = kmp_search(text, pattern);
    
    std::cout << "KMP Algorithm:\\n";
    std::cout << "Text: " << text << "\\n";
    std::cout << "Pattern: " << pattern << "\\n";
    std::cout << "Matches at positions: ";
    for (int pos : matches) {
        std::cout << pos << " ";
    }
    std::cout << "\\n";
    
    return 0;
}
```

**Очікуваний вивід:**
```
Prefix Function for pattern: ABABC
i:    0 1 2 3 4
char: A B A B C
pi:   0 0 1 2 0

KMP Algorithm:
Text: ABABDABACDABABCABAB
Pattern: ABABC
Matches at positions: 10
```

---

## Частина 4: Benchmark — Порівняння продуктивності

### Завдання

Порівняти всі три алгоритми на різних типах даних.

### Код benchmark.cpp

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "timer.h"

// Включіть всі три алгоритми

// Генератор тестових даних
std::string generate_worst_case(int n, int m) {
    // Для Naive: текст з багатьма майже-збігами
    std::string text(n, 'A');
    text[n-1] = 'B';  // Один символ відрізняється
    return text;
}

std::string generate_random(int n) {
    std::string text;
    for (int i = 0; i < n; i++) {
        text += char('A' + rand() % 26);
    }
    return text;
}

int main() {
    // Тест 1: Короткий патерн
    {
        std::string text = generate_random(1'000'000);
        std::string pattern = "PATTERN";
        
        std::cout << "=== Test 1: Random text (1M chars), short pattern ===\\n";
        
        {
            Timer t("Naive");
            auto matches = naive_search(text, pattern);
            std::cout << "  Matches found: " << matches.size() << "\\n";
        }
        
        {
            Timer t("Rabin-Karp");
            auto matches = rabin_karp_search(text, pattern);
            std::cout << "  Matches found: " << matches.size() << "\\n";
        }
        
        {
            Timer t("KMP");
            auto matches = kmp_search(text, pattern);
            std::cout << "  Matches found: " << matches.size() << "\\n";
        }
    }
    
    // Tест 2: Найгірший випадок для Naive
    {
        std::string text = generate_worst_case(100'000, 1000);
        std::string pattern(1000, 'A');
        pattern[999] = 'B';
        
        std::cout << "\\n=== Test 2: Worst case for Naive ===\\n";
        
        {
            Timer t("Naive");
            auto matches = naive_search(text, pattern);
            std::cout << "  Matches found: " << matches.size() << "\\n";
        }
        
        {
            Timer t("KMP");
            auto matches = kmp_search(text, pattern);
            std::cout << "  Matches found: " << matches.size() << "\\n";
        }
    }
    
    return 0;
}
```

### Результати (приклад)

| Test Case | Naive | Rabin-Karp | KMP |
|-----------|-------|------------|-----|
| Random 1M, short pattern | 15 ms | 12 ms | 8 ms |
| Worst case (AAAA...B) | 8500 ms | 200 ms | 150 ms |

---

## Частина 5: Real Application — DNA Sequencing

### Завдання

Знайти всі входження генетичного маркера у послідовності ДНК.

```cpp
#include <iostream>
#include <string>
#include <vector>

int main() {
    // Фрагмент ДНК (A, T, G, C)
    std::string dna = "ATCGATCGATCGTAGCTAGCTAGCTGATCGATCGAT";
    
    // Шукаємо маркер
    std::string marker = "ATCG";
    
    auto matches = kmp_search(dna, marker);
    
    std::cout << "DNA Sequence: " << dna << "\\n";
    std::cout << "Marker: " << marker << "\\n";
    std::cout << "Found at positions: ";
    for (int pos : matches) {
        std::cout << pos << " ";
    }
    std::cout << "\\nTotal occurrences: " << matches.size() << "\\n";
    
    return 0;
}
```

---

## Контрольні питання

1. Для якого типу тексту Naive алгоритм може бути швидшим за KMP?

<details markdown="1">
<summary>Відповідь</summary>

Коли патерн **дуже короткий** (2-3 символи) і текст випадковий. Overhead побудови prefix function у KMP може бути більшим за прості порівняння. Також Naive має кращу cache locality (послідовний доступ).

</details>

2. Як перевірити правильність реалізації KMP?

<details markdown="1">
<summary>Відповідь</summary>

1. Порівняти результати з Naive алгоритмом (він простий і очевидно правильний)
2. Тест з патерном, що повторюється: "ABABAB"
3. Перевір prefix function вручну для простого патерна
4. Edge cases: порожній патерн, патерн довший за текст, патерн == текст

</details>

3. Чому KMP швидший за Rabin-Karp у найгіршому випадку?

<details markdown="1">
<summary>Відповідь</summary>

**KMP** має гарантований O(n+m) час — кожен символ тексту обробляється рівно один раз.

**Rabin-Karp** може деградувати до O(n*m) при багатьох колізіях хешів, бо доведеться робити повне порівняння рядків для кожної hash collision.

</details>

4. Як адаптувати ці алгоритми для пошуку кількох патернів одночасно?

<details markdown="1">
<summary>Відповідь</summary>

**Rabin-Karp**: Зберігати хеші всіх патернів у hash set. Порівнювати хеш вікна з усіма патернами за O(1).

**KMP**: Потрібно побудувати **Aho-Corasick automaton** — узагальнення KMP для множини патернів. Це тема для окремої лекції!

</details>
