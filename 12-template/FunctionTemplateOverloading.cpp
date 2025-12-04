/* Тестування перевантаження шаблонів функцій (FunctionTemplateOverloading.cpp) */
#include <iostream>
using namespace std;

// Шаблон функції для обміну двома змінними
template <typename T>
void mySwap(T &a, T &b);
// Обмін двома змінними узагальненого фундаментального типу

// Перевантажений шаблон функції для обміну масивами
template <typename T>
void mySwap(T a[], T b[], int size);
// Обмін двома масивами узагальненого типу

// Шаблон функції для виведення масиву
template <typename T>
void print(const T *const array, int size);
// Виведення масиву узагальненого типу

int main() {
  int i1 = 1, i2 = 2;
  mySwap(i1, i2);  // Викликається перша версія mySwap(T &, T &)
  cout << "i1 is " << i1 << ", i2 is " << i2 << endl;

  const int SIZE = 3;
  int ar1[] = {1, 2, 3}, ar2[] = {4, 5, 6};
  mySwap(ar1, ar2, SIZE);  // Викликається друга версія mySwap(T [], T [], int)
  print(ar1, SIZE);
  print(ar2, SIZE);
}

template <typename T>
void mySwap(T &a, T &b) {
  T temp;
  temp = a;
  a = b;
  b = temp;
}

template <typename T>
void mySwap(T a[], T b[], int size) {
  T temp;
  for (int i = 0; i < size; ++i) {
    temp = a[i];
    a[i] = b[i];
    b[i] = temp;
  }
}

template <typename T>
void print(const T *const array, int size) {
  cout << "(";
  for (int i = 0; i < size; ++i) {
    cout << array[i];
    if (i < size - 1) cout << ",";
  }
  cout << ")" << endl;
}
