# Практикум 16: Knapsack Problem — Оптимі��ація вантажу за допомогою DP

← [Index](index.md)

**Теорія:** [Лекція 23: Greedy \u0026 Dynamic Programming](23_optimization_dp.md)

---

## Роль: Logistics Optimizer

Ви працюєте в компанії з доставки. Вантажівка має обмежену вагу, але є багато товарів з різною вагою та цінністю. Ваша задача — вибрати товари так, щоб максимізувати загальну цінність, не перевищуючи ліміт ваги.

**Це класична задача про рюкзак (Knapsack Problem).**

---

## Частина 1: Формулювання задачі

**Дано:**
- `W` — максимальна вага рюкзака (capacity).
- `N` — кількість предметів.
- Для кожного предмета `i`:
  - `weight[i]` — вага.
  - `value[i]` — цінність.

**Знайти:** Підмножину предметів, яка максимізує сумарну цінність, але не перевищує вагу `W`.

**Приклад:**
```
Capacity W = 10 kg
Items:
  1. weight = 2, value = 10
  2. weight = 3, value = 15
  3. weight = 5, value = 25
  4. weight = 7, value = 35

Оптимальне рішення: взяти предмети 1 та 4 → total weight = 9, total value = 45
```

---

## Частина 2: Greedy підхід (наївний)

**Ідея:** Сортувати предмети за співвідношенням "цінність/вага" і брати найвигідніші.

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

struct Item {
    int weight;
    int value;
    double ratio; // value / weight
};

int greedyKnapsack(int W, std::vector<Item>& items) {
    // Сортуємо за співвідношенням (спадання)
    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });
    
    int total_weight = 0;
    int total_value = 0;
    
    std::cout << "Greedy selection:\\n";
    for (const auto& item : items) {
        if (total_weight + item.weight <= W) {
            total_weight += item.weight;
            total_value += item.value;
            std::cout << "  Take: weight=" << item.weight 
                      << ", value=" << item.value << "\\n";
        }
    }
    
    return total_value;
}
```

**Проблема Greedy:** Не завжди дає оптимальне рішення для 0/1 Knapsack.

**Приклад Greedy failure:**
```
W = 6
Items: 
  A: weight=2, value=100 (ratio=50)
  B: weight=3, value=80  (ratio=26.7)
  C: weight=5, value=100 (ratio=20)

Greedy: вибере A (2kg, 100) та B (3kg, 80) → total=180
Optimal: A (2kg, 100) та частина C — але це Fractional Knapsack!
Для 0/1: оптимально вибрати лише C (5kg, 100) якщо інші не підходять.
```

---

## Частина 3: Dynamic Programming підхід

**Ідея:** Побудувати таблицю `dp[i][w]`, де:
- `i` — розглянуто перші `i` предметів.
- `w` — поточна вага рюкзака.
- `dp[i][w]` = максимальна цінність для цих параметрів.

**Рекурентна формула:**
```
dp[i][w] = max(
    dp[i-1][w],                          // Не беремо i-й предмет
    dp[i-1][w - weight[i]] + value[i]    // Беремо i-й предмет
)
```

### Реалізація

```cpp
#include <vector>
#include <algorithm>

struct Item {
    int weight;
    int value;
    std::string name; // Для зручності
};

int knapsackDP(int W, const std::vector<Item>& items) {
    int n = items.size();
    
    // Таблиця DP: (n+1) x (W+1)
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            // Не беремо предмет i
            dp[i][w] = dp[i-1][w];
            
            // Намагаємося взяти предмет i
            int item_weight = items[i-1].weight;
            int item_value = items[i-1].value;
            
            if (item_weight <= w) {
                dp[i][w] = std::max(dp[i][w], 
                                    dp[i-1][w - item_weight] + item_value);
            }
        }
    }
    
    return dp[n][W];
}
```

**Складність:** O(N * W) — де N = кількість предметів, W = вага рюкзака.

---

## Частина 4: Відновлення рішення (які предмети взяли)

**Завдання:** Не тільки знайти максимальну цінність,

 але й вивести, які предмети були вибрані.

```cpp
std::vector<Item> getSelectedItems(int W, const std::vector<Item>& items,
                                   const std::vector<std::vector<int>>& dp) {
    int n = items.size();
    std::vector<Item> selected;
    
    int w = W;
    for (int i = n; i > 0; i--) {
        // Якщо значення змінилося, значить ми взяли цей предмет
        if (dp[i][w] != dp[i-1][w]) {
            selected.push_back(items[i-1]);
            w -= items[i-1].weight;
        }
    }
    
    std::reverse(selected.begin(), selected.end());
    return selected;
}
```

**Використання:**
```cpp
int main() {
    std::vector<Item> items = {
        {2, 10, "Laptop"},
        {3, 15, "Camera"},
        {5, 25, "Monitor"},
        {7, 35, "Drone"}
    };
    
    int W = 10;
    
    // DP розв'язок
    std::vector<std::vector<int>> dp(items.size() + 1, std::vector<int>(W + 1, 0));
    int max_value = knapsackDP(W, items);
    
    std::cout << "Max value: " << max_value << "\\n";
    
    auto selected = getSelectedItems(W, items, dp);
    std::cout << "Selected items:\\n";
    for (const auto& item : selected) {
        std::cout << "  " << item.name << " (weight=" << item.weight 
                  << ", value=" << item.value << ")\\n";
    }
}
```

---

## Частина 5: Порівняння Greedy vs DP

**Експеримент:** Запуститиь обидва алгоритми на одних даних.

```cpp
void compareAlgorithms(int W, std::vector<Item>& items) {
    // Greedy
    for (auto& item : items) {
        item.ratio = static_cast<double>(item.value) / item.weight;
    }
    int greedy_value = greedyKnapsack(W, items);
    
    // DP
    int dp_value = knapsackDP(W, items);
    
    std::cout << "\\n=== Comparison ===\\n";
    std::cout << "Greedy result: " << greedy_value << "\\n";
    std::cout << "DP result:     " << dp_value << "\\n";
    
    if (greedy_value == dp_value) {
        std::cout << "Greedy found optimal solution!\\n";
    } else {
        std::cout << "Greedy suboptimal. DP wins by " 
                  << (dp_value - greedy_value) << "\\n";
    }
}
```

---

## Бонус: Fractional Knapsack (Greedy працює!)

**Відмінність:** Можна брати **частини** предметів.

У цьому випадку Greedy алгоритм **завжди** дає оптимальне рішення:

```cpp
double fractionalKnapsack(int W, std::vector<Item>& items) {
    // Сортуємо за ratio
    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });
    
    double total_value = 0.0;
    int remaining_capacity = W;
    
    for (const auto& item : items) {
        if (remaining_capacity >= item.weight) {
            // Беремо весь предмет
            total_value += item.value;
            remaining_capacity -= item.weight;
        } else {
            // Беремо частину предмета
            double fraction = static_cast<double>(remaining_capacity) / item.weight;
            total_value += item.value * fraction;
            break; // Рюкзак заповнений
        }
    }
    
    return total_value;
}
```

---

## Контрольні питання

1. Чому Greedy не працює для 0/1 Knapsack?

<details markdown="1">
<summary>Відповідь</summary>

Greedy завжди бере предмет з найкращим співвідношенням value/weight. Але це може заблокувати можливість взяти кілька інших предметів, які разом дають більшу цінність. 

Приклад: якщо Greedy вибрав предмет вагою 7kg з цінністю 40, він може заблокувати два предмети по 3kg і 4kg з цінностями 25 і 30 (разом 55).

</details>

2. Яка складність DP розв'язку Knapsack?

<details markdown="1">
<summary>Відповідь</summary>

**O(N * W)** часу та O(N * W) пам'яті для таблиці. Це псевдополіноміальна складність (Pseudo-polynomial), бо залежить від числового значення W, а не від довжини вводу. Для дуже великих W це може стати проблемою.

</details>

3. Чи можна оптимізувати пам'ять DP до O(W) замість O(N * W)?

<details markdown="1">
<summary>Відповідь</summary>

**Так!** Використовувати тільки 1D масив замість 2D таблиці, оскільки для обчислення `dp[i][w]` нам потрібен лише попередній рядок `dp[i-1][...]`.

```cpp
std::vector<int> dp(W + 1, 0);

for (int i = 0; i < n; i++) {
    // Важливо йти справа наліво, щоб не перезаписати потрібні значення
    for (int w = W; w >= items[i].weight; w--) {
        dp[w] = std::max(dp[w], dp[w - items[i].weight] + items[i].value);
    }
}
```

</details>

4. У чому різниця між 0/1 Knapsack і Unbounded Knapsack?

<details markdown="1">
<summary>Відповідь</summary>

- **0/1 Knapsack:** Кожен предмет можна взяти **лише раз**.
- **Unbounded Knapsack:** Кожен предмет можна брати **необмежену кількість разів**.

Для Unbounded змінюється DP формула — замість `dp[i-1][...]` використовуємо `dp[i][...]` (бо можемо брати той самий предмет знову).

</details>
