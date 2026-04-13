# Практикум 11: Matrix Engine (Templates & Operators)

← [Index](index.md)

**Теорія:** [Лекція 17: Generics та Оператори](17_generics_operators.md)

---


## Роль: Core Tech Developer (Game Engine)

Ваша студія розробляє 3D-рушій. Графічна підсистема постійно працює з матрицями (трансформації, повороти).
Поточний код виглядає так:
```cpp
// Legacy code (жахливо)
MatrixFloat m3 = Matrix_Multiply(m1, m2);
MatrixInt grid3 = Matrix_Add_Int(g1, g2);

```

Ваша задача — переписати це, використовуючи **Шаблони** (щоб працювало і для `int`, і для `double`) та **Перевантаження операторів** (щоб код виглядав як математика).

Цільовий синтаксис:

```cpp
// Modern code (наша мета)
Matrix<float> m3 = m1 * m2;
Matrix<int> grid3 = g1 + g2;
std::cout << m3;

```

---

## Експрес-опитування

1. Якщо ми пишемо `template <typename T>`, у який момент компілятор створює реальний код класу? (Під час написання, під час компіляції чи під час запуску?)
2. Чому оператор `<<` (вивід у потік) зазвичай реалізують як `friend` функцію, а не метод класу?
3. Чи можна перевантажити оператор `+` так, щоб він віднімав числа? (Технічно — так, а чи варто це робити?)

<details markdown="1">
<summary>Інженерна довідка</summary>

1. **Під час компіляції (Compile-time).** Це називається *instantiation*.
2. Тому що лівим операндом є `std::ostream` (`cout`), а ми не можемо змінювати код стандартної бібліотеки.
3. **Ні в якому разі.** Це порушує "Principle of Least Surprise". Оператори мають робити те, що від них очікують.

</details>

### Контейнер `std::vector` — Сучасна заміна масивів `[]`

У сучасному C++ ми майже не використовуємо класичні масиви (`int arr[10]`), тому що вони "забувають" свій розмір і не можуть рости. Замість них ми використовуємо `std::vector<T>` — це динамічний масив, що автоматично керує своєю пам'яттю.

**Аналогія з масивами:**
| Класичний масив `[]` | Контейнер `std::vector` |
|---|---|
| `int arr[rows][cols];` | `std::vector<std::vector<int>> matrix;` |
| `arr[i][j] = 5;` | `matrix[i][j] = 5;` |
| Треба знати розмір наперед | Можна змінювати розмір (`resize`) |
| Легко вийти за межі | Можна перевіряти межі (`.at()`) |

**Як створити двомірний вектор (Матрицю):**
Двомірний вектор — це "вектор векторів". Кожен рядок — це окремий вектор.

```cpp
// Створити матрицю 3 ряди на 4 стовпці (оскільки value не передано — ініціалізується нулями):
std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols)); 

// Доступ до елемента:
matrix[1][2] = 42; 
```

---

## Завдання 1: Шаблонний каркас (`Matrix.h`)

Створіть файл `Matrix.h` (шаблони пишуть повністю у хедерах!).

**Вимоги:**

1. Клас `Matrix` приймає тип `T`.
2. Зберігає дані у `std::vector<std::vector<T>>` (двовимірний масив).
3. Зберігає `rows` та `cols`.
4. **Конструктор:** Приймає розміри `rows` і `cols`. Заповнює матрицю нулями.

```cpp
#pragma once
#include <vector>
#include <iostream>
#include <stdexcept> // Для помилок

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    int rows;
    int cols;

public:
    // Constructor
    Matrix(int r, int c) : rows(r), cols(c) {
        // resize() та конструктор vector<T>(n) виконують замовчувальну ініціалізацію.
        // Довідка: https://en.cppreference.com/w/cpp/container/vector/resize
        data.resize(r, std::vector<T>(c)); // Оскільки value не передано — ініціалізується нулем (для чисел)
    }

    // Getters
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // Доступ до елементів (для зручності: m.at(0, 1) = 5)
    T& at(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return data[r][c];
    }

    // const версія для читання
    const T& at(int r, int c) const {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return data[r][c];
    }
};

```

> [!NOTE]
> **Навіщо нам дві майже однакові функції `at`?**
> Це вияв принципу **Const-Correctness** (Константна безпека). Уявіть ситуацію:
> 
> 1. **`T& at(...)`**: Це дозвіл на **читання та запис**. Вона повертає звичайне посилання, через яке можна змінити елемент (наприклад, `m.at(0,0) = 5;`). Але якщо об'єкт константний (`const Matrix`), викликати цей метод **заборонено**, бо через нього можна випадково зламати "обіцянку не змінювати дані".
> 
> 2. **`const T& at(...) const`**: Це дозвіл **тільки на читання**. Слово `const` в кінці сигнатури гарантує компілятору, що цей метод нічого не змінює всередині класу.
> 
> **Чому це критично:** У нашому `operator<<` (Завдання 2) ми приймаємо матрицю як `const Matrix& m`. Якщо ми не напишемо другу версію `at`, компілятор просто не дозволить нам прочитати дані з матриці для виводу в консоль, вважаючи це небезпечною операцією.

---

## Завдання 2: "Красивий вивід" (`operator<<`)

Ми хочемо писати `std::cout << m;`. Для шаблонних класів найкращою практикою є ідіома **Hidden Friend**. 

**Чому це важливо:** Як зазначено в Лекції 17, зовнішні шаблонні `friend`-функції потребують складного синтаксису і часто призводять до помилок лінкера. **Hidden Friend** дозволяє визначити тіло оператора прямо всередині класу — це простіше, коротше і надійніше.

**Додайте це всередину класу `Matrix`:**

```cpp
    // Hidden Friend: тіло функції пишеться прямо в класі.
    // Хоча вона в класі, вона залишається зовнішньою функцією.
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
        for (int i = 0; i < m.rows; ++i) { // Маємо прямий доступ до private fields
            for (int j = 0; j < m.cols; ++j) {
                os << m.data[i][j] << "\t";
            }
            os << "\n";
        }
        return os;
    }
```

*Перевірте в `main.cpp`: створіть `Matrix<int> m(2, 2)`, заповніть і виведіть.*

<details markdown="1">
<summary><b>Підказка: Як має виглядати Matrix.h та main.cpp на цьому етапі (Завдання 1-2)</b></summary>

**Matrix.h:**
```cpp
#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    int rows, cols;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        // resize() виконує zero-initialization для чисел
        data.resize(r, std::vector<T>(c)); 
    }

    T& at(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) throw std::out_of_range("Bounds");
        return data[r][c];
    }

    const T& at(int r, int c) const {
        if (r < 0 || r >= rows || c < 0 || c >= cols) throw std::out_of_range("Bounds");
        return data[r][c];
    }

    // Hidden Friend Idiom: тіло функції прямо в класі
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j) {
                os << m.data[i][j] << "\t";
            }
            os << "\n";
        }
        return os;
    }
};
```

**main.cpp:**
```cpp
#include "Matrix.h"
#include <iostream>

int main() {
    Matrix<int> m(2, 2);
    m.at(0, 0) = 1; m.at(0, 1) = 2;
    m.at(1, 0) = 3; m.at(1, 1) = 4;

    std::cout << "My Matrix:\n" << m << std::endl;
    return 0;
}
```
</details>

---

## Завдання 3: Додавання та Множення (Const-Correctness)

Ми маємо реалізувати математичні операції. 

> [!IMPORTANT]
> **Вимога:** Дотримуйтесь "Трьох обіцянок const" (див. Лекцію 17, Зупинка 1). 
> 1. Аргумент `const Matrix<T>& other` (не змінюємо те, що додаємо).
> 2. Сам метод `const` (операція `+` не змінює поточну матрицю).
> 3. Результат повертається за значенням `Matrix<T>` **без const** (щоб працювали оптимізації **RVO** та Move Semantics).

**Зміст завдання:**

1.  **Додавання (`operator+`):**
    - Перевірити, чи збігаються розміри. Якщо ні — кинути `std::invalid_argument`.
    - Створити нову матрицю `result`.
    - У подвійному циклі скласти елементи: `result.at(i, j) = this->data[i][j] + other.data[i][j]`.

2.  **Множення (`operator*`):**
    - Перевірити розміри (`cols == other.rows`).
    - Алгоритм: "Рядок на Стовпчик".
    - $$ C_{ij} = \sum_{k=0}^{M-1} A_{ik} \times B_{kj} $$

<details markdown="1">
<summary><b>Рішення: перевірте себе</b></summary>

```cpp
    // Всередині класу Matrix:

    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions mismatch for addition");
        }
        
        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.at(i, j) = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
        }

        Matrix<T> result(rows, other.cols);
        
        for (int i = 0; i < rows; ++i) { // Рядки A
            for (int j = 0; j < other.cols; ++j) { // Стовпці B
                for (int k = 0; k < cols; ++k) { // Скалярний добуток
                    result.at(i, j) += data[i][k] * other.at(k, j);
                }
            }
        }
        return result;
    }
```
</details>

---

## Завдання із зірочкою: Функціональний стиль

### Що таке "Функціональний стиль"?

Зазвичай ми самі пишемо цикли (`for`), щоб обробити дані. **Функціональний стиль** пропонує інший підхід: ми створюємо один універсальний цикл (`apply`), а саму логіку (що саме робити з числом) передаємо як параметр.

*   **Функція як аргумент:** Уявіть, що ви передаєте всередину методу не просто число, а цілий "шматок коду" (алгоритм).
*   **Лямбда-вираз (`[]...`):** Це "одноразова" функція без імені, яку ми створюємо прямо на місці виклику. Синтаксис `[](int x) { return x * x; }` буквально означає: "візьми `x` і поверни його квадрат".

Це дозволяє відокремити **процес** перебору матриці (який завжди однаковий) від **логіки** обробки даних (яка може бути будь-якою).

**Завдання:** Створіть метод `apply`, який приймає **функцію** (лямбду) і застосовує її до кожного елемента матриці.

<details markdown="1">
<summary><b>Рішення: як це реалізувати</b></summary>

```cpp
    // Всередині класу
    template <typename Func>
    void apply(Func f) {
        for (auto& row : data) {
            for (auto& val : row) {
                val = f(val); // Замінюємо значення результатом функції
            }
        }
    }
```

**Приклад використання в `main` (піднести все до квадрату):**
```cpp
    m.apply([](int x) { return x * x; });
```
</details>

---

## Завдання 4: Пастка "Стіни тексту" (C++20 Concepts)

Шаблони в C++ за замовчуванням працюють за принципом **Compile-time Duck Typing**: "якщо воно виглядає як число і підтримує оператор `*`, то це число". Але що буде, якщо ми передамо тип, який не знає математики?

**1. Провокуємо помилку:**
Спробуйте створити матрицю рядків і перемножити їх:
```cpp
Matrix<std::string> s1(2, 2);
Matrix<std::string> s2(2, 2);
auto s3 = s1 * s2; // ❌ Рядки не можна множити!
```
Ви отримаєте величезну помилку ("стіну тексту"). Зверніть увагу: компілятор скаржиться на код **всередині `Matrix.h`**, хоча помилка — у вашому виклику в `main.cpp`. Це ускладнює відладку у великих проєктах.

**2. Рішення: Впроваджуємо Контракт:**
Підключіть `<concepts>` і обмежте тип `T` лише числами.

```cpp
#include <concepts>

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <Number T> // Тепер Matrix приймає лише числа
class Matrix {
   // ...
};
```
Тепер при спробі створити `Matrix<std::string>` компілятор зупиниться одразу в `main.cpp`, коротко сказавши: "string не задовольняє вимогу Number".

---

## Definition of Done

Створіть файл `main.cpp` з таким сценарієм (Test Case):

1. Створіть матрицю `A` (2x3) типу `int` і `B` (3x2) типу `int`.
2. Перевірте, що спроба створити `Matrix<std::string>` відхиляється компілятором (якщо ви виконали Завдання 4).
3. Заповніть матриці числами та виведіть їх.
4. Спробуйте зробити `C = A * B`. Виведіть результат.
5. Спробуйте зробити `D = A + B`. Має "впасти" з помилкою (перехопіть її через `try-catch` і виведіть повідомлення "Error: Dimensions mismatch").
6. Створіть матрицю `double` і перевірте, що логіка працює і для дробових чисел.
7. **Type Deduction Trap:** Спробуйте скласти `Matrix<int>` та `Matrix<double>`. Виявіть причину помилки (Зупинка 3) та навчіться її вирішувати через явну специфікацію типів або кастинг.

```cpp
int main() {
    try {
        Matrix<int> A(2, 3);
        // ... fill A ...
        Matrix<int> B(3, 2);
        // ... fill B ...
        
        Matrix<int> C = A * B;
        std::cout << "Result:\n" << C << std::endl;
        
        // 5. This should fail (Dimensions mismatch)
        Matrix<int> D = A + B; 

        // 7. Type Deduction Trap
        Matrix<int> mi(2, 2);
        Matrix<double> md(2, 2);
        // auto res = mi + md; // ❌ Помилка: Matrix<int> != Matrix<double>
        // Щоб виправити, треба або привести типи, або розширити шаблон оператора.
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

```

---

## Контрольні питання

1. Коли компілятор генерує код шаблонного класу — під час написання, компіляції чи запуску? Які наслідки це має для `.h`-файлів?
2. Чому `operator<<` у шаблонних класах реалізують через ідіому **Hidden Friend** (всередині класу), а не як звичайну зовнішню `friend` функцію?
3. У чому різниця між `operator+` (повертає нову матрицю) і `operator+=` (змінює поточну)? Яке з них ефективніше за пам'яттю?
4. Що відбудеться, якщо спробувати скласти `Matrix<int>` і `Matrix<double>`? Як це виправити?
5. У чому різниця між "Duck Typing" у шаблонах та C++20 Concepts з точки зору відладки коду?

<details markdown="1">
<summary>Відповіді для самоперевірки</summary>

1. **Під час компіляції** (template instantiation). Саме тому весь код шаблону має бути у `.h`-файлі: компілятор підставляє конкретний тип (наприклад, `int`) і генерує реальний клас у момент компіляції файлу, де цей тип використовується. З `.cpp` він не зміг би цього зробити.
2. Зовнішні `friend`-шаблони потребують складних попередніх декларацій та синтаксису `<>`. **Hidden Friend** (визначення всередині класу) усуває цей візуальний шум, запобігає помилкам лінкування та обмежує видимість функції механізмом ADL (она знайдеться лише тоді, коли аргументом справді є `Matrix`).
3. `operator+` створює **нову** матрицю-результат (виділяє пам'ять). `operator+=` змінює об'єкт на місці — не виділяє нової пам'яті та на практиці є швидшим. Компілятор часто виводить `operator+` через `operator+=` (`a + b` = `temp(a); temp += b; return temp`).
4. Компілятор відмовить: шаблон не знає, як додати `T` + `U` різних типів. Можна виправити через `template <typename T, typename U>` і тип результату через `decltype`, або через `std::common_type_t<T,U>` (C++14).
5. **Duck Typing** видає помилку "всередині" реалізації шаблону (складно читати). **Concepts** перевіряють тип "на вході" (у місці виклику), даючи коротку і зрозумілу помилку про невиконання контракту.

</details>
