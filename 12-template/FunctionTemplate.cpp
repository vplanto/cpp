/* Тестування шаблону функції (FunctionTemplate.cpp) */
#include <iostream>
using namespace std;

// Шаблон функції: template <typename T> - T є параметром типу
template <typename T>
void mySwap(T &a, T &b);
// Обмін значеннями двох змінних узагальненого типу, переданих за посиланням
// У <algorithm> є стандартна версія swap()

int main() {
  int i1 = 1, i2 = 2;
  // Компілятор генерує mySwap(int &, int &) під час інстанціації шаблону
  mySwap(i1, i2);
  cout << "i1 is " << i1 << ", i2 is " << i2 << endl;

  char c1 = 'a', c2 = 'b';
  // Компілятор генерує mySwap(char &, char &)
  mySwap(c1, c2);
  cout << "c1 is " << c1 << ", c2 is " << c2 << endl;

  double d1 = 1.1, d2 = 2.2;
  // Компілятор генерує mySwap(double &, double &)
  mySwap(d1, d2);
  cout << "d1 is " << d1 << ", d2 is " << d2 << endl;

  // mySwap(i1, d1);
  // Помилка: немає відповідної функції для mySwap(int&, double&)
  // Обидва параметри мають бути одного типу T
}

// Визначення шаблону функції
template <typename T>
void mySwap(T &a, T &b) {
  T temp;  // temp має тип T (визначається під час інстанціації)
  temp = a;
  a = b;
  b = temp;
}
