# Практикум 19: Building a Binary Search Tree — Реалізація та Візуалізація

← [Index](index.md)

**Теорія:** [Лекція 26: Tree Data Structures](26_tree_structures.md)

---

## Роль: Data Structure Engineer

Ви — інженер, який працює над власною реалізацією key-value store. Щоб зрозуміти, як працює `std::map`, ви створюєте власне Binary Search Tree з нуля.

---

## Частина 0: Структура проекту

```
bst_project/
├── bst.h              # BST клас та операції
├── visualizer.h       # ASCII візуалізація
├── test_bst.cpp       # Тести
├── benchmark.cpp      # Порівняння з std::map
└── Makefile
```

---

## Частина 1: Базова структура BST

### bst.h

```cpp
#pragma once
#include <iostream>
#include <queue>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;
    
    Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST {
private:
    Node* root;
    
    // Допоміжні рекурсивні функції
    Node* insert_helper(Node* node, int key);
    Node* search_helper(Node* node, int key);
    Node* delete_helper(Node* node, int key);
    Node* find_min_helper(Node* node);
    void destroy_tree(Node* node);
    
public:
    BST() : root(nullptr) {}
    
    ~BST() {
        destroy_tree(root);
    }
    
    void insert(int key) {
        root = insert_helper(root, key);
    }
    
    bool search(int key) {
        return search_helper(root, key) != nullptr;
    }
    
    void remove(int key) {
        root = delete_helper(root, key);
    }
    
    Node* get_root() const { return root; }
};

// Вставка
Node* BST::insert_helper(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }
    
    if (key < node->key) {
        node->left = insert_helper(node->left, key);
        node->left->parent = node;
    } else if (key > node->key) {
        node->right = insert_helper(node->right, key);
        node->right->parent = node;
    }
    
    return node;
}

// Пошук
Node* BST::search_helper(Node* node, int key) {
    if (node == nullptr || node->key == key) {
        return node;
    }
    
    if (key < node->key) {
        return search_helper(node->left, key);
    } else {
        return search_helper(node->right, key);
    }
}

// Знайти мінімум
Node* BST::find_min_helper(Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Видалення
Node* BST::delete_helper(Node* node, int key) {
    if (node == nullptr) return node;
    
    if (key < node->key) {
        node->left = delete_helper(node->left, key);
    } else if (key > node->key) {
        node->right = delete_helper(node->right, key);
    } else {
        // Знайшли вузол для видалення
        
        // Випадок 1: немає лівої дитини
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        // Випадок 2: немає правої дитини
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        
        // Випадок 3: дві дитини
        Node* successor = find_min_helper(node->right);
        node->key = successor->key;
        node->right = delete_helper(node->right, successor->key);
    }
    
    return node;
}

// Деструктор
void BST::destroy_tree(Node* node) {
    if (node) {
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }
}
```

---

## Частина 2: ASCII Візуалізація

### visualizer.h

```cpp
#pragma once
#include "bst.h"
#include <iostream>
#include <string>

class TreeVisualizer {
public:
    static void print_tree(Node* root, std::string prefix = "", bool is_left = true) {
        if (root == nullptr) {
            return;
        }
        
        std::cout << prefix;
        std::cout << (is_left ? "├──" : "└──");
        std::cout << root->key << "\\n";
        
        std::string new_prefix = prefix + (is_left ? "│   " : "    ");
        
        if (root->left || root->right) {
            if (root->left) {
                print_tree(root->left, new_prefix, true);
            } else {
                std::cout << new_prefix << "├──" << "null\\n";
            }
            
            if (root->right) {
                print_tree(root->right, new_prefix, false);
            } else {
                std::cout << new_prefix << "└──" << "null\\n";
            }
        }
    }
    
    // Горизонтальна візуалізація
    static void print_horizontal(Node* root, int space = 0, int height = 10) {
        if (root == nullptr) {
            return;
        }
        
        space += height;
        
        print_horizontal(root->right, space);
        
        std::cout << std::string(space - height, ' ') << root->key << "\\n";
        
        print_horizontal(root->left, space);
    }
};
```

---

## Частина 3: Тестування BST

### test_bst.cpp

```cpp
#include "bst.h"
#include "visualizer.h"
#include <iostream>

int main() {
    BST tree;
    
    // Тест 1: Вставка
    std::cout << "=== Test 1: Insertion ===\\n";
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);
    tree.insert(7);
    tree.insert(13);
    
    std::cout << "Tree after insertions:\\n";
    TreeVisualizer::print_tree(tree.get_root());
    
    // Тест 2: Пошук
    std::cout << "\\n=== Test 2: Search ===\\n";
    std::cout << "Search 6: " << (tree.search(6) ? "Found" : "Not found") << "\\n";
    std::cout << "Search 15: " << (tree.search(15) ? "Found" : "Not found") << "\\n";
    
    // Тест 3: Видалення листа
    std::cout << "\\n=== Test 3: Delete leaf (4) ===\\n";
    tree.remove(4);
    TreeVisualizer::print_tree(tree.get_root());
    
    // Тест 4: Видалення вузла з одною дитиною
    std::cout << "\\n=== Test 4: Delete node with one child (14) ===\\n";
    tree.remove(14);
    TreeVisualizer::print_tree(tree.get_root());
    
    // Тест 5: Видалення вузла з двома дітьми
    std::cout << "\\n=== Test 5: Delete node with two children (3) ===\\n";
    tree.remove(3);
    TreeVisualizer::print_tree(tree.get_root());
    
    // Тест 6: Горизонтальна візуалізація
    std::cout << "\\n=== Horizontal View ===\\n";
    TreeVisualizer::print_horizontal(tree.get_root());
    
    return 0;
}
```

**Очікуваний вивід (приклад):**
```
=== Test 1: Insertion ===
Tree after insertions:
├──8
│   ├──3
│   │   ├──1
│   │   │   ├──null
│   │   │   └──null
│   │   └──6
│   │       ├──4
│   │       └──7
│   └──10
│       ├──null
│       └──14
│           ├──13
│           └──null
```

---

## Частина 4: Ротації (підготовка до RB-дерев)

### Додайте до bst.h

```cpp
// Ліва ротація
Node* rotate_left(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    x->parent = y;
    y->left = x;
    
    return y;
}

// Права ротація
Node* rotate_right(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    
    x->parent = y->parent;
    y->parent = x;
    x->right = y;
    
    return x;
}
```

### Тест ротацій

```cpp
#include "bst.h"
#include "visualizer.h"

int main() {
    BST tree;
    tree.insert(3);
    tree.insert(1);
    tree.insert(5);
    tree.insert(4);
    tree.insert(6);
    
    std::cout << "Before rotation:\\n";
    TreeVisualizer::print_horizontal(tree.get_root());
    
    // Виконуємо ліву ротацію на корені
    Node* new_root = tree.rotate_left(tree.get_root());
    
    std::cout << "\\nAfter left rotation on 3:\\n";
    TreeVisualizer::print_horizontal(new_root);
    
    return 0;
}
```

---

## Частина 5: Benchmark — BST vs std::map

### benchmark.cpp

```cpp
#include "bst.h"
#include <map>
#include <iostream>
#include <chrono>
#include <random>

class Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::string name;
public:
    Timer(const std::string& n) : name(n) {
        start = std::chrono::high_resolution_clock::now();
    }
    
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "[" << name << "] " << ms.count() << " ms\\n";
    }
};

int main() {
    const int N = 100'000;
    std::vector<int> data;
    
    // Генеруємо випадкові числа
    std::mt19937 rng(42);
    for (int i = 0; i < N; i++) {
        data.push_back(rng() % 1000000);
    }
    
    // Тест 1: Вставка у наше BST
    {
        Timer t("BST insert");
        BST tree;
        for (int val : data) {
            tree.insert(val);
        }
    }
    
    // Тест 2: Вставка у std::map
    {
        Timer t("std::map insert");
        std::map<int, int> map;
        for (int val : data) {
            map[val] = val;
        }
    }
    
    // Тест 3: Найгірший випадок (послідовна вставка)
    std::cout << "\\n=== Worst case: Sequential insertion ===\\n";
    
    {
        Timer t("BST sequential");
        BST tree;
        for (int i = 0; i < 10'000; i++) {
            tree.insert(i);
        }
    }
    
    {
        Timer t("std::map sequential");
        std::map<int, int> map;
        for (int i = 0; i < 10'000; i++) {
            map[i] = i;
        }
    }
    
    return 0;
}
```

**Очікувані результати:**
```
[BST insert] 85 ms
[std::map insert] 45 ms

=== Worst case: Sequential insertion ===
[BST sequential] 1250 ms  (деградація до O(n²)!)
[std::map sequential] 12 ms  (RB-tree балансування!)
```

**Висновок:** Незбалансоване BST деградує до O(n) висоти при послідовній вставці, тоді як std::map (Red-Black tree) залишається O(log n).

---

## Контрольні питання

1. Чому видалення вузла з двома дітьми вимагає знаходження наступника (successor)?

<details markdown="1">
<summary>Відповідь</summary>

Щоб зберегти BST властивість після видалення. **Наступник** — це найменший елемент у правому піддереві, тобто він більший за всі елементи у лівому піддереві видаленого вузла, але менший за всі інші у правому. Тому він може безпечно замінити видалений вузол.

</details>

2. Чи можна реалізувати BST без рекурсії?

<details markdown="1">
<summary>Відповідь</summary>

**Так!** Всі операції можна зробити ітеративно:
- insert: while loop, йдемо вліво/вправо
- search: while loop
- delete: складніше, але можливо з явним стеком

Рекурсія просто зручніша для читання.

</details>

3. Чому у benchmark послідовна вставка у BST така повільна?

<details markdown="1">
<summary>Відповідь</summary>

Вставка 1,2,3,...,N створює лінійний ланцюжок (кожен вузол має тільки праву дитину). Висота = N, тому кожна вставка коштує O(N) → загальна складність O(N²).

std::map (RB-tree) балансується після кожної вставки, тому висота залишається O(log N) → загальна складність O(N log N).

</details>

4. Як перевірити, чи є дерево валідним BST?

<details markdown="1">
<summary>Відповідь</summary>

Рекурсивна перевірка з передачею мінімуму та максимуму:

```cpp
bool is_valid_bst(Node* node, int min_val, int max_val) {
    if (!node) return true;
    
    if (node->key <= min_val || node->key >= max_val) {
        return false;
    }
    
    return is_valid_bst(node->left, min_val, node->key) &&
           is_valid_bst(node->right, node->key, max_val);
}
```

Викликати: `is_valid_bst(root, INT_MIN, INT_MAX)`.

</details>
