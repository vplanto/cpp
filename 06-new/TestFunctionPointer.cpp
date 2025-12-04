/* Тестування вказівників на функції (TestFunctionPointer.cpp) */
#include <iostream>
using namespace std;

int arithmetic(int, int, int (*)(int, int));
// Приймає 3 аргументи: 2 int та вказівник на функцію
// int (*)(int, int) - тип вказівника на функцію, що приймає два int та повертає int
int add(int, int);
int sub(int, int);

int add(int n1, int n2) { return n1 + n2; }
int sub(int n1, int n2) { return n1 - n2; }

int arithmetic(int n1, int n2, int (*operation)(int, int)) {
  // (*operation) - виклик функції через вказівник
  // operation(n1, n2) також працює (альтернативний синтаксис)
  return (*operation)(n1, n2);
}

int main() {
  int number1 = 5, number2 = 6;

  // Передача функції add як аргументу (ім'я функції неявно перетворюється на вказівник)
  cout << arithmetic(number1, number2, add) << endl;
  // Передача функції sub як аргументу
  cout << arithmetic(number1, number2, sub) << endl;
}
