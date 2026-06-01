# Практикум 15: Pathfinder — Пошук шляху в лабіринті за допомогою BFS та DFS

← [Index](index.md)

**Теорія:** [Лекція 22: Графи та Алгоритми пошуку](22_graphs_search.md)

---

## Роль: Game AI Developer

Ваша задача — створити AI для гри, який знаходить вихід з лабіринту. Ви реалізуєте два підходи (BFS і DFS) і порівняєте їх.

**Мета:** Розуміти, як працюють алгоритми обходу графів на практиці.

---

## Частина 1: Представлення лабіринту

Лабіринт — це 2D сітка (grid), де:
- `0` = прохід (можна ходити).
- `1` = стіна (не можна пройти).
- `S` = старт.
- `E` = вихід (ціль).

**Приклад:**
```
S 0 1 0 0
0 0 1 0 1
1 0 0 0 0
1 1 1 0 E
```

### Структура даних

Створіть заголовочний файл `Maze.h`:

```cpp
#include <vector>
#include <string>

struct Position {
    int row, col;
    
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

class Maze {
private:
    std::vector<std::vector<int>> grid;
    Position start, end;
    int rows, cols;

public:
    Maze(const std::vector<std::vector<int>>& maze_grid, 
         Position s, Position e) 
        : grid(maze_grid), start(s), end(e) {
        rows = grid.size();
        cols = grid[0].size();
    }
    
    bool isValid(const Position& pos) const {
        return pos.row >= 0 && pos.row < rows &&
               pos.col >= 0 && pos.col < cols &&
               grid[pos.row][pos.col] == 0;
    }
    
    Position getStart() const { return start; }
    Position getEnd() const { return end; }
};
```

---

## Частина 2: BFS — пошук найкоротшого шляху

**Алгоритм:**
1. Додаємо стартову позицію до черги.
2. Поки черга не порожня:
   - Витягуємо позицію.
   - Якщо це ціль — знайшли!
   - Інакше додаємо всіх сусідів (вгору, вниз, ліворуч, праворуч) до черги.

Створіть заголовочний файл `BFS.h`:

```cpp
#include <queue>
#include <unordered_set>
#include <unordered_map>

// Хеш-функція для Position (щоб використовувати в unordered_set)
struct PositionHash {
    size_t operator()(const Position& p) const {
        return std::hash<int>()(p.row) ^ (std::hash<int>()(p.col) << 1);
    }
};

std::vector<Position> BFS(const Maze& maze) {
    std::queue<Position> q;
    std::unordered_set<Position, PositionHash> visited;
    std::unordered_map<Position, Position, PositionHash> parent; // Для відновлення шляху
    
    Position start = maze.getStart();
    Position end = maze.getEnd();
    
    q.push(start);
    visited.insert(start);
    
    // Напрямки руху: вгору, вниз, ліворуч, праворуч
    std::vector<Position> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    
    while (!q.empty()) {
        Position current = q.front();
        q.pop();
        
        if (current == end) {
            // Знайшли! Відновлюємо шлях
            return reconstructPath(parent, start, end);
        }
        
        // Перевіряємо всіх сусідів
        for (const auto& dir : directions) {
            Position neighbor = {current.row + dir.row, current.col + dir.col};
            
            if (maze.isValid(neighbor) && visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    
    return {}; // Шлях не знайдено
}

std::vector<Position> reconstructPath(
    const std::unordered_map<Position, Position, PositionHash>& parent,
    const Position& start,
    const Position& end) {
    
    std::vector<Position> path;
    Position current = end;
    
    while (!(current == start)) {
        path.push_back(current);
        current = parent.at(current);
    }
    
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}
```

---

## Частина 3: DFS — пошук будь-якого шляху

**Алгоритм (рекурсивний):**
1. Якщо поточна позиція = ціль → знайшли!
2. Інакше перевіряємо всіх сусідів рекурсивно.
3. Якщо сусід веде до цілі → повертаємо `true`.

Створіть заголовочний файл `DFS.h`:

```cpp
bool DFSRecursive(const Maze& maze, 
                  Position current, 
                  const Position& end,
                  std::unordered_set<Position, PositionHash>& visited,
                  std::vector<Position>& path) {
    
    if (current == end) {
        path.push_back(current);
        return true; // Знайшли!
    }
    
    visited.insert(current);
    path.push_back(current);
    
    std::vector<Position> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    
    for (const auto& dir : directions) {
        Position neighbor = {current.row + dir.row, current.col + dir.col};
        
        if (maze.isValid(neighbor) && visited.find(neighbor) == visited.end()) {
            if (DFSRecursive(maze, neighbor, end, visited, path)) {
                return true; // Шлях знайдено
            }
        }
    }
    
    // Backtracking: цей шлях не працює
    path.pop_back();
    return false;
}

std::vector<Position> DFS(const Maze& maze) {
    std::unordered_set<Position, PositionHash> visited;
    std::vector<Position> path;
    
    DFSRecursive(maze, maze.getStart(), maze.getEnd(), visited, path);
    return path;
}
```

---

## Частина 4: Візуалізація шляху та тестування

**Завдання:** Надрукуйте лабіринт з позначеним шляхом.

Створіть файл `main.cpp` та додайте наступний код:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include "Maze.h"
#include "BFS.h"
#include "DFS.h"

void printMaze(const Maze& maze, const std::vector<Position>& path) {
    auto grid = maze.getGrid();
    
    for (const auto& pos : path) {
        if (!(pos == maze.getStart()) && !(pos == maze.getEnd())) {
            grid[pos.row][pos.col] = 2; // Маркер шляху
        }
    }
    
    Position start = maze.getStart();
    Position end = maze.getEnd();
    
    for (int r = 0; r < (int)grid.size(); ++r) {
        for (int c = 0; c < (int)grid[r].size(); ++c) {
            Position pos = {r, c};
            if (pos == start) {
                std::cout << "S ";
            } else if (pos == end) {
                std::cout << "E ";
            } else if (grid[r][c] == 0) {
                std::cout << ". ";
            } else if (grid[r][c] == 1) {
                std::cout << "# ";
            } else if (grid[r][c] == 2) {
                std::cout << "* ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> grid1 = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0}
    };
    Maze maze1(grid1, {0, 0}, {3, 4});

    std::vector<std::vector<int>> grid2 = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 1},
        {1, 1, 1, 1, 0}
    };
    Maze maze2(grid2, {0, 0}, {3, 4});

    std::vector<std::vector<int>> grid3 = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1},
        {0, 0, 0, 1, 0, 0},
        {1, 1, 0, 0, 0, 0}
    };
    Maze maze3(grid3, {0, 0}, {5, 5});

    std::vector<std::pair<std::string, Maze>> test_cases = {
        {"Приклад 1: Стандартний лабіринт", maze1},
        {"Приклад 2: Непрохідний лабіринт", maze2},
        {"Приклад 3: Більший лабіринт", maze3}
    };

    for (const auto& [name, maze] : test_cases) {
        std::cout << "\n========================================\n";
        std::cout << name << "\n";
        std::cout << "========================================\n";

        std::cout << "\n=== BFS ===\n";
        auto bfs_path = BFS(maze);
        if (bfs_path.empty()) {
            std::cout << "Шлях не знайдено!\n";
        } else {
            std::cout << "Довжина шляху: " << bfs_path.size() << "\n";
            printMaze(maze, bfs_path);
        }

        std::cout << "\n=== DFS ===\n";
        auto dfs_path = DFS(maze);
        if (dfs_path.empty()) {
            std::cout << "Шлях не знайдено!\n";
        } else {
            std::cout << "Довжина шляху: " << dfs_path.size() << "\n";
            printMaze(maze, dfs_path);
        }
    }
}
```

### Компіляція та запуск

Для компіляції проекту за допомогою `g++` перейдіть у папку з файлами та виконайте:

```bash
g++ -std=c++17 main.cpp -o pathfinder
```

Для запуску програми:

```bash
./pathfinder
```

---

## Контрольні питання

1. Чому BFS гарантує найкоротший шлях, а DFS — ні?

<details markdown="1">
<summary>Відповідь</summary>

BFS досліджує лабіринт **рівнями** (спочатку всі клітинки на відстані 1, потім 2 тощо). Коли BFS досягає цілі, це гарантовано найкоротший шлях.

DFS йде **максимально глибоко** першим шляхом, який знайде. Це може бути довгий обхідний шлях, але DFS його прийме, бо не знає про коротші альтернативи.

</details>

2. Яка складність BFS і DFS для лабіринту розміром N x M?

<details markdown="1">
<summary>Відповідь</summary>

**O(N * M)** — у найгіршому випадку обидва алгоритми відвідують кожну клітинку. Але BFS використовує більше пам'яті (черга може зберігати багато позицій), тоді як DFS використовує стек рекурсії (глибина може бути великою).

</details>

3. Як адаптувати BFS для підрахунку кількості кроків до виходу?

<details markdown="1">
<summary>Відповідь</summary>

Зберігати відстань разом з позицією у черзі:

```cpp
std::queue<std::pair<Position, int>> q; // (позиція, відстань)
q.push({start, 0});

while (!q.empty()) {
    auto [current, distance] = q.front();
    q.pop();
    
    if (current == end) {
        return distance; // Повертаємо кількість кроків
    }
    
    // Додаємо сусідів з +1 до відстані
    q.push({neighbor, distance + 1});
}
```

</details>

