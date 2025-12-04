/* Тестування sizeof для масивів (TestSizeofArray.cpp) */
#include <iostream>
using namespace std;

// Прототип функції
void fun(const int *arr, int size);

int main() {
  const int SIZE = 5;
  int a[SIZE] = {8, 4, 5, 3, 2};
  // sizeof(a) - розмір масиву в байтах (5 * sizeof(int))
  cout << "sizeof in main() is " << sizeof(a) << endl;
  cout << "address in main() is " << a << endl;
  fun(a, SIZE);
}

// Визначення функції
void fun(const int *arr, int size) {
  // sizeof(arr) - розмір вказівника (зазвичай 4 або 8 байт), НЕ розмір масиву!
  // У функції arr - це вказівник, а не масив, тому sizeof повертає розмір вказівника
  cout << "sizeof in function is " << sizeof(arr) << endl;
  cout << "address in function is " << arr << endl;
}
