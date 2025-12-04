/* Тестування динамічного виділення масиву (TestDynamicArray.cpp) */
#include <cstdlib>   // Бібліотека для rand()
#include <iostream>
using namespace std;

int main() {
  const int SIZE = 5;
  int* pArray;

  pArray = new int[SIZE];  // new[] - динамічне виділення масиву
                           // Виділяє пам'ять для SIZE елементів типу int

  // Присвоєння випадкових чисел від 0 до 99
  // *(pArray + i) - арифметика вказівників: pArray + i вказує на i-тий елемент
  for (int i = 0; i < SIZE; ++i) {
    *(pArray + i) = rand() % 100;  // rand() % 100 - випадкове число від 0 до 99
  }
  // Виведення масиву
  for (int i = 0; i < SIZE; ++i) {
    cout << *(pArray + i) << " ";
  }
  cout << endl;

  delete[] pArray;  // delete[] - звільнення масиву, виділеного через new[]
                    // Використовується delete[], а не delete для масивів
  return 0;
}
