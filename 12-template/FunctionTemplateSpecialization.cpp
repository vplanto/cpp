#include <iostream>

// Узагальнена функція (шаблон)
template <typename T>
void func(T arg) {
  std::cout << "In generic function with argument " << arg << '\n';
}

// Нешаблонна функція (має пріоритет над шаблоном для int)
void func(int arg) {
  std::cout << "In non-template function with argument " << arg << '\n';
}

// Явна спеціалізація узагальненої функції для типу int
// template <> - синтаксис явної спеціалізації
template <>
void func<int>(int arg) {
  std::cout << "In explicit specialization function with argument " << arg
            << '\n';
}

int main() {
  func(10);    // Викликається нешаблонна функція (найвищий пріоритет)
  func<>(10);  // Викликається явна спеціалізація шаблону (<> - явне вказання шаблону)
  func('a');   // Викликається узагальнена функція (char не має спеціалізації)
  return 0;
}

// УВАГА: Якщо нешаблонна функція відповідає виклику,
// вона має пріоритет над явною спеціалізацією, а потім над шаблонною функцією.
