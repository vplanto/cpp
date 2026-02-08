# Практикум 14: Search Engine — Індексація файлів за допомогою Hash Maps

← [Index](index.md)

**Теорія:** [Лекція 21: Sorting Algorithms](21_sorting_algorithms.md)

---

## Роль: Search Engine Developer

Ви розробляєте "Google Lite" — локальний пошуковик для текстових файлів. Користувач вводить ключове слово, і ви миттєво знаходите всі файли, де воно зустрічається.

**Головна ідея:** Створити **інвертований індекс** (Inverted Index) — структуру даних, яка зіставляє кожне слово зі списком файлів, де воно зустрічається.

## Code Style Convention

Продовжуємо суворі правила:

1. **Classes:** `PascalCase` (`SearchEngine`, `Document`).
2. **Functions/Methods:** `camelCase` (`buildIndex`, `searchByKeyword`).
3. **Variables:** `snake_case` (`file_name`, `word_count`).
4. **Constants:** `UPPER_SNAKE_CASE` (`MAX_RESULTS`).

---

## Частина 1: Setup — структура проекту

```
search_engine/
├── data/              # Текстові файли для індексації
│   ├── doc1.txt
│   ├── doc2.txt
│   └── doc3.txt
├── search_engine.h    # Інтерфейс SearchEngine
├── search_engine.cpp  # Реалізація
└── main.cpp           # Точка входу
```

**Створіть тестові файли:**

`data/doc1.txt`:
```
C++ is a powerful programming language.
It supports object-oriented programming.
```

`data/doc2.txt`:
```
Python is easy to learn.
C++ requires more practice.
```

`data/doc3.txt`:
```
Object-oriented programming is popular.
Both C++ and Python support it.
```

---

## Частина 2: Токенізація — розбиття тексту на слова

**Завдання:** Розбити текст на окремі слова (tokens) і привести їх до нижнього регістру.

```cpp
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// Функція для токенізації тексту
std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string word;
    
    while (ss >> word) {
        // Видаляємо розділові знаки
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        
        // Приводимо до нижнього регістру
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        if (!word.empty()) {
            tokens.push_back(word);
        }
    }
    
    return tokens;
}
```

**Тест:**
```cpp
std::string text = "C++ is a powerful programming language.";
auto words = tokenize(text);
// Результат: ["c++", "is", "a", "powerful", "programming", "language"]
```

---

## Част��на 3: Інвертований індекс

**Структура даних:**
```cpp
std::unordered_map<std::string, std::set<std::string>> inverted_index;
```

- **Ключ:** Слово (наприклад, "programming").
- **Значення:** Множина файлів, де зустрічається це слово (наприклад, {"doc1.txt", "doc2.txt"}).

**Чому `std::set`?** Щоб уникнути дублікатів файлів і автоматично тримати їх відсортованими.

### Побудова індексу

```cpp
#include <unordered_map>
#include <set>
#include <fstream>
#include <filesystem>

class SearchEngine {
private:
    std::unordered_map<std::string, std::set<std::string>> index;

public:
    void buildIndex(const std::string& directory_path) {
        for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
            if (entry.is_regular_file()) {
                std::string file_name = entry.path().filename().string();
                indexFile(file_name, entry.path().string());
            }
        }
    }

private:
    void indexFile(const std::string& file_name, const std::string& file_path) {
        std::ifstream file(file_path);
        std::string line;
        
        while (std::getline(file, line)) {
            auto words = tokenize(line);
            
            for (const auto& word : words) {
                index[word].insert(file_name); // Додаємо файл до списку
            }
        }
    }
};
```

---

## Частина 4: Пошук за ключовим словом

**Завдання:** Знайти всі файли, де зустрічається слово.

```cpp
std::set<std::string> search(const std::string& keyword) {
    std::string lower_keyword = keyword;
    std::transform(lower_keyword.begin(), lower_keyword.end(), 
                   lower_keyword.begin(), ::tolower);
    
    if (index.find(lower_keyword) != index.end()) {
        return index[lower_keyword];
    }
    
    return {}; // Порожня множина, якщо слово не знайдено
}
```

**Використання:**
```cpp
SearchEngine engine;
engine.buildIndex("data/");

auto results = engine.search("programming");
// Результат: {"doc1.txt", "doc3.txt"}

for (const auto& file : results) {
    std::cout << file << "\\n";
}
```

---

## Частина 5: Розширена функціональність

### 5.1. Статистика індексу

Додайте метод для виводу кількості унікальних слів та файлів:

```cpp
void printStats() const {
    std::cout << "Total unique words: " << index.size() << "\\n";
    
    std::set<std::string> all_files;
    for (const auto& [word, files] : index) {
        all_files.insert(files.begin(), files.end());
    }
    
    std::cout << "Total files indexed: " << all_files.size() << "\\n";
}
```

### 5.2. Пошук за кількома словами (AND логіка)

Знайти файли, де зустрічаються **всі** слова з запиту.

```cpp
std::set<std::string> searchMultiple(const std::vector<std::string>& keywords) {
    if (keywords.empty()) return {};
    
    // Починаємо з результатів першого слова
    std::set<std::string> result = search(keywords[0]);
    
    // Перетин з результатами інших слів
    for (size_t i = 1; i < keywords.size(); i++) {
        std::set<std::string> current = search(keywords[i]);
        std::set<std::string> intersection;
        
        std::set_intersection(result.begin(), result.end(),
                              current.begin(), current.end(),
                              std::inserter(intersection, intersection.begin()));
        
        result = intersection;
    }
    
    return result;
}
```

**Приклад:**
```cpp
auto results = engine.searchMultiple({"c++", "programming"});
// Знайде файли, де є обидва слова
```

---

## Бонус: TF-IDF Ranking

**Завдання:** Ранжувати файли за релевантністю (як Google).

**TF-IDF (Term Frequency - Inverse Document Frequency):**
- **TF:** Як часто слово зустрічається у документі.
- **IDF:** Наскільки рідкісне слово у всій колекції.

**Formula:**
```
TF-IDF(слово, документ) = TF(слово, документ) * IDF(слово)
IDF(слово) = log(Total Documents / Documents with Word)
```

**Реалізація (спрощена):**

```cpp
#include <cmath>
#include <map>

double calculateTFIDF(const std::string& word, const std::string& file_name) {
    // TF: кількість разів слово зустрічається у файлі
    int word_count = countWordInFile(word, file_name);
    int total_words = getTotalWordsInFile(file_name);
    double tf = static_cast<double>(word_count) / total_words;
    
    // IDF: рідкісність слова
    int docs_with_word = index[word].size();
    int total_docs = getTotalDocuments();
    double idf = std::log(static_cast<double>(total_docs) / docs_with_word);
    
    return tf * idf;
}
```

---

## Контрольні питання (Definition of Done)

1. Яка складність побудови індексу, якщо у нас N файлів і кожен має в середньому M слів?

<details markdown="1">
<summary>Відповідь</summary>

**O(N * M).** Для кожного файлу ми читаємо M слів і додаємо їх до hash map (O(1) на вставку). Загалом: N файлів * M слів = O(N*M).

</details>

2. Чому ми використовуємо `std::set` для зберігання файлів, а не `std::vector`?

<details markdown="1">
<summary>Відповідь</summary>

`std::set` автоматично:
1. Уникає дублікатів (якщо слово зустрічається у файлі кілька разів, файл додається лише раз).
2. Тримає файли відсортованими.
3. Швидкий пошук для операцій типу set_intersection.

</details>

3. Як адаптувати пошук для підтримки OR логіки (знайти файли, де є хоча б одне слово)?

<details markdown="1">
<summary>Відповідь</summary>

Замість `set_intersection` використати `set_union`:

```cpp
std::set<std::string> searchOR(const std::vector<std::string>& keywords) {
    std::set<std::string> result;
    
    for (const auto& keyword : keywords) {
        auto current = search(keyword);
        result.insert(current.begin(), current.end()); // Об'єднання
    }
    
    return result;
}
```

</details>

4. Чому TF-IDF допомагає знайти релевантніші документи?

<details markdown="1">
<summary>Відповідь</summary>

**TF** показує, наскільки документ "про" це слово (чим частіше — тим релевантніше).
**IDF** зменшує вагу дуже поширених слів (наприклад, "the", "and"), які зустрічаються скрізь і не містять інформації. Рідкісні слова отримують більшу вагу.

</details>
