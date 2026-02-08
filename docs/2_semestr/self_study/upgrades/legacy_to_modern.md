# Legacy to Modern: C++ Upgrade Guide

[← Back to Self-Study Guide](../modern_cpp_guide.md)

## Philosophy: Understanding Before Upgrading

Each pattern below shows:
1. **Educational Pattern (C++98/11)** — What you learn in lectures to understand fundamentals
2. **Production Pattern (C++20/23)** — What you write in real projects
3. **When to use each** — Context matters!

---

## Pattern 1: Raw Pointers → Standard Containers

**Context:** [Lecture 13 - OOP Philosophy](../../13_oop_philosophy.md)

### ⚠️ Educational Pattern (C++98)

```cpp
class Player {
    int* inventory;
    int size;
public:
    Player(int n) {
        inventory = new int[n];  // Manual allocation
        size = n;
    }
    
    ~Player() {
        delete[] inventory;  // Manual cleanup - easy to forget!
    }
    
    // ❌ Missing: Copy constructor and copy assignment operator
    // Without these, copying will cause DOUBLE FREE crash!
};
```

**Problems:**
- Requires manual `delete[]` (resource leak if forgotten)
- Need to implement Rule of Three (copy ctor, copy assign, dtor)
- Exception unsafe: if constructor throws after `new`, memory leaks
- 100 lines of boilerplate for basic functionality

### ✅ Production Pattern (C++20)

```cpp
class Player {
    std::vector<int> inventory;  // Self-managing, exception-safe
public:
    Player(int n) : inventory(n) {}
    
    // That's it! Compiler generates:
    // - Destructor (calls vector's destructor)
    // - Copy constructor (deep copy automatically)
    // - Copy assignment (deep copy automatically)
    // - Move constructor (efficient transfer)
    // - Move assignment (efficient transfer)
};
```

**Benefits:**
- **Rule of Zero:** No custom destructor needed
- **Exception Safe:** Vector cleans up automatically on exceptions
- **Correct by Default:** Copying works without custom code
- **Performance:** Can `reserve()` capacity to avoid reallocations

### When to Use Each

| Scenario | Use |
|----------|-----|
| **Dynamic size, frequent changes** | `std::vector<T>` |
| **Fixed size known at compile time** | `std::array<T, N>` |
| **View of existing array (no ownership)** | `std::span<T>` (C++20) |
| **Interfacing with C API** | Raw pointer (but wrap in RAII) |

**Performance:** `std::vector` has **zero overhead** compared to manual `new[]` when properly used with `reserve()`.

---

## Pattern 2: Manual Delete → Smart Pointers

**Context:** [Lecture 14 - RAII](../../14_raii_lifecycle.md)

### ⚠️ Educational Pattern

```cpp
class Document {
    File* file;
public:
    Document(const std::string& path) {
        file = new File(path);
        if (!file->isOpen()) {
            delete file;  // ❌ Must remember to clean up!
            throw std::runtime_error("Failed");
        }
    }
    
    ~Document() {
        delete file;  // ❌ Must remember!
    }
    
    // ❌ Missing: Copy and move operations
};
```

**Problems:**
- Manual `delete` in destructor (easy to forget)
- Manual cleanup in error paths
- Copy operations undefined (will crash if copied)

### ✅ Production Pattern

```cpp
class Document {
    std::unique_ptr<File> file;
public:
    Document(const std::string& path) 
        : file(std::make_unique<File>(path)) {
        if (!file->isOpen()) {
            throw std::runtime_error("Failed");
            // ✓ file automatically cleaned up even on exception!
        }
    }
    
    // ✓ No destructor needed
    // ✓ Copy deleted automatically (unique ownership)
    // ✓ Move works correctly
};
```

**The Rule:** *The best destructor is the one you don't write.*

### Smart Pointer Decision Tree

```
Need dynamic allocation?
├─ No → Use std::vector or std::array
└─ Yes → Shared ownership?
    ├─ Yes → std::shared_ptr<T>
    └─ No → std::unique_ptr<T>
```

**Performance:**
- `std::unique_ptr`: **Zero overhead** (same as raw pointer)
- `std::shared_ptr`: Small overhead (reference counting)

---

## Pattern 3: Templates → Concepts (Readable Errors!)

**Context:** [Lecture 17 - Generics](../../17_generics_operators.md)

### ⚠️ C++11 Pattern

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

add(std::string("hello"), std::string("world"));
```

**Error message (GCC):**
```
error: no match for 'operator+' (operand types are 'std::string' and 'std::string')
...
[200 lines of template instantiation context]
...
In instantiation of 'T add(T, T) [with T = std::basic_string<char>]'
...
```

😱 **200 lines of compiler spew!**

### ✅ C++20 Pattern

```cpp
template <std::integral T>  // ← Concept constraint
T add(T a, T b) {
    return a + b;
}

add(std::string("hello"), std::string("world"));
```

**Error message (GCC with C++20):**
```
error: 'std::string' does not satisfy 'std::integral'
note: the concept 'std::integral<std::string>' evaluated to false
```

✅ **1 line, human-readable!**

### Common Standard Concepts

```cpp
#include <concepts>

// Numeric types
std::integral<T>           // int, long, short, char, etc.
std::floating_point<T>     // float, double, long double
std::signed_integral<T>    // signed int types
std::unsigned_integral<T>  // unsigned int types

// Type relationships
std::same_as<T, U>         // Exact type match
std::convertible_to<From, To>  // Safe conversion exists
std::derived_from<Derived, Base>  // Inheritance check

// Operations
std::copyable<T>           // Can be copied
std::movable<T>            // Can be moved
std::equality_comparable<T>  // Has operator==
```

### Custom Concepts

```cpp
template <typename T>
concept Drawable = requires(T obj) {
    { obj.draw() } -> std::same_as<void>;
    { obj.getColor() } -> std::convertible_to<std::string>;
};

// Now use it:
template <Drawable T>
void render(T shape) {
    shape.draw();  // ✓ Guaranteed to exist at compile time
}
```

---

## Pattern 4: Verbose Operators → Abbreviated Templates

**Context:** [Lecture 17 - Operator Overloading](../../17_generics_operators.md)

### ⚠️ C++11 Pattern

```cpp
class Vector2D {
public:
    double x, y;
    
    const Vector2D operator+(const Vector2D& other) const {
        return Vector2D{x + other.x, y + other.y};
    }
    
    template <typename T>
    const Vector2D operator*(const T& scalar) const {
        return Vector2D{x * scalar, y * scalar};
    }
};
```

### ✅ C++20 Pattern (Abbreviated Function Templates)

```cpp
class Vector2D {
public:
    double x, y;
    
    auto operator+(std::same_as<Vector2D> auto const& other) const {
        return Vector2D{x + other.x, y + other.y};
    }
    
    auto operator*(std::integral auto const& scalar) const {
        return Vector2D{x * scalar, y * scalar};
    }
};
```

**Benefits:**
- More concise syntax
- Type constraints visible in signature
- Better error messages

---

## Pattern 5: Raw Arrays → std::span (Bounds Safety)

**Context:** [Lecture 20 - Vectors and Lists](../../20_lists_vector.md)

### ⚠️ C-Style Pattern

```cpp
void processArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
    // ❌ No bounds checking
    // ❌ Easy to pass wrong size
    // ❌ Doesn't work with std::vector without .data()
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    processArray(arr, 5);  // Have to pass size manually
}
```

**Problems:**
- Size and pointer are separate (can mismatch)
- No bounds checking (buffer overflow risk)
- Doesn't work with `std::vector` or `std::array` directly

### ✅ C++20 Pattern (std::span)

```cpp
#include <span>

void processArray(std::span<int> arr) {  // ← Knows its size!
    for (int& val : arr) {  // Range-based for works!
        val *= 2;
    }
    // ✓ Bounds checked (with .at())
    // ✓ Works with arrays, vectors, arrays—anything contiguous
}

int main() {
    // Works with C-style array
    int arr[5] = {1, 2, 3, 4, 5};
    processArray(arr);  // ✓ Size deduced automatically
    
    // Works with std::vector
    std::vector<int> vec = {1, 2, 3, 4, 5};
    processArray(vec);  // ✓ No .data() needed!
    
    // Works with std::array
    std::array<int, 5> stdarr = {1, 2, 3, 4, 5};
    processArray(stdarr);  // ✓ Works seamlessly
}
```

**Benefits:**
- **Size bundled with pointer** (no mismatch errors)
- **Works with any contiguous container** (array, vector, std::array)
- **Bounds checking available** (`arr.at(i)` throws on out-of-bounds)
- **Zero overhead** (just two pointers: begin and end)

---

## Pattern 6: std::endl → std::print (Performance + Readability)

**Context:** [Lecture 24 - I/O Performance](../../24_performance_optimization.md)

### ⚠️ Traditional Pattern

```cpp
#include <iostream>

int main() {
    int x = 42;
    std::string name = "Alice";
    
    // Old way:
    std::cout << "Hello, " << name << "! Your value is " << x << std::endl;
    //                                                              ^^^^^^
    //                                                     Flushes buffer! Slow!
}
```

**Problems:**
- `std::endl` **flushes the buffer** (forces write to disk/terminal)
- Flushing is expensive (~1000x slower than buffering)
- Verbose syntax for complex formatting

### ✅ C++20 Pattern (std::format)

```cpp
#include <format>
#include <iostream>

int main() {
    int x = 42;
    std::string name = "Alice";
    
    // C++20 way:
    std::cout << std::format("Hello, {}! Your value is {}\n", name, x);
    //                                                        ^^
    //                                                  Just newline, no flush
}
```

### ✅ C++23 Pattern (std::print) — Even Better!

```cpp
#include <print>  // C++23

int main() {
    int x = 42;
    std::string name = "Alice";
    
    // C++23 way:
    std::print("Hello, {}! Your value is {}\n", name, x);
    // ✓ Type-safe
    // ✓ No flush overhead
    // ✓ Python-like syntax
}
```

**Performance Comparison (writing 1 million lines):**

| Method | Time |
|--------|------|
| `std::cout << ... << std::endl` | 5000ms (flushes every line) |
| `std::cout << ... << "\n"` | 500ms (buffered) |
| `std::format` + `std::cout` | 450ms (type-safe formatting) |
| `std::print` | 400ms (optimized for output) |

**Rule:** Use `\n` instead of `std::endl` unless you **need** to flush (rare).

### Fallback: {fmt} Library

If your compiler doesn't support C++23 yet:
```cpp
#include <fmt/core.h>  // fmt library (C++11 compatible)

fmt::print("Hello, {}! Your value is {}\n", name, x);
```

Install: `sudo apt install libfmt-dev` or use vcpkg/conan

---

## Pattern 7: String Conversion (atoi/stoi → std::from_chars)

**Context:** [Lecture 24 - Performance (1 Billion Row Challenge)](../../24_performance_optimization.md)

### ⚠️ Traditional Patterns

```cpp
#include <cstdlib>  // C library
#include <string>   // C++ library

// C-style (atoi)
int value1 = atoi("12345");
// ❌ No error handling (returns 0 on failure)
// ❌ Slow (locale-aware, dynamic allocation)

// C++11 (stoi)
int value2 = std::stoi("12345");
// ✓ Throws exception on error
// ❌ Still slow (allocates std::string, locale-aware)
```

**Performance:** ~50ns per conversion (1B rows = 50 seconds!)

### ✅ C++17 Pattern (std::from_chars)

```cpp
#include <charconv>
#include <string_view>

int parse_int(std::string_view str) {
    int value;
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);
    
    if (ec == std::errc{}) {
        return value;  // Success
    } else {
        throw std::runtime_error("Parse error");
    }
}

int main() {
    int value = parse_int("12345");
    // ✓ No exceptions in hot path
    // ✓ No dynamic allocation
    // ✓ Locale-independent (predictable)
}
```

**Performance:** ~5ns per conversion (10x faster!)

**1 Billion rows:** 5 seconds vs 50 seconds — **45 second savings!**

### Error Handling

```cpp
auto [ptr, ec] = std::from_chars(data, data + size, value);

if (ec == std::errc::invalid_argument) {
    // Invalid characters in input
} else if (ec == std::errc::result_out_of_range) {
    // Number too large for int
} else {
    // Success: value contains the parsed number
}
```

---

## Summary: The Modern C++ Philosophy

| **Principle** | **Old Way** | **New Way** |
|---------------|-------------|-------------|
| **Memory** | `new` / `delete` | `std::vector` / `std::unique_ptr` |
| **Ownership** | Manual tracking | Smart pointers |
| **Arrays** | `int* arr, int size` | `std::span<int>` |
| **Templates** | SFINAE hell | Concepts |
| **I/O** | `std::cout <<` + `endl` | `std::print` / `std::format` |
| **Parsing** | `atoi` / `stoi` | `std::from_chars` |

**Golden Rule:** If you're writing `new`, `delete`, or manual size tracking, you're doing it wrong in modern C++!

---

## Next Steps

- [Visual Diagrams](../visuals/memory_diagrams.md) — See these patterns in action
- [Coding Challenges](../exercises/coding_challenges.md) — Practice refactoring legacy code
- [Quick Reference](../quick_reference/cheatsheet.md) — Fast lookup

[← Back to Self-Study Guide](../modern_cpp_guide.md)
