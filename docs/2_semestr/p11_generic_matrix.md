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
        // Змінюємо розмір вектора: r рядків, в кожному c елементів
        data.resize(r, std::vector<T>(c, 0)); // 0 - значення за замовчуванням
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

---

## Завдання 2: "Красивий вивід" (`operator<<`)

Ми хочемо писати `cout << m`.
Для цього треба оголосити `friend` функцію.

**Додайте це всередину класу:**

```cpp
    // Friend declaration
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& m);

```

**Реалізуйте це ПІСЛЯ класу (але в тому ж .h файлі):**

```cpp
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            os << m.at(i, j) << "\t";
        }
        os << "\n";
    }
    return os;
}

```

*Перевірте в `main.cpp`: створіть `Matrix<int> m(2, 2)`, заповніть і виведіть.*

---

## Завдання 3: Додавання та Множення

Реалізуйте математику.

**1. Додавання (`operator+`):**

* Перевірити, чи збігаються розміри. Якщо ні — кинути `std::invalid_argument`.
* Створити нову матрицю `result`.
* У подвійному циклі: `result.at(i, j) = this->at(i, j) + other.at(i, j)`.
* Повернути `result`.

**2. Множення (`operator*`):**

* Правило: `(N x M) * (M x K) = (N x K)`. Перевірити розміри (`cols == other.rows`).
* Алгоритм: "Рядок на Стовпчик".
$$ C_{ij} = \sum_{k=0}^{M-1} A_{ik} \times B_{kj} $$

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

---

## Завдання із зірочкою: Функціональний стиль

Зробіть метод `apply`, який приймає **функцію** (лямбду) і застосовує її до кожного елемента матриці.

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

// Використання в main: піднести все до квадрату
m.apply([](int x) { return x * x; });

```

---

## Definition of Done

Створіть файл `main.cpp` з таким сценарієм (Test Case):

1. Створіть матрицю `A` (2x3) типу `int` і `B` (3x2) типу `int`.
2. Заповніть їх числами (через `at()` або цикл).
3. Виведіть їх в консоль.
4. Спробуйте зробити `C = A * B`. Виведіть результат.
5. Спробуйте зробити `D = A + B`. Має "впасти" з помилкою (перехопіть її через `try-catch` і виведіть повідомлення "Error: Dimensions mismatch").
6. Створіть матрицю `double` і перевірте, що логіка працює і для дробових чисел.

```cpp
int main() {
    try {
        Matrix<int> A(2, 3);
        // ... fill A ...
        Matrix<int> B(3, 2);
        // ... fill B ...
        
        Matrix<int> C = A * B;
        std::cout << "Result:\n" << C << std::endl;
        
        // This should fail
        Matrix<int> D = A + B; 
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

```
