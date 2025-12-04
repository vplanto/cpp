/* Передача масиву в функцію через вказівник (TestArrayPassingPointer.cpp) */
#include <iostream>
using namespace std;

// Прототип функції
int max(const int *arr, int size);

int main() {
  const int SIZE = 5;
  int numbers[SIZE] = {10, 20, 90, 76, 22};
  // numbers - ім'я масиву, що неявно перетворюється на вказівник на перший елемент
  cout << max(numbers, SIZE) << endl;
}

// Повертає максимальне значення масиву
// Параметр - вказівник на const int (явна форма передачі масиву)
int max(const int *arr, int size) {
  int max = *arr;  // *arr - розіменування вказівника (перший елемент)
  for (int i = 1; i < size; ++i) {
    // *(arr + i) - арифметика вказівників: arr + i вказує на i-тий елемент
    // Еквівалентно arr[i], але використовується арифметика вказівників
    if (max < *(arr + i)) max = *(arr + i);
  }
  return max;
}
