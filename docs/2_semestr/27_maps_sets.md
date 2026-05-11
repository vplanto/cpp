# Лекція 27: Асоціативні контейнери — Map та Set

[← Лекція 26](26_tree_structures.md) | [Index](index.md)

## Мета

Зрозуміти, як влаштовані **асоціативні контейнери** в C++ STL: `std::map`, `std::unordered_map`, `std::set`, `std::unordered_set`. Навчитися обирати між ними в залежності від задачі. Зрозуміти зв'язок з попередньо вивченими Red-Black Trees та Hash Tables.

> **📚 Матеріал лекції базується на:**  
> Maps.pdf · Sets.pdf

## Експрес-опитування

1. Як отримати елемент зі `std::vector` за ключем (не індексом)?
2. Якщо додати однаковий елемент у `std::set` двічі — що станеться?
3. `std::map` чи `std::unordered_map` — який швидший для пошуку? Чому?

<details markdown="1">
<summary>Інженерна відповідь</summary>

1. Ніяк — вектор індексований тільки числами. Для ключів потрібен `std::map` або `std::unordered_map`.
2. **Нічого** — `std::set` ігнорує дублікати. Розмір не зміниться.
3. `std::unordered_map` — O(1) avg. `std::map` — O(log n). Але `unordered_map` не гарантує порядок та має гірший worst-case.

</details>

---

## Частина 1: std::set — Множина унікальних елементів

### Що таке Set?

**Множина (Set)** — контейнер, що зберігає **унікальні** елементи у **відсортованому** порядку. Математична аналогія з теорії множин.

```
Ключові властивості std::set:
  ✓ Унікальність:   дублікати ігноруються
  ✓ Відсортованість: елементи завжди у порядку (asc)
  ✓ Реалізація:     Red-Black Tree (L26!)
```

**Складність операцій:**

| Операція | Час | Пояснення |
|---------|-----|-----------|
| `insert(x)` | O(log n) | Пошук місця в RB-дереві |
| `erase(x)` | O(log n) | Видалення вузла з RB-дерева |
| `find(x)` | O(log n) | Бінарний пошук у дереві |
| `count(x)` | O(log n) | 0 або 1 (унікальність) |
| `begin()/end()` | O(1) | Вказівник на крайній вузол |
| `size()` | O(1) | |

### Синтаксис та основні операції

```cpp
#include <set>

std::set<int> s;

// Вставка
s.insert(5);
s.insert(2);
s.insert(8);
s.insert(2);  // Ігнорується — дублікат!
s.insert(1);

// Стан: {1, 2, 5, 8} — відсортовано автоматично!

// Пошук
auto it = s.find(5);
if (it != s.end()) {
    std::cout << "Знайдено: " << *it; // 5
}

// count() — зручна перевірка наявності
if (s.count(3) == 0) {
    std::cout << "3 відсутній";
}

// Видалення
s.erase(2);  // {1, 5, 8}

// Обхід (завжди в порядку!)
for (int x : s) {
    std::cout << x << " "; // 1 5 8
}

// Розмір
std::cout << s.size(); // 3
```

### Range queries (діапазонний пошук)

`std::set` завдяки сортуванню підтримує ефективний пошук у діапазоні:

```cpp
std::set<int> s = {1, 3, 5, 7, 9, 11, 13};

// lower_bound(x) — перший елемент >= x
auto lo = s.lower_bound(5);  // вказує на 5

// upper_bound(x) — перший елемент > x
auto hi = s.upper_bound(9);  // вказує на 11

// Елементи в діапазоні [5, 9]:
for (auto it = lo; it != hi; ++it) {
    std::cout << *it << " "; // 5 7 9
}
```

### Коли використовувати std::set?

- ✅ Потрібна **автоматична сортованість**
- ✅ Потрібні **range-based queries** (знайти всі елементи від A до B)
- ✅ **Дедуплікація** (видалення дублікатів з колекції)
- ❌ Не підходить, якщо потрібен доступ за індексом

---

## Частина 2: std::unordered_set — Хеш-таблиця

### Що всередині?

`std::unordered_set` побудований на **хеш-таблиці** замість дерева. Відсутній порядок, зате O(1) у середньому.

```
Порівняння std::set vs std::unordered_set:

std::set (RB-Tree):
  {1, 2, 5, 8} → завжди відсортовано
  insert/find: O(log n)

std::unordered_set (Hash Table):
  {8, 1, 5, 2} → порядок довільний (залежить від хешу)
  insert/find: O(1) average, O(n) worst case
```

```cpp
#include <unordered_set>

std::unordered_set<std::string> us;

us.insert("apple");
us.insert("banana");
us.insert("cherry");
us.insert("apple");   // дублікат, ігнорується

std::cout << us.count("banana"); // 1 (є)
std::cout << us.count("mango");  // 0 (немає)

us.erase("banana");

// ВАЖЛИВО: порядок обходу НЕ гарантований!
for (const auto& s : us) {
    std::cout << s << " "; // може бути будь-який порядок
}
```

### Коли що обирати?

| Критерій | `std::set` | `std::unordered_set` |
|---------|-----------|---------------------|
| **Порядок** | Відсортований | Немає |
| **Пошук** | O(log n) | O(1) avg |
| **Range queries** | ✅ Підтримує | ❌ Ні |
| **Worst-case** | O(log n) гарантовано | O(n) при колізіях |
| **Пам'ять** | Менше | Більше (load factor) |
| **Коли** | Потрібен порядок або діапазони | Тільки пошук/вставка |

---

## Частина 3: std::map — Словник (ключ → значення)

### Що таке Map?

**Map (Асоціативний масив / Словник)** — контейнер, що зберігає пари **ключ → значення**. Кожен ключ унікальний. Ключі зберігаються у **відсортованому** порядку.

```
std::map — це std::set, але кожен елемент має "прикріплене" значення.

Колекція: { "Alice" → 95, "Bob" → 87, "Charlie" → 92 }
Ключ: std::string (ім'я)
Значення: int (оцінка)
```

**Складність:** Ідентична `std::set` — O(log n) для пошуку/вставки/видалення.

### Синтаксис та ключові операції

```cpp
#include <map>

std::map<std::string, int> scores;

// Вставка — 3 способи:
scores["Alice"] = 95;                         // 1. operator[] (вставляє якщо немає!)
scores.insert({"Bob", 87});                   // 2. insert з pair
scores.emplace("Charlie", 92);                // 3. emplace (ефективніше)

// УВАГА: operator[] - небезпечний при читанні!
// Якщо ключ відсутній — він АВТОМАТИЧНО ДОДАЄТЬСЯ з value = 0
auto val = scores["Dave"];  // Тепер Dave є в map з оцінкою 0!
std::cout << scores.size(); // 4, не 3!

// Безпечний пошук:
auto it = scores.find("Alice");
if (it != scores.end()) {
    std::cout << it->first << ": " << it->second; // Alice: 95
}

// Перевірка наявності (без вставки!):
if (scores.count("Bob") > 0) {
    std::cout << "Bob exists";
}

// Видалення
scores.erase("Dave"); // видаляємо випадково доданий

// Обхід (ключі завжди відсортовані!)
for (const auto& [name, score] : scores) {  // C++17 structured binding
    std::cout << name << " → " << score << "\n";
    // Alice → 95
    // Bob → 87
    // Charlie → 92
}
```

> [!WARNING]
> **Класична пастка:** `map["key"]` при **читанні** невідомого ключа **вставляє** його з нульовим значенням! Використовуйте `find()` або `count()` для безпечної перевірки.

### Практичний приклад: Підрахунок частоти слів

```cpp
#include <map>
#include <string>
#include <sstream>

std::map<std::string, int> wordCount(const std::string& text) {
    std::map<std::string, int> freq;
    std::istringstream iss(text);
    std::string word;
    
    while (iss >> word) {
        freq[word]++;  // якщо слова нема — створює з 0, потім +1
    }
    return freq;
}

auto freq = wordCount("the cat sat on the mat the cat");
// { "cat":2, "mat":1, "on":1, "sat":1, "the":3 } — відсортовано!

for (auto& [word, count] : freq) {
    std::cout << word << ": " << count << "\n";
}
```

---

## Частина 4: std::unordered_map — Хеш-Map

### Різниця з std::map

`std::unordered_map` — це `std::map` з хеш-таблицею замість RB-дерева.

```cpp
#include <unordered_map>

std::unordered_map<std::string, int> phoneBook;

phoneBook["Alice"] = 380501234567;
phoneBook["Bob"]   = 380671234567;

// Пошук — O(1) середньому!
if (phoneBook.count("Alice")) {
    std::cout << phoneBook["Alice"]; // 380501234567
}

// Обхід — порядок НЕ гарантований:
for (auto& [name, phone] : phoneBook) {
    std::cout << name << ": " << phone << "\n";
    // Може бути Bob перед Alice!
}
```

### Порівняльна таблиця всіх 4 контейнерів

| Контейнер | Унікальність | Порядок | Пошук | Структура |
|-----------|-------------|---------|-------|-----------|
| `std::set` | ✅ ключів | ✅ відсортований | O(log n) | RB-Tree |
| `std::unordered_set` | ✅ ключів | ❌ | O(1) avg | Hash Table |
| `std::map` | ✅ ключів | ✅ відсортований за ключем | O(log n) | RB-Tree |
| `std::unordered_map` | ✅ ключів | ❌ | O(1) avg | Hash Table |

---

## Частина 5: Вибір контейнера — Дерево рішень

```
Потрібне зберігання пар (ключ, значення)?
│
├── НІ  → Потрібна унікальність?
│         ├── НІ  → std::vector або std::list
│         └── ТАК → Потрібен відсортований порядок?
│                   ├── ТАК → std::set
│                   └── НІ  → std::unordered_set  (швидший)
│
└── ТАК → Потрібен відсортований порядок або range queries?
          ├── ТАК → std::map
          └── НІ  → std::unordered_map  (швидший)
```

---

## Практичне застосування

- [Практикум 14: Search Engine](p14_search_engine.md) — побудова пошукового індексу `word → {files}` за допомогою `std::unordered_map`.
- [Практикум 15: Pathfinder](p15_pathfinder.md) — пошук шляху в лабіринті (використання `unordered_map` та `unordered_set` для відстеження стану клітинок).

---

## Контрольні питання

1. Чому `scores["Dave"]` у `std::map` додає новий запис, а `scores.find("Dave")` — ні?

<details markdown="1">
<summary>Відповідь</summary>

`operator[]` — це "доступ або вставка". Якщо ключ відсутній, він конструює новий елемент з default value (0 для int). `find()` лише шукає і повертає `end()` якщо не знайдено, без жодної вставки.

</details>

2. Навіщо використовувати `std::set` замість `std::unordered_set`, якщо у другого краща складність?

<details markdown="1">
<summary>Відповідь</summary>

`std::set` підходить коли: потрібен **відсортований порядок** (наприклад, вивести в алфавітному порядку), потрібні **range queries** (`lower_bound`, `upper_bound`), або потрібна **гарантована** O(log n) (без worst-case O(n) при хеш-колізіях).

</details>

3. Як ефективно знайти 5 найпопулярніших слів у тексті?

<details markdown="1">
<summary>Відповідь</summary>

1. Підрахуємо частоту через `std::unordered_map<string, int>` — O(n)
2. Завантажимо пари (count, word) в `std::priority_queue` розміром 5 — O(n log 5) = O(n)
3. Витягнемо top-5 з черги — O(5 log 5) = O(1)

Загальна складність: O(n), набагато краще ніж сортування O(n log n).

</details>
