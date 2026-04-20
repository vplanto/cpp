# Лекція 18: Modern C++ — Move Semantics, Smart Pointers та Lambdas

[← Лекція 17](17_generics_operators.md) | [Index](index.md) | [Далі: Лекція 19 →](19_complexity_profiling.md)


## Мета
Перестати писати як у 1998 році.
1.  Зрозуміти **Move Semantics**: як "вкрасти" дані замість копіювання (оптимізація швидкодії).
2.  Освоїти **Smart Pointers**: як назавжди забути про `delete` та Memory Leaks.
3.  Вивчити **Lambdas**: як писати функціональний код у стилі Python/JS.

## Експрес-опитування
1.  У чому різниця між "Копіюванням" файлу і "Переміщенням" файлу на диску? Що швидше?
2.  Що станеться, якщо функція викине `exception`, а ви забули написати `delete` для свого вказівника?
3.  Чи можна передати функцію як аргумент іншій функції?

<details markdown="1">
<summary>Інженерна відповідь</summary>

1.  **Переміщення миттєве** (змінюється запис у таблиці файлової системи). Копіювання — довге (читання + запис усіх байтів). У пам'яті так само.
2.  **Memory Leak.** Пам'ять залишиться зайнятою назавжди (до перезапуску процесу).
3.  Так, через вказівник на функцію, функтор або (як ми сьогодні дізнаємось) через `lambda` та `std::function`.

</details>

---

## Частина 1: Move Semantics (R-value References)

Це головна фіча C++11, яка зробила мову значно швидшою.

### Проблема: Зайві копії
Уявіть, що ви повертаєте величезний `Vector` з функції.
```cpp
Vector createHugeVector() {
    Vector v(1000000); // 1. Виділили пам'ять
    return v;          // 2. Скопіювали v у тимчасовий об'єкт (Deep Copy)
                       // 3. Знищили v
}
Vector main_vec = createHugeVector(); // 4. Скопіювали тимчасовий об'єкт у main_vec

```

Ми двічі копіюємо мільйон елементів, щоб просто передати їх. Це безглуздо.

### Рішення: "Пограбування" (Move)

Замість того, щоб копіювати дані, ми "крадемо" вказівник на дані у тимчасового об'єкта, який все одно зараз помре.

Для цього існує **R-value reference (`&&`)**.

* **L-value (`&`):** Те, що має ім'я і адресу (змінна `x`). Може жити довго.
* **R-value (`&&`):** Тимчасове значення (`5`, `x + y`, результат функції). Живе лише в цьому рядку.

### The Rule of Five (Правило П'яти)

До нашого "Rule of Three" додаються ще два методи:

```cpp
class Buffer {
    int* data;
    size_t size;
public:
    // 1. Dtor, 2. Copy Ctor, 3. Copy Assign... (старі)

    // 4. Move Constructor
    // Приймає тимчасовий об'єкт (other)
    Buffer(Buffer&& other) noexcept {
        data = other.data; // 1. Крадемо ресурс
        size = other.size;
        
        other.data = nullptr; // 2. Замітаємо сліди (обнуляємо жертву)
        other.size = 0;
    }

    // 5. Move Assignment Operator
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;     // 1. Звільняємо своє старе
            
            data = other.data; // 2. Крадемо чуже
            size = other.size;
            
            other.data = nullptr; // 3. Обнуляємо жертву
            other.size = 0;
        }
        return *this;
    }
};

```

Тепер `v1 = std::move(v2)` перемістить дані за O(1).

---

## Частина 2: Smart Pointers (RAII на стероїдах)

<details markdown="1">
<summary>🔬 <b>Mathematical View:</b> Pointers as Index Functions</summary>

**Memory as Sequence:**

Model memory as a sequence:
$$M = (m_0, m_1, m_2, \dots, m_n)$$

where each $m_i$ is a byte.

**Pointer Definition:**

A pointer $p$ is simply an **index** $i \in \mathbb{N}$:
$$p: () \to \mathbb{N}, \quad p() = i$$

**Dereferencing:**
$$*p = m_{p()}$$

Accessing the value stored at index $p()$.

**Pointer Arithmetic:**
```cpp
int* p = &arr[0];  // p() = i
p + 1;              // p() = i + sizeof(int)
```

This is index arithmetic: $p_{new}() = p() + \text{sizeof}(T)$.

**Example:**
```cpp
int arr[5] = {10, 20, 30, 40, 50};
int* p = arr;  // p() = address of arr[0]

*p      → m_{p()} = 10
*(p+1)  → m_{p() + 4} = 20  // sizeof(int) = 4 bytes
*(p+2)  → m_{p() + 8} = 30
```

**Iterators (Generalized Indices):**

For non-contiguous structures (linked list, tree), we need a **traversal function**:
$$\text{next}: \text{Node} \to \text{Node}$$

An iterator is a pair:
$$\text{Iterator} = (\text{current\_node}, \text{next\_function})$$

Examples:
- Array iterator: $\text{next}(i) = i + 1$ (trivial index increment)
- List iterator: $\text{next}(node) = node \to next$ (follow pointer)
- Tree iterator: $\text{next}(n) = \text{in\_order\_successor}(n)$ (complex tree traversal)

**Why Smart Pointers:**

Raw pointer: Index $p$ with manual lifecycle management  
Smart pointer: $(p, \text{deleter})$ — index + automatic cleanup function

When smart pointer goes out of scope:
1. Call $\text{deleter}(p)$ (free memory at index $p$)
2. Set $p = \text{null}$ (invalid index)

**See also:** [Memory Model Glossary](00_memory_model_glossary.md#1-memory--storage-duration) for storage duration.

</details>

Ви більше не повинні писати `new` і `delete` вручну. Ніколи.
Стандартна бібліотека `<memory>` дає нам "розумні" обгортки.

### 1. `std::unique_ptr<T>` (Ексклюзивний власник)

* **Суть:** "Цим об'єктом володію тільки я".
* **Копіювання:** Заборонено (Deleted Copy Ctor).
* **Переміщення:** Дозволено (`std::move`).
* **Overhead:** Нульовий. Це просто `T*` під капотом.

```cpp
#include <memory>

void usage() {
    // make_unique - безпечний спосіб створення (C++14)
    std::unique_ptr<Player> p1 = std::make_unique<Player>("Hero");
    
    p1->attack(); // Працює як звичайний вказівник ->
    
    // std::unique_ptr<Player> p2 = p1; // ПОМИЛКА КОМПІЛЯЦІЇ! Копіювання заборонено.
    std::unique_ptr<Player> p2 = std::move(p1); // ОК. p1 тепер пустий, p2 володіє даними.
} // p2 виходить з scope -> викликається delete. Автоматично.

```

### 2. `std::shared_ptr<T>` (Спільна власність)

* **Суть:** "Ми володіємо цим разом". Використовує **Reference Counting** (лічильник посилань).
* **Копіювання:** Збільшує лічильник `ref_count++`.
* **Знищення:** Зменшує `ref_count--`. Пам'ять звільняється, коли лічильник == 0.

---

## Частина 3: Exceptions (Обробка помилок)

Коди помилок (`return -1`) — це минуле століття. Вони ігноруються, вони змішують логіку з обробкою помилок.

**Механізм:**

1. **Throw:** Кидаємо проблему вгору.
2. **Try-Catch:** Ловимо проблему там, де знаємо, як її вирішити.

```cpp
double divide(double a, double b) {
    if (b == 0) throw std::runtime_error("Division by zero!");
    return a / b;
}

void main() {
    try {
        divide(10, 0);
    } 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

```

**Головне про Exceptions:** Вони працюють ідеально тільки з **RAII**.
Якщо виділити пам'ять через `new`, потім кинути `throw`, а `delete` стоїть нижче — буде витік.
Якщо використовувати `unique_ptr` — він сам очиститься під час польоту виключення (Stack Unwinding).

---

## Частина 4: Lambdas & Functional Programming

Іноді нам треба передати шматок коду в функцію (наприклад, критерій сортування). Писати окрему функцію або функтор — довго.

**Лямбда** — це анонімна функція прямо в коді.
**Синтаксис:** `[capture](params) { body }`

```cpp
#include <algorithm>
#include <vector>

void lambdaDemo() {
    std::vector<int> v = {1, 5, 2, 4, 3};
    int threshold = 3;

    // Сортуємо по спаданню
    std::sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });

    // Capture list [threshold]: Захоплюємо змінну із зовнішнього світу
    auto it = std::find_if(v.begin(), v.end(), [threshold](int x) {
        return x > threshold; 
    });
}

```

`std::function<Ret(Args)>` — це універсальна обгортка, яка може зберігати лямбду, функтор або вказівник на функцію.

---

## Контрольні питання

1. Що таке `std::move`? Чи переміщує він дані фізично? (Підказка: ні, це просто каст до `&&`, який дозволяє вибрати Move Constructor).
2. Чому `unique_ptr` швидший за `shared_ptr`?
3. Напишіть лямбду, яка приймає два `int` і повертає їх суму.
4. В чому небезпека `shared_ptr` при циклічних посиланнях (A посилається на B, B на A)? (Підказка: Memory Leak, для цього є `weak_ptr`).

<details markdown="1">
<summary>Відповіді</summary>

1. `std::move(x)` не рухає байти. Він просто каже компілятору: "Вважай `x` тимчасовим об'єктом, його можна грабувати". Сама робота робиться в конструкторі.
2. `unique_ptr` не має оверхеду (просто вказівник). `shared_ptr` має атомарний лічильник посилань і додатковий блок пам'яті (control block), що повільніше.
3. `[](int a, int b) { return a + b; };`
4. Лічильник посилань ніколи не стане нулем, бо об'єкти тримають один одного. Пам'ять ніколи не звільниться.

</details>
