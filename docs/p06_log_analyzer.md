# Практикум 6: `std::string` — Створюємо "Аналізатор логів"

## 🎯 Наш "продукт" сьогодні

Уявимо, що ми — системні адміністратори, і у нас є "брудний" лог-файл. Наша задача — написати утиліту, яка "парсить" (розбирає) цей лог і виводить дані у красивому, читабельному форматі. Це одна з найпоширеніших задач у програмуванні.

**Наш "брудний" лог:**

```
[INFO] user: admin session_id: 1001 action: login
[ERROR] user: guest session_id: 1002 action: access_denied
[INFO] user: dev session_id: 1003 action: logout
```

**Наш "чистий" звіт (мета):**

```
РІВЕНЬ | КОРИСТУВАЧ | ID СЕСІЇ | ДІЯ
-----------------------------------------------------
INFO   | admin      | 1001     | login
ERROR  | guest      | 1002     | access_denied
INFO   | dev        | 1003     | logout
```

## 🏁 Експрес-опитування

У [Лекції 9](09_string.md) ми вже познайомилися з `std::string`. Давайте пригадаємо:

1.  У чому головна перевага `std::string` над `char[]` (C-String)?
2.  Як з'єднати (конкатенувати) два `std::string`?
3.  Чому `cin >> myString;` — погана ідея для зчитування повного імені?
4.  Який заголовочний файл потрібно підключити для роботи з `std::string`?

<details markdown="1">
<summary>Натисніть, щоб побачити відповіді</summary>

1.  **Безпека та зручність.** `std::string` **автоматично керує пам'яттю**, тому ми не можемо отримати "переповнення буфера". Він також надає зручні методи (`.length()`, `.find()` тощо).
2.  За допомогою оператора **`+`** (наприклад, `string s3 = s1 + s2;`).
3.  Тому що `cin >>` зчитує лише **одне слово** (до першого пробілу). Для зчитування повного рядка потрібен `getline`.
4.  Потрібно підключити **`<string>`**.

</details>

-----

## 💡 Довідка: Концепція Потоків (Streams)

Ми ще не вивчали роботу з файлами (це буде в [Лекції 11](11_stream.md)), але нам потрібно розуміти концепцію **Потоку**.

У C++ **потік (stream)** — це абстракція для послідовного вводу/виводу даних. Уявіть його як трубу, по якій байт за байтом течуть дані.

  * **`std::cin`** — це потік, підключений до клавіатури.
  * **`std::cout`** — це потік, підключений до екрана.

Сьогодні ми використаємо **`std::stringstream`** (з бібліотеки `<sstream>`). Це спеціальний потік, який дозволяє працювати зі звичайним рядком (`std::string`) так, ніби це файл або консоль. Ми зможемо "читати" з нього дані за допомогою `>>` або `getline`.

-----

## Частина 1: Підготовка даних (Stringstream)

Спочатку створимо наші дані.

```cpp
#include <iostream>
#include <string>
#include <sstream> // Для "симуляції" файлу (string stream)
#include <iomanip> // Для красивого виводу

using namespace std;

// Зверніть увагу: тут немає '+' між рядками!
// Це "Concatenation of String Literals" — фіча C++.
// Компілятор сам "склеїть" ці рядки в один довгий під час компіляції.
string rawLog = 
    "[INFO] user: admin session_id: 1001 action: login\n"
    "[ERROR] user: guest session_id: 1002 action: access_denied\n"
    "[INFO] user: dev session_id: 1003 action: logout\n";

int main() {
    // 1. "Заряджаємо" наш рядок у потік stringstream
    stringstream ss(rawLog);
    string line; 

    // 2. Зчитуємо "потік" по одному рядку (до '\n'), поки він не закінчиться
    while (getline(ss, line)) {
        // Тут ми будемо обробляти кожен рядок 'line'
        cout << "Отримано рядок: " << line << endl;
    }
    return 0;
}
```

-----

## Частина 2: "Парсинг" — ріжемо рядок (`find` та `substr`)

Тепер найцікавіше. Нам потрібно написати функцію, яка буде "вирізати" потрібне значення (наприклад, ім'я юзера) з рядка.

**Алгоритм функції `parseValue(line, key)`:**

1.  Знайти, де починається ключ (наприклад, `"user: "`).
2.  Знайти, де закінчується значення (наступний пробіл).
3.  Вирізати шматок тексту між ними.

```cpp
// Функція-помічник
string parseValue(const string& line, string key) {
    // 1. Шукаємо позицію ключа
    size_t startPos = line.find(key);
    if (startPos == string::npos) { // npos означає "не знайдено"
        return "N/A";
    }
    
    // 2. Зсуваємось на довжину ключа, щоб вказати на початок ЗНАЧЕННЯ
    startPos += key.length();

    // 3. Шукаємо кінець значення (перший пробіл ПІСЛЯ початку значення)
    size_t endPos = line.find(" ", startPos);

    // 4. Вирізаємо підрядок
    // substr(початок, довжина)
    // Якщо endPos == npos (кінець рядка), substr візьме все до кінця
    return line.substr(startPos, endPos - startPos);
}

// ... всередині циклу while ...
while (getline(ss, line)) {
    string level = parseValue(line, "[");
    // У 'level' зараз "[INFO", треба прибрати зайву дужку '[' (ми її знайшли)
    // А також ми хочемо прибрати ']' в кінці.
    // Простіше використати find для початку значення:
    
    // Давайте спростимо і використаємо нашу функцію для всього:
    string user = parseValue(line, "user: ");
    string session = parseValue(line, "session_id: ");
    string action = parseValue(line, "action: ");

    // Для Рівня (INFO/ERROR) доведеться трохи схитрувати або покращити парсер.
    // Але для простоти давайте виріжемо його вручну:
    size_t levelStart = line.find('[') + 1;
    size_t levelEnd = line.find(']');
    string cleanLevel = line.substr(levelStart, levelEnd - levelStart);

    cout << cleanLevel << " " << user << " " << session << " " << action << endl;
}
```

-----

## Частина 3: Форматований вивід (`<iomanip>`)

Тепер зробимо красиву табличку, як ми планували.

**Інструменти:**

  * `setw(n)`: Встановлює ширину поля (робить стовпчики рівними).
  * `left`: Вирівнює текст по лівому краю.

<!-- end list -->

```cpp
// ... перед циклом (Заголовок) ...
cout << left;
cout << setw(10) << "РІВЕНЬ" << "| " 
     << setw(15) << "КОРИСТУВАЧ" << "| " 
     << setw(10) << "ID СЕСІЇ" << "| " 
     << "ДІЯ" << endl;
cout << string(50, '-') << endl; // Лінія з 50 дефісів

// ... всередині циклу (Замість простого cout) ...
cout << left;
cout << setw(10) << cleanLevel << "| " 
     << setw(15) << user << "| " 
     << setw(10) << session << "| " 
     << action << endl;
```

-----

## Частина 4: Пастки `std::string` та вводу

Ми вже говорили в лекції про безпеку (`.at()` vs `[]`). Але є ще одна популярна проблема.

### Проблема "Змішаного вводу" (`cin` + `getline`)

Якщо ви спочатку читаєте число (або слово через `cin >>`), а потім намагаєтесь прочитати рядок через `getline`, вас чекає сюрприз.

```cpp
int age;
string name;

cout << "Вік: ";
cin >> age; // Користувач вводить "25" і тисне Enter

cout << "Ім'я: ";
getline(cin, name); // ПРОБЛЕМА! Програма не чекає вводу!
                    // 'name' стає порожнім, програма йде далі.
```

**Чому?** `cin >> age` зчитує число `25`, але залишає символ нового рядка `\n` (Enter) у буфері. `getline` бачить цей `\n`, думає "О, порожній рядок\!" і завершує роботу.

**Рішення:** Завжди очищуйте буфер після `cin >>` перед використанням `getline`.

```cpp
cin >> age;
cin.ignore(); // "З'їдає" зайвий \n
getline(cin, name); // Тепер працює!
```

-----

## Контрольні питання

1.  **Потоки.** Для чого ми використовували `stringstream` у цьому практикумі? Чому не можна було просто працювати з `string rawLog` напряму?
2.  **Парсинг.** Функція `substr` приймає два параметри: `pos` і `len`. Що станеться, якщо ми не передамо другий параметр (`len`)?
3.  **`iomanip`.** Що робить маніпулятор `setw(10)`? Чи діє він на всі наступні виводи, чи тільки на один?
4.  **Пастка.** Ви написали `cin >> id; getline(cin, status);`, але `status` зчитався як порожній рядок. Яку команду ви забули додати між ними?
5.  **Синтаксис.** У коді ми написали:
    ```cpp
    string s = "Line 1\n"
               "Line 2\n";
    ```
    Чи це помилка? Як це працює?

<details markdown="1">
<summary>Натисніть, щоб побачити відповіді</summary>

1.  **`stringstream`** дозволив нам перетворити звичайний рядок на **потік**. Завдяки цьому ми змогли використати зручну функцію `getline()`, яка вміє читати дані "по рядках". Звичайний `std::string` не має методу "дай наступний рядок".
2.  Якщо не передати `len`, `substr` поверне **все до кінця рядка** (починаючи з `pos`).
3.  `setw(10)` встановлює ширину поля **тільки для наступного** елемента виводу. Для наступних елементів ширину треба задавати знову.
4.  Забули **`cin.ignore();`** (щоб прибрати залишковий `\n` з буфера).
5.  Ні, це не помилка. Це **конкатенація рядкових літералів**. C++ автоматично об'єднує рядки, що стоять поруч, в один під час компіляції.

</details>

-----

## 📝 Повний код програми

<details markdown="1">
<summary>Натисніть, щоб відкрити повний код (main.cpp)</summary>

```cpp
#include <iostream>
#include <string>
#include <sstream> // Для роботи з потоками рядків
#include <iomanip> // Для форматування (setw, left)

using namespace std;

// Імітація вмісту файлу логів
// Компілятор автоматично склеїть ці літерали в один рядок
string rawLog = 
    "[INFO] user: admin session_id: 1001 action: login\n"
    "[ERROR] user: guest session_id: 1002 action: access_denied\n"
    "[INFO] user: dev session_id: 1003 action: logout\n";

// Функція для пошуку та вирізання значення за ключем
// Приклад: parseValue("... user: admin ...", "user: ") поверне "admin"
string parseValue(const string& line, const string& key) {
    size_t startPos = line.find(key);
    if (startPos == string::npos) {
        return "-";
    }
    
    // Початок значення = початок ключа + довжина ключа
    startPos += key.length();

    // Шукаємо кінець значення (наступний пробіл)
    size_t endPos = line.find(' ', startPos);

    // Якщо пробіл не знайдено (кінець рядка), беремо все до кінця
    if (endPos == string::npos) {
        return line.substr(startPos);
    }

    return line.substr(startPos, endPos - startPos);
}

int main() {
    stringstream ss(rawLog); // Перетворюємо рядок на потік
    string line;

    // Шапка таблиці
    cout << left;
    cout << setw(10) << "LEVEL" << "| " 
         << setw(15) << "USER" << "| " 
         << setw(10) << "SESSION" << "| " 
         << "ACTION" << endl;
    cout << string(55, '-') << endl;

    // Читаємо потік рядок за рядком
    while (getline(ss, line)) {
        if (line.empty()) continue;

        // 1. Витягуємо рівень (INFO/ERROR)
        // Він завжди між [ та ]
        size_t lvlStart = line.find('[') + 1;
        size_t lvlEnd = line.find(']');
        string level = line.substr(lvlStart, lvlEnd - lvlStart);

        // 2. Витягуємо інші поля за допомогою нашої функції
        string user = parseValue(line, "user: ");
        string session = parseValue(line, "session_id: ");
        string action = parseValue(line, "action: ");

        // 3. Виводимо відформатований рядок
        cout << setw(10) << level << "| " 
             << setw(15) << user << "| " 
             << setw(10) << session << "| " 
             << action << endl;
    }

    return 0;
}
```

</details>
