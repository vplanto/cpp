#include <iostream>
using namespace std;

// Демонстрація перевантаження функцій (function overloading)
// Перевантаження - кілька функцій з однаковим ім'ям, але різними параметрами

// Функція для додавання двох цілих чисел
int add(int a, int b) { return a + b; }

// Функція для додавання трьох цілих чисел (різна кількість параметрів)
int add(int a, int b, int c) { return a + b + c; }

// Функція для додавання двох дробових чисел (різні типи параметрів)
float add(float a, float b) { return a + b; }

int main() {
  // Виклик перевантажених функцій
  // Компілятор вибирає правильну функцію на основі типів та кількості аргументів
  cout << "Addition of two integers: " << add(5, 10) << endl;
  cout << "Addition of three integers: " << add(5, 10, 15) << endl;
  cout << "Addition of two floats: " << add(5.5f, 10.5f) << endl;  // f - суфікс для float

  return 0;
}
