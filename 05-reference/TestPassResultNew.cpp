/* Тестування повернення динамічно виділеної пам'яті (TestPassResultNew.cpp) */
#include <iostream>
using namespace std;

int* squarePtr(int);
int& squareRef(int);

int main() {
  int number = 8;
  cout << number << endl;              // 8
  // Динамічно виділена пам'ять існує до явного видалення
  cout << *squarePtr(number) << endl;  // 64 - працює коректно
  cout << squareRef(number) << endl;   // 64 - працює коректно
  // УВАГА: пам'ять, виділена через new, має бути звільнена через delete!
}

int* squarePtr(int number) {
  // new int(...) - динамічне виділення пам'яті в купі (heap)
  // Пам'ять залишається валідною після виходу з функції
  int* dynamicAllocatedResult = new int(number * number);
  return dynamicAllocatedResult;  // Повертаємо вказівник на динамічно виділену пам'ять
}

int& squareRef(int number) {
  // Динамічне виділення пам'яті
  int* dynamicAllocatedResult = new int(number * number);
  // *dynamicAllocatedResult - розіменування вказівника
  // Повертаємо посилання на динамічно виділену пам'ять
  return *dynamicAllocatedResult;
}
