# Memory Model & Execution Environment Glossary

> **Audience:** Applied Mathematics students  
> **Purpose:** Formal definitions of C++ systems concepts without relying on engineering tribal knowledge

This document defines the foundational execution model of C++ using mathematical notation familiar to students with formal training in discrete mathematics and algorithms.

---

## 1. Memory & Storage Duration

### Problem Context

C++ documentation uses colloquial terms like "stack" and "heap" which conflict with the **abstract data type** meanings (Stack = LIFO structure, Heap = priority queue). We need precise terminology.

### Formal Definitions

Let $M$ denote the memory address space available to a program:
$$M = \{m_0, m_1, m_2, \dots, m_{2^{64}-1}\}$$

Each $m_i$ represents one addressable byte.

#### Storage Duration Classes

C++ defines **four storage duration classes** (lifetime rules):

**1. Automatic Storage Duration**

- **Colloquial Name:** "Stack" (misleading — refers to LIFO allocation order, not the data structure)
- **Lifetime:** $[\text{scope entry}, \text{scope exit})$
- **Allocation Order:** LIFO (Last In, First Out)
- **Deallocation:** Deterministic, automatic at scope exit

**Formal Model:**
```
Let scope S have entry point t₁ and exit point t₂.
Object x with automatic storage has lifetime:
  L(x) = [t₁, t₂)

Allocation: push(stack_pointer, sizeof(x))
Deallocation: pop(stack_pointer, sizeof(x))  // Automatic at t₂
```

**Example:**
```cpp
void foo() {
    int x = 42;  // Automatic storage
                  // Created at scope entry
}                // Destroyed at scope exit (deterministic)
```

---

**2. Dynamic Storage Duration**

- **Colloquial Name:** "Heap" (misleading — NOT a heap data structure, just dynamic allocation pool)
- **Lifetime:** $[\text{new expression}, \text{delete expression})$
- **Allocation Order:** Non-deterministic, OS-managed
- **Deallocation:** Manual (programmer responsibility)

**Formal Model:**
```
Object x has dynamic storage duration if:
  allocation_time(x) = time of 'new' expression
  deallocation_time(x) = time of 'delete' expression (or ∞ if leaked)

Memory region: Managed by OS allocator (e.g., malloc/free in C)
```

**Example:**
```cpp
int* p = new int(42);  // Dynamic storage allocated at runtime
// ... arbitrary lifetime ...
delete p;               // Manual deallocation required
```

**Memory Leak:**
$$\text{Leak} = \{x \mid x \text{ allocated but } \nexists \text{ corresponding delete}\}$$

---

**3. Static Storage Duration**

- **Lifetime:** $[\text{program start}, \text{program exit})$
- **Example:** Global variables, `static` local variables

---

**4. Thread-Local Storage Duration**

- **Lifetime:** $[\text{thread creation}, \text{thread destruction})$
- **Example:** `thread_local` variables

---

### Why "Stack" vs "Heap" Matters

**Performance Characteristics:**

| Property | Automatic (Stack) | Dynamic (Heap) |
|----------|-------------------|----------------|
| **Allocation Cost** | $O(1)$ — pointer increment | $O(\log n)$ to $O(n)$ — search free list |
| **Deallocation Cost** | $O(1)$ — automatic | $O(\log n)$ — update free list |
| **Fragmentation** | None (contiguous LIFO) | Possible (scattered allocations) |
| **Lifetime Control** | Scope-bound (rigid) | Manual (flexible but error-prone) |

---

## 2. Compilation & Linking Model

### Problem Context

Engineering documentation assumes knowledge of "object files" and "linker errors" without defining the translation phases. We formalize the compilation pipeline.

### Translation Pipeline as Function Composition

```
Source.cpp → [Preprocessor] → Translation_Unit.i → 
[Compiler] → Object_File.o → [Linker] → Executable
```

**Formal Definitions:**

#### Translation Unit

$$TU = \text{maximal set of declarations visible to a single compiler invocation}$$

After preprocessing, one `.cpp` file becomes one translation unit.

**Example:**
```cpp
// foo.cpp
#include "header.h"  // Preprocessor replaces with header contents
int x = 42;

// Translation Unit = {contents of header.h, int x = 42}
```

---

#### Symbol

$$\text{Symbol} = (\text{name}, \text{type\_signature})$$

A symbol is a unique identifier for a function or variable.

**Example:**
```cpp
void foo(int x);        // Symbol: (foo, int→void)
void foo(double x);     // Symbol: (foo, double→void)  [different signature!]
```

---

#### Linker Error

**Definition:**  
$$\text{Linker Error} \iff \exists s \in \text{Symbols}_{\text{referenced}} : s \notin \bigcup_{i} \text{Symbols}_{\text{defined}}(TU_i)$$

Translation: A symbol is used but no translation unit provides its definition.

**Example:**
```cpp
// main.cpp
void external_func();  // Declaration (symbol referenced)
int main() {
    external_func();   // Use
}

// No other .cpp provides definition of external_func
// → Linker error: undefined reference to external_func
```

---

### Why Templates Must Be in Headers

**Problem:**  
Templates are **not instantiated** until they are used with a specific type.

**Model:**
```
Let F = template<typename T> class Vector
Instantiation: F(int) generates actual code for Vector<int>

Compiler operates per translation unit:
  TU₁ sees: F declaration only
  TU₂ needs: F(int) — but can't generate code without F definition!

Solution: F definition must be in header (visible to all TUs)
```

**Error Without Header:**
```
TU_main.cpp: Needs F(int) → sees only declaration → can't instantiate
Linker:      Searches all TU₁, TU₂, ... → finds no F(int) code → ERROR
```

---

## 3. Hardware Latency (Abstract Probabilistic Model)

### Problem Context

Terms like "cache miss" and "branch prediction" assume knowledge of CPU micro-architecture. We abstract this as latency functions.

### Access Latency Function

Define $L: \text{MemoryLocation} \to \mathbb{R}^+$ as the **expected time** to retrieve data.

**Hierarchy:**

| Location | Latency (cycles) | Human Scale Analogy |
|----------|------------------|---------------------|
| CPU Register | $L(r) = 0$ | Immediate (thought) |
| L1 Cache | $L(\ell_1) \approx 4$ | 3 seconds |
| L2 Cache | $L(\ell_2) \approx 12$ | 10 seconds |
| RAM | $L(\text{ram}) \approx 100$ | 5 minutes |
| SSD | $L(\text{ssd}) \approx 100{,}000$ | 3 days |

**Practical Impact:**

For a loop accessing array (contiguous memory):
```cpp
for (int i = 0; i < N; i++) {
    sum += arr[i];  // Likely in cache: L ≈ 4 cycles
}
```

For a linked list (scattered memory):
```cpp
for (Node* p = head; p != nullptr; p = p->next) {
    sum += p->data;  // Likely cache miss: L ≈ 100 cycles each!
}
```

**Expected time:**
- Array: $4N$ cycles
- Linked list: $100N$ cycles (25× slower despite same $O(n)$ complexity!)

---

### Branch Prediction

**Model as Probabilistic Classifier:**

Let $P(\text{correct\_prediction})$ = probability CPU guesses next instruction correctly.

- **Deterministic code:** $P \approx 0.95$ (95% accuracy)
- **Random branches:** $P \approx 0.5$ (coin flip)

**Virtual Functions & Prediction Failure:**

```cpp
for (Animal* a : animals) {
    a->speak();  // Runtime type unknown → random branch
}
```

Expected penalty per call:
$$\text{Cost} = P \cdot 0 + (1 - P) \cdot \text{misprediction\_penalty}$$

For $P = 0.5$, penalty $\approx$ 15 cycles:
$$\text{Cost} = 0.5 \cdot 0 + 0.5 \cdot 15 = 7.5 \text{ cycles overhead}$$

---

## 4. Concurrency Primitives

### Mutex (Binary Semaphore)

**State Space:**
$$S = \{\text{unlocked}, \text{locked}\}$$

**Operations:**

$$\text{lock}: S \to S$$
$$\text{lock}(s) = \begin{cases}
\text{locked} & \text{if } s = \text{unlocked} \\
\text{BLOCK} & \text{if } s = \text{locked} \, (\text{wait until unlocked})
\end{cases}$$

$$\text{unlock}: S \to S$$
$$\text{unlock}(s) = \begin{cases}
\text{unlocked} & \text{if } s = \text{locked} \\
\text{ERROR} & \text{if } s = \text{unlocked}
\end{cases}$$

---

### Deadlock

**Formal Definition:**

Let $T = \{T_1, T_2, \dots, T_n\}$ be threads and $M = \{M_1, M_2, \dots, M_m\}$ be mutexes.

**Deadlock occurs** if there exists a circular wait:
$$T_1 \xrightarrow{\text{waits for}} M_1 \xrightarrow{\text{held by}} T_2 \xrightarrow{\text{waits for}} M_2 \xrightarrow{\text{held by}} T_1$$

**Example:**
```cpp
Thread 1:               Thread 2:
lock(M1);               lock(M2);
lock(M2);  ← BLOCKS     lock(M1);  ← BLOCKS
```

Both threads wait forever: $\lim_{t \to \infty} \text{progress}(T_1) = \lim_{t \to \infty} \text{progress}(T_2) = 0$

---

## Reference Guide

**When confused by jargon, map to formal definitions:**

| Engineering Term | Formal Equivalent |
|------------------|-------------------|
| "Stack" | Automatic storage duration |
| "Heap" | Dynamic storage duration |
| "Linker error" | Symbol $s$ referenced but $s \notin$ defined symbols |
| "Cache miss" | $L(\text{access}) = L(\text{ram}) \gg L(\ell_1)$ |
| "Deadlock" | Circular wait condition |

All C++ "magic" is reducible to these mathematical models.
