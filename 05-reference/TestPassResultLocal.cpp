/* Тестування повернення локальної змінної (TestPassResultLocal.cpp) */
#include <iostream>
using namespace std;

int* squarePtr(int);
int& squareRef(int);

int main() {
  int number = 8;
  cout << number << endl;              // 8
  // ПРОБЛЕМА: повертається адреса локальної змінної, яка вже не існує
  cout << *squarePtr(number) << endl;  // Невизначена поведінка!
  cout << squareRef(number) << endl;   // Невизначена поведінка!
}

int* squarePtr(int number) {
  int localResult = number * number;  // Локальна змінна
  return &localResult;                // ПОВЕРТАННЯ АДРЕСИ ЛОКАЛЬНОЇ ЗМІННОЇ - ПОМИЛКА!
  // Попередження: повертається адреса локальної змінної 'localResult'
  // Після виходу з функції localResult знищується, адреса стає невалідною
}

int& squareRef(int number) {
  int localResult = number * number;  // Локальна змінна
  return localResult;                 // ПОВЕРТАННЯ ПОСИЛАННЯ НА ЛОКАЛЬНУ ЗМІННУ - ПОМИЛКА!
  // Попередження: повертається посилання на локальну змінну 'localResult'
  // Після виходу з функції localResult знищується, посилання стає невалідним
}
