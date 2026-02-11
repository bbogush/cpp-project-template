# C++ Code Style Guide

This document defines the coding style for this C++ project. The goal is **readability, consistency, and safety**.

---

## 1. General Principles

- Prefer **clarity over cleverness**
- Be consistent with existing code
- Optimize only when needed and measured
- Follow modern C++ (C++17/C++20) best practices

---

## 2. File Structure

### File naming

- Headers: `snake_case.hpp`
- Sources: `snake_case.cpp`
- One primary class per file (when reasonable)

Example:
```
order_book.hpp
order_book.cpp
```

### Include order

```cpp
#include <system_headers>

#include <third_party_headers>

#include "project_headers"
```

---

## 3. Naming Conventions

### Types

- Classes / Structs / Enums: **PascalCase**

```cpp
class OrderBook;
struct TradeEvent;
enum class OrderSide;
```

### Functions

- Functions & methods: **snake_case**

```cpp
void update_order_book();
bool is_valid() const;
```

### Variables

- Local variables: **snake_case**
- Member variables: **snake_case_** (trailing underscore)

```cpp
int order_count;
std::string symbol_;
```

### Constants

- `constexpr` or `const`
- Upper snake case

```cpp
constexpr int MAX_RETRIES = 5;
```

---

## 4. Formatting

### Indentation

- 4 spaces
- No tabs

### Braces

- K&R style

```cpp
if (condition) {
    do_something();
}
```

### Line length

- Max **100 characters** per line

---

## 5. Modern C++ Rules

- Prefer `constexpr`, `noexcept`, `[[nodiscard]]`
- Prefer `enum class` over `enum`
- Prefer `std::array` / `std::vector` over raw arrays
- Avoid raw `new` / `delete`

```cpp
[[nodiscard]] int compute() noexcept;
```

---

## 6. References, Pointers, Ownership

- Use references when ownership is not transferred
- Use smart pointers for ownership

```cpp
void process(const Order& order);
std::unique_ptr<Session> session;
```

---

## 7. Error Handling

- Prefer return values or `std::expected` (if available)
- Use exceptions only for truly exceptional cases
- Never throw from destructors

---

## 8. Const Correctness

- Mark everything `const` where possible

```cpp
const std::string& symbol() const;
```

---

## 9. Header Rules

- Headers must be **self-contained**
- Use `#pragma once`
- Do not include unused headers

```cpp
#pragma once
```

---

## 10. Comments

- Explain **why**, not **what**
- Keep comments up to date

```cpp
// Price is adjusted to avoid crossing the spread
```

---

## 11. Logging & Debugging

- No `std::cout` in production code
- Use project logging facilities
- Debug-only code must be guarded

```cpp
#ifdef DEBUG
log_debug("state=", state);
#endif
```

---

## 12. Tooling

Recommended tools:

- `clang-format`
- `clang-tidy`
- `cppcheck`

Formatting must pass:
```
clang-format --style=file
```

---

## 13. References

- C++ Core Guidelines
- Google C++ Style Guide (as reference, not strict)
- LLVM Coding Standards

---

**Any deviation from this style must be justified and documented.**

