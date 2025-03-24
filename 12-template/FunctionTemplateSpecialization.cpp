#include <iostream>

// A generic function
template <typename T>
void func(T arg) {
  std::cout << "In generic function with argument " << arg << '\n';
}

// A non-template function
void func(int arg) {
  std::cout << "In non-template function with argument " << arg << '\n';
}

// An explicit specialization of the generic function for int
template <>
void func<int>(int arg) {
  std::cout << "In explicit specialization function with argument " << arg
            << '\n';
}

int main() {
  func(10);    // This will call the non-template function
  func<>(10);  // This will call the explicit specialization of the template
  func('a');   // This will call the generic function
  return 0;
}

// Be aware that if a non-template function definition corresponds to a function
// call, it will be prioritized over the explicit specialization and then the
// template function.
