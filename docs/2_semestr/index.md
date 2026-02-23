# Основи програмування (Семестр 2)
## C++ Engineering: Architecture, Modern Tooling & Performance

Другий семестр курсу трансформує знання синтаксису C++ у навички **інженерного проектування**.

**Фокус семестру:**
1. **Архітектура:** Перехід від написання функцій до проектування систем (OOP, SOLID, API Design).
2. **Performance:** Розуміння вартості абстракцій. Як залізо (CPU Caches, Branch Prediction) впливає на вибір структур даних.
3. **Algorithmic Thinking:** Глибоке розуміння того, що **"Алгоритм = Структура даних"**. Вибір правильного контейнера важливіший за мікро-оптимізації.

Ми переходимо від питання *"Як це написати?"* до питань *"Як це спроектувати?"* та *"Чому це працює повільно?"*.

> **Довідник:** [Глосарій: Модель пам'яті та середовище виконання C++](00_memory_model_glossary.md) — формальні визначення термінів для студентів з математичним бекґраундом.

---

## Блок 1: Об'єктно-орієнтована архітектура (OOP Core)

Ми вчимося керувати складністю, захищати дані (Інваріанти) та автоматизувати управління ресурсами (RAII).

| # | Матеріал | Ключова ідея |
|---|----------|--------------|
| Лекція 13 | [Філософія ООП: Інкапсуляція та Інваріанти](13_oop_philosophy.md) | Чому `struct` недостатньо? Як перетворити "мішок з даними" на "розумний об'єкт". |
| Лекція 14 | [Життєвий цикл (RAII), Анатомія методів та Структура проекту](14_raii_lifecycle.md) | Конструктори, Деструктори та автоматичне керування файлами. Розділення на `.h` та `.cpp`. |
| Лекція 15 | [Правило Трьох, Deep Copy та Перевантаження Операторів](15_rule_of_three.md) | Чому `a = b` може вбити вашу програму? Shallow Copy vs Deep Copy. |
| Лекція 16 | [Спадкування, Поліморфізм та V-Table](16_inheritance_polymorphism.md) | Ціна віртуальних функцій. Як працює динамічна диспетчеризація "під капотом". |
| Практикум 9 | [Проектуємо "Monobank Lite" (Вступ в ООП)](p09_oop_bank.md) | Перший клас, інкапсуляція, Code Style. |
| Практикум 10 | [RAII та Logger — "Чорний ящик" для банку](p10_raii_logger.md) | Автоматичне закриття файлів та логування. |

---

## Блок 2: Modern C++ & Generics

Ми переходимо від "C з класами" до сучасного C++. Вчимося писати код, який працює з будь-якими типами даних і робить це ефективно.

| # | Матеріал | Ключова ідея |
|---|----------|--------------|
| Лекція 17 | [Узагальнене програмування (Generics) та Перевантаження Операторів](17_generics_operators.md) | Templates: як написати код один раз для `int`, `double` та `UserType`. Магія `operator+`. |
| Лекція 18 | [Modern C++ — Move Semantics, Smart Pointers та Lambdas](18_modern_cpp_move_smart.md) | Як прискорити код, "крадучи" ресурси (`std::move`). Чому `new`/`delete` більше не потрібні. |
| Практикум 11 | [Matrix Engine (Templates & Operators)](p11_generic_matrix.md) | Створення математичної бібліотеки: `C = A * B`. |

---

## Блок 3: Performance Engineering & Data Structures

Ми перестаємо вірити інтуїції і починаємо вірити цифрам. Вивчаємо, як залізо (CPU Caches) впливає на вибір алгоритмів.

| # | Матеріал | Ключова ідея |
|---|----------|--------------|
| Лекція 19 | [Performance Engineering — Big O та Брехня CPU](19_complexity_profiling.md) | Чому доступ до RAM — це "5 хвилин перерви" для процесора. Вчимося бачити $O(N^2)$. |
| Лекція 20 | [Лінійні структури — Битва Vector vs List](20_lists_vector.md) | Анатомія `std::vector` та `std::list`. Чому Linked List — це "вбивця кешу". |
| Практикум 12 | [Performance Lab — Оптимізація коду (x10 Speedup)](p12_performance_lab.md) | Профілювання, `reserve()`, прапорці компілятора. |
| Практикум 13 | [Algorithms & Good Taste (Torvalds Edition)](p13_algorithms_and_taste.md) | Алгоритмічна задача про потяг та робота з подвійними вказівниками. |

---

## Блок 4: Фундаментальні алгоритми (Applied CS)

Класика Computer Science через призму практичного застосування.

| # | Матеріал | Ключова ідея |
|---|----------|--------------|
| Лекція 21 | [Алгоритми сортування (Sorting Deep Dive)](21_sorting_algorithms.md) | QuickSort, MergeSort та IntroSort. Стабільність та "Big O". |
| Лекція 22 | [Графи та Алгоритми пошуку (Graphs & Search)](22_graphs_search.md) | Binary Search. Графи в пам'яті (Matrix vs List). BFS та DFS для навігації. |
| Лекція 23 | [Стратегії оптимізації (Greedy & Dynamic Programming)](23_optimization_dp.md) | Коли жадібність працює, а коли потрібне DP. Задача про рюкзак. |
| Практикум 14 | [Search Engine — Індексація файлів (Hash Maps)](p14_search_engine.md) | Побудова пошукового індексу за допомогою хеш-таблиці. |
| Практикум 15 | [Pathfinder — Пошук шляху в лабіринті (BFS/DFS)](p15_pathfinder.md) | Практичне застосування BFS та DFS. |
| Практикум 16 | [Knapsack Problem — Оптимізація вантажу (DP)](p16_knapsack.md) | Розв'язання задачі про рюкзак методом динамічного програмування. |

---

## Додатковий матеріал: Advanced Topics

Для студентів, які хочуть заглибитися у performance engineering та екстремальну оптимізацію.

| # | Матеріал | Ключова ідея |
|---|----------|--------------|
| Лекція 24 | [Performance Deep Dive — Профілювання та Оптимізація](24_performance_deep_dive.md) | Memory hierarchy, Timer class, compiler flags, perf profiling, Makefile. |
| Лекція 25 | [String Algorithms — Pattern Matching](25_string_algorithms.md) | Naive, Rabin-Karp, KMP. Complexity proofs and rolling hash optimization. |
| Лекція 26 | [Tree Data Structures — BST and Red-Black Trees](26_tree_structures.md) | BST operations, rotations, Red-Black balancing mechanics, why std::map uses RB-trees. |
| Практикум 17 | [1 Billion Row Challenge — Екстремальна оптимізація](p17_billion_row.md) | Прискорення обробки даних у 50+ разів. String view, integer math, zero-copy техніки. |
| Практикум 18 | [Pattern Matching Algorithms — Реалізація та Порівняння](p18_pattern_matching.md) | Implement Naive, Rabin-Karp, KMP. Benchmark and DNA sequencing application. |
| Практикум 19 | [Building a Binary Search Tree — Візуалізація та Benchmark](p19_bst_implementation.md) | BST from scratch, rotations, ASCII visualization, comparison with std::map. |

---

## Self-Study: Modern C++ Companion

Опціональні матеріали, які показують сучасні C++20/23 альтернативи до патернів з лекцій.

* [Modern C++ Self-Study Guide](self_study/modern_cpp_guide.md) — Production-ready patterns
  - [Legacy → Modern Upgrades](self_study/upgrades/legacy_to_modern.md) — C++98/11 → C++20/23 side-by-side
  - [Visual Diagrams](self_study/visuals/memory_diagrams.md) — Mermaid visualizations of memory & execution
  - [Coding Challenges](self_study/exercises/coding_challenges.md) — 6 interactive exercises with solutions
  - [Quick Reference](self_study/quick_reference/cheatsheet.md) — Cheatsheet for fast lookup

**Навіщо?** Лекції навчають фундаментам через C++11 (розуміємо *"чому"*). Self-study показує, що пишуть професіонали у 2024 (вчимося *"як"*).

---

## Для викладача

* [Методичні рекомендації та типові больові точки студентів](todo.md) — Педагогічні стратегії, технічний стек, Paint Points.
