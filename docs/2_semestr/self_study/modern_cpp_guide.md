# Modern C++ Self-Study Guide

[← Back to Main Index](../index.md)

## Overview

The main lectures teach C++ fundamentals using C++11/14 patterns to ensure you understand **how things work under the hood**. This self-study guide shows you **modern C++20/23 alternatives** used in production codebases.

**Why learn both?**
- **Core Lectures:** Understand memory management, why RAII exists, how virtual functions work
- **This Guide:** Learn what professional C++ engineers actually write in 2024+

## Learning Path

```
1. ✅ Complete the main lecture (understand fundamentals)
2. 📖 Read WHY the pattern exists (core concepts)
3. 🚀 Learn the MODERN alternative (this guide)
4. 💻 Practice with interactive exercises
```

---

## Modules

### 📚 [Legacy to Modern Upgrades](upgrades/legacy_to_modern.md)

Side-by-side comparisons of C++98/11 → C++20/23 patterns

**Topics:**
- Raw pointers → `std::vector` / `std::array` (Rule of Zero)
- Manual `delete` → `std::unique_ptr` / `std::shared_ptr`
- Templates → Concepts (readable errors!)
- Raw arrays → `std::span` (bounds safety)
- `std::endl` → `std::print` (performance)
- String conversion upgrades

**Best for:** Understanding "this is how I learned it, but how do professionals do it?"

---

### 🎨 [Visual Diagrams](visuals/memory_diagrams.md)

Mermaid diagrams for invisible runtime concepts

**Topics:**
- 3-Compartment Box Model (UML class diagram)
- Shallow vs Deep Copy (memory graph)
- V-Table Dynamic Dispatch (flowchart)
- Vector Reallocation (sequence diagram)

**Best for:** Visual learners who want to "see" memory layout and execution flow

---

### 💻 [Coding Challenges](exercises/coding_challenges.md)

Interactive exercises with hints and full solutions

**Challenges:**
- Refactor `struct` to `class` with invariants
- Debug constructor errors
- Estimate Big-O complexity (tricky cases)
- Find hidden performance bugs
- Benchmark `std::endl` vs `\n`

**Best for:** Hands-on practice and testing your understanding

---

### ⚡ [Quick Reference Cheatsheet](quick_reference/cheatsheet.md)

Fast lookup for modern C++ patterns

**Topics:**
- Smart pointer decision tree
- Container selection guide
- Rule of Zero vs Rule of Five
- Concepts quick syntax
- Common pitfalls and fixes

**Best for:** Quick reference while coding, exam prep

---

## When to Use This Guide

| Situation | Recommendation |
|-----------|----------------|
| **Learning from scratch** | Complete lectures first, then explore this guide |
| **Interview prep** | Use Quick Reference + Coding Challenges |
| **Production code** | Follow Legacy→Modern upgrades religiously |
| **Exam review** | Visual Diagrams + Cheatsheet |

---

## Modern C++ Philosophy

**The Golden Rules:**

1. **Rule of Zero** — Default to containers and smart pointers. The best destructor is the one you don't write.

2. **Concepts over SFINAE** — C++20 Concepts give readable errors. Use them.

3. **`std::span` for arrays** — No more `void func(int* arr, int size)`. Use `std::span<int>`.

4. **Avoid `new`/`delete`** — If you write these keywords, you're doing it wrong (unless interfacing with C APIs).

5. **`std::format` over `<<`** — Type-safe, faster, more readable.

---

## Prerequisites

- Basic C++ syntax (variables, functions, control flow)
- Understanding of pointers and references (from main lectures)
- C++20-capable compiler:
  - GCC 10+
  - Clang 11+
  - MSVC 19.29+

**Compiler flags:**
```bash
g++ -std=c++20 -Wall -Wextra your_code.cpp
```

For C++23 features (`std::print`):
```bash
g++ -std=c++23 -Wall -Wextra your_code.cpp
```

---

## Navigation

| Module | Content Type | Estimated Time |
|--------|--------------|----------------|
| [Upgrades](upgrades/legacy_to_modern.md) | Reading + Code | 2-3 hours |
| [Visuals](visuals/memory_diagrams.md) | Diagrams | 1 hour |
| [Exercises](exercises/coding_challenges.md) | Hands-on coding | 3-4 hours |
| [Cheatsheet](quick_reference/cheatsheet.md) | Reference | As needed |

**Total commitment:** ~6-8 hours for complete mastery

---

## Feedback

Found an error? Have a suggestion? Open an issue or contact the course instructor.

**Happy coding! 🚀**
