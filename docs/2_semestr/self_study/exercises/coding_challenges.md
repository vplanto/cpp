# Coding Challenges: Interactive Exercises

[← Back to Self-Study Guide](../modern_cpp_guide.md)

## How to Use This Guide

Each challenge follows this structure:
1. **Problem** — What needs to be fixed/improved
2. **Hints** — Progressive clues (expand if stuck)
3. **Solution** — Complete working code with explanations

**Learning Strategy:** Try solving without hints first, then progressively reveal hints if stuck.

---

## Challenge 1: Invariant Enforcement

**Difficulty:** ⭐⭐☆☆☆  
**Context:** [Lecture 13 - Encapsulation](../../13_oop_philosophy.md#invariants)  
**Time:** 15-20 minutes

### Problem

Refactor this `struct` into a `class` that enforces time validity.

```cpp
struct Time {
    int hours;
    int minutes;
};

// Current problem:
Time meeting = {25, 99};  // ❌ Compiles fine, but invalid time!
Time alarm = {-5, 30};     // ❌ Negative hours!
```

**Requirements:**
1. Convert to `class` with `private` members
2. Add constructor that validates:
   - `0 <= hours <= 23`
   - `0 <= minutes <= 59`
3. Add getters (`getHours()`, `getMinutes()`)
4. Add setter `setHours(int h)` that maintains invariant
5. Throw `std::invalid_argument` for invalid values

<details>
<summary>💡 Hint 1: Class Structure</summary>

Start with the basic structure:
```cpp
class Time {
private:
    int hours;
    int minutes;
    
public:
    Time(int h, int m) {
        // Validate and set here
    }
    
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
};
```
</details>

<details>
<summary>💡 Hint 2: Validation Logic</summary>

Use `if` statements to check ranges:
```cpp
if (h < 0 || h > 23) {
    throw std::invalid_argument("Hours must be 0-23");
}
```
</details>

<details>
<summary>💡 Hint 3: What About setMinutes?</summary>

You also need `setMinutes(int m)` with the same validation pattern!
</details>

<details>
<summary>✅ Complete Solution</summary>

```cpp
#include <stdexcept>
#include <string>

class Time {
private:
    int hours;
    int minutes;
    
    // Helper function to validate (DRY principle)
    void validateHours(int h) const {
        if (h < 0 || h > 23) {
            throw std::invalid_argument(
                "Hours must be 0-23, got " + std::to_string(h)
            );
        }
    }
    
    void validateMinutes(int m) const {
        if (m < 0 || m > 59) {
            throw std::invalid_argument(
                "Minutes must be 0-59, got " + std::to_string(m)
            );
        }
    }
    
public:
    // Constructor with validation
    Time(int h, int m) {
        validateHours(h);
        validateMinutes(m);
        hours = h;
        minutes = m;
    }
    
    // Getters (const methods)
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    
    // Setters with validation
    void setHours(int h) {
        validateHours(h);
        hours = h;
    }
    
    void setMinutes(int m) {
        validateMinutes(m);
        minutes = m;
    }
};

// Usage examples:
int main() {
    Time meeting(14, 30);  // ✓ Valid
    std::cout << meeting.getHours() << ":" << meeting.getMinutes();
    
    try {
        Time invalid(25, 99);  // ✗ Throws exception
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // Output: Error: Hours must be 0-23, got 25
    }
    
    try {
        meeting.setHours(-5);  // ✗ Throws exception
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
```

**Key Lessons:**
1. **Private members** prevent direct access
2. **Validation in constructor** ensures object never created in invalid state
3. **Validation in setters** maintains invariant throughout lifetime
4. **Helper functions** (DRY: Don't Repeat Yourself) reduce code duplication

</details>

---

## Challenge 2: Fix the Constructor Bug

**Difficulty:** ⭐⭐☆☆☆  
**Context:** [Lecture 13 - Constructors](../../13_oop_philosophy.md#constructors)  
**Time:** 10-15 minutes

### Problem

Find and fix the logic error in this constructor:

```cpp
class BankAccount {
private:
    std::string owner;
    double balance;
    
public:
    BankAccount(std::string name, double initial_balance) {
        owner = name;
        balance = initial_balance;  // ❌ Bug here!
    }
};

// Problem:
BankAccount acc("Alice", -1000.0);  // Should this be allowed?
```

**Requirements:**
1. Identify the bug (what invariant is missing?)
2. Add validation to prevent invalid state
3. Decide: throw exception or use default value?

<details>
<summary>💡 Hint: What's the invariant?</summary>

**Invariant:** Bank balance should never be negative (unless you support overdrafts).

Think: Should `BankAccount("Alice", -1000)` be allowed?
</details>

<details>
<summary>✅ Solution A: Throw Exception</summary>

```cpp
class BankAccount {
private:
    std::string owner;
    double balance;
    
public:
    BankAccount(std::string name, double initial_balance) {
        if (initial_balance < 0) {
            throw std::invalid_argument("Initial balance cannot be negative");
        }
        owner = name;
        balance = initial_balance;
    }
};

// Usage:
try {
    BankAccount acc("Alice", -1000.0);  // Throws
} catch (const std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
}
```

**When to use:** Strict validation (bank software, safety-critical systems)
</details>

<details>
<summary>✅ Solution B: Default to Safe Value</summary>

```cpp
class BankAccount {
private:
    std::string owner;
    double balance;
    
public:
    BankAccount(std::string name, double initial_balance) {
        owner = name;
        balance = (initial_balance < 0) ? 0.0 : initial_balance;
        // Negative values clamped to 0
    }
};

// Usage:
BankAccount acc("Alice", -1000.0);  // balance = 0.0 (silent fix)
```

**When to use:** Lenient systems (games, UI sliders)
</details>

**Discussion:** Which approach is better? Depends on context!
- **Banking/Medical:** Exception (fail fast, don't hide errors)
- **Games/UI:** Silent clamp (user experience over strict correctness)

---

## Challenge 3: Big-O Complexity Estimation

**Difficulty:** ⭐⭐⭐☆☆  
**Context:** [Lecture 19 - Complexity](../../19_complexity_profiling.md)  
**Time:** 20 minutes

### Problem

Determine the time complexity of these code snippets. **Don't run the code yet!** Analyze first.

#### Snippet A
```cpp
void mysteryA(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {  // ← Trick!
            std::cout << i << "," << j << std::endl;
        }
    }
}
```

#### Snippet B
```cpp
void mysteryB(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        vec.push_back(i);  // ← Danger!
    }
}
```

#### Snippet C
```cpp
int mysteryC(int n) {
    if (n <= 1) return 1;
    return mysteryC(n - 1) + mysteryC(n - 2);  // ← Expensive!
}
```

<details>
<summary>💡 Hint for A</summary>

Inner loop runs a **constant** 10 times. Does that depend on `n`?
</details>

<details>
<summary>💡 Hint for B</summary>

Every iteration adds an element. What happens to `vec.size()`?
</details>

<details>
<summary>💡 Hint for C</summary>

Draw the recursion tree for `n=5`. How many times is each level called?
</details>

<details>
<summary>✅ Solutions</summary>

### Snippet A: $O(n)$ ← Trick Question!

```cpp
void mysteryA(int n) {
    for (int i = 0; i < n; i++) {          // n iterations
        for (int j = 0; j < 10; j++) {      // 10 iterations (constant!)
            // ...
        }
    }
}
// Total: n * 10 = 10n = O(n)  (NOT O(n²)!)
```

**Common mistake:** "Two nested loops = $O(n^2)$"  
**Truth:** Inner loop is constant → $O(n \times 10) = O(n)$

---

### Snippet B: **INFINITE LOOP!**

```cpp
void mysteryB(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {  // size() grows every iteration!
        vec.push_back(i);  // Adds element → size() increases
    }
}
// i=0: vec.size()=1, add 0 → size()=2
// i=1: vec.size()=2, add 1 → size()=3
// i=2: vec.size()=3, add 2 → size()=4
// → Loop NEVER ends! (until out of memory)
```

**Fix:**
```cpp
size_t original_size = vec.size();
for (size_t i = 0; i < original_size; i++) {
    vec.push_back(i);
}
```

---

### Snippet C: $O(2^n)$ — Exponential!

```cpp
int mysteryC(int n) {
    if (n <= 1) return 1;
    return mysteryC(n-1) + mysteryC(n-2);  // Fibonacci
}
```

**Recursion tree for `n=5`:**
```
                   fib(5)
                /          \
            fib(4)          fib(3)
           /      \        /      \
       fib(3)   fib(2)  fib(2)  fib(1)
       /   \    /   \   /   \
    fib(2) fib(1) ...
```

**Count:** Each level roughly doubles → $O(2^n)$

**For `n=40`:** ~1 billion calls (~1 second)  
**For `n=50`:** ~1 trillion calls (~17 minutes!)

**Fix: Memoization (Dynamic Programming):**
```cpp
std::unordered_map<int, int> cache;

int fibonacci(int n) {
    if (n <= 1) return 1;
    if (cache.count(n)) return cache[n];  // ✓ Check cache
    
    cache[n] = fibonacci(n-1) + fibonacci(n-2);
    return cache[n];
}
// Complexity: O(n) — each fib(k) computed only once!
```

</details>

---

## Challenge 4: Cache-Friendly Iteration

**Difficulty:** ⭐⭐⭐⭐☆  
**Context:** [Lecture 19 - Hardware Latency](../../19_complexity_profiling.md#hardware)  
**Time:** 30 minutes (includes benchmarking)

### Problem

Which is faster: iterating a `std::vector` or `std::list` with 1 million elements?

**Prediction:** Both are $O(n)$. Should be same speed, right?

```cpp
// Version A: std::vector
std::vector<int> vec(1000000);
int sum = 0;
for (int val : vec) {
    sum += val;
}

// Version B: std::list
std::list<int> lst(1000000);
int sum = 0;
for (int val : lst) {
    sum += val;
}
```

<details>
<summary>💡 Hint: Memory Layout</summary>

- **Vector:** Elements stored contiguously in memory  
  `[0][1][2][3][4]...` (cache-friendly)

- **List:** Elements scattered (each node = separate allocation)  
  `[0]→[1]→[2]→[3]→[4]...` (cache-hostile)

Which one benefits from CPU cache?
</details>

<details>
<summary">✅ Solution + Benchmark Code</summary>

```cpp
#include <vector>
#include <list>
#include <chrono>
#include <iostream>

template <typename Container>
long long benchmark(Container& container) {
    auto start = std::chrono::high_resolution_clock::now();
    
    long long sum = 0;
    for (auto val : container) {
        sum += val;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {
    const int N = 1'000'000;
    
    // Vector
    std::vector<int> vec(N, 1);
    long long time_vec = benchmark(vec);
    
    // List
    std::list<int> lst(N, 1);
    long long time_lst = benchmark(lst);
    
    std::cout << "Vector: " << time_vec << " ms\n";
    std::cout << "List:   " << time_lst << " ms\n";
    std::cout << "List is " << (time_lst / time_vec) << "x slower\n";
}
```

**Typical Results:**
```
Vector: 2 ms
List:   50 ms
List is 25x slower
```

**Why?**
- **Vector:** Sequential memory → CPU prefetches next elements → L1 cache hits
- **List:** Random memory access → cache miss for every node → wait for RAM

**Lesson:** Big-O notation doesn't capture hardware reality!

</details>

---

## Challenge 5: Hidden Copy Bug

**Difficulty:** ⭐⭐⭐☆☆  
**Context:** [Lecture 24 - Performance](../../24_performance_optimization.md)  
**Time:** 15 minutes

### Problem

Find the performance bug in this code:

```cpp
std::vector<std::string> loadNames(const std::string& filename) {
    // Loads 1 million names from file
    // Each name: ~20 characters
}

int main() {
    auto names = loadNames("database.txt");
    
    for (auto name : names) {  // ❌ Bug here!
        if (name.length() > 10) {
            processLongName(name);
        }
    }
}
```

**Hint:** Look carefully at the type of `name` in the loop.

<details>
<summary>💡 Hint: Copy vs Reference</summary>

What does `auto name` deduce to? `std::string` or `std::string&`?

Remember: `auto` deduces **by value** unless you explicitly use `&`!
</details>

<details>
<summary>✅ Solution</summary>

**Bug:** `auto name` creates a **copy** of each string!

With 1 million strings × 20 bytes each:
- **Copied data:** 20 MB
- **Allocation overhead:** ~1 million `malloc()` calls
- **Time:** ~500 ms

**Fix:**
```cpp
for (const auto& name : names) {  // ← Reference, not copy!
    if (name.length() > 10) {
        processLongName(name);
    }
}
// Time: ~50 ms (10x faster!)
```

**Rule:** **Always use `const auto&` in range-based for loops** unless you need to modify the copy.

**Exception:** For cheap-to-copy types (int, double, small structs), `auto` is fine:
```cpp
std::vector<int> numbers = {1, 2, 3};
for (auto num : numbers) {  // OK: int is cheap to copy (4 bytes)
    std::cout << num;
}
```

</details>

---

## Challenge 6: std::endl Performance Trap

**Difficulty:** ⭐⭐☆☆☆  
**Context:** [Lecture 24 - I/O Performance](../../24_performance_optimization.md)  
**Time:** 20 minutes (includes benchmarking)

### Problem

Benchmark the performance difference between `std::endl` and `'\n'`.

Write 1 million lines to a file using:
1. `std::endl`
2. `'\n'`

Measure the time difference.

<details>
<summary>💡 Hint: What does std::endl do?</summary>

`std::endl` = `'\n'` + `flush()`

Flushing forces immediate write to disk (bypasses buffer).
</details>

<details>
<summary>✅ Benchmark Code</summary>

```cpp
#include <fstream>
#include <chrono>
#include <iostream>

long long benchmark_endl() {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::ofstream file("output_endl.txt");
    for (int i = 0; i < 1'000'000; i++) {
        file << i << std::endl;  // Flushes every line!
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

long long benchmark_newline() {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::ofstream file("output_newline.txt");
    for (int i = 0; i < 1'000'000; i++) {
        file << i << '\n';  // Buffered
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {
    long long time_endl = benchmark_endl();
    long long time_newline = benchmark_newline();
    
    std::cout << "std::endl: " << time_endl << " ms\n";
    std::cout << "'\\n':      " << time_newline << " ms\n";
    std::cout << "std::endl is " << (time_endl / time_newline) << "x slower\n";
}
```

**Typical Results:**
```
std::endl: 5000 ms (5 seconds!)
'\n':      500 ms
std::endl is 10x slower
```

**Why?**
- `std::endl` flushes buffer to disk every line (1M system calls)
- `'\n'` writes to buffer, OS flushes when buffer full (~100 system calls)

**Rule:** Use `'\n'` unless you **need** immediate flush (e.g., logging before crash).

</details>

---

## Summary: What These Challenges Teach

| Challenge | Concept | Key Takeaway |
|-----------|---------|--------------|
| **Invariant Enforcement** | Encapsulation | Private + validation = impossible invalid state |
| **Constructor Bug** | Invariants | Constructors must establish invariants |
| **Big-O Estimation** | Complexity | Constant loops ≠ $O(n^2)$, watch for infinite loops |
| **Cache Performance** | Hardware | Big-O ignores cache effects (25× real-world difference) |
| **Hidden Copy** | References | Always `const auto&` for range-based loops |
| **endl Performance** | I/O | Flushing is expensive, use `'\n'` |

---

## Next Steps

- [Quick Reference](../quick_reference/cheatsheet.md) — Decision trees and cheat sheets
- [Legacy to Modern](../upgrades/legacy_to_modern.md) — See production patterns

[← Back to Self-Study Guide](../modern_cpp_guide.md)
