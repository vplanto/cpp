/*
 * Обчислення суми чисел від 1 до верхньої межі за допомогою циклу while (SumNumbers.cpp).
 */
#include <iostream>  // Підключення бібліотеки для вводу/виводу
using namespace std; // Використання стандартного простору імен

int main() {
  int sum = 0;    // Оголошення змінної типу int для накопичення суми
                  // Ініціалізація початкового значення суми як 0
  int upperbound; // Верхня межа - сумуємо числа від 1 до цього значення

  // Запитуємо у користувача верхню межу
  cout << "Enter the upperbound: ";
  cin >> upperbound;

  // Використовуємо цикл while для послідовного додавання чисел 1, 2, 3, ..., до upperbound
  int number = 1;  // Починаємо з числа 1
  while (number <= upperbound) {  // Цикл виконується, поки number не перевищить upperbound
    sum = sum + number; // Додаємо поточне число до накопиченої суми
    ++number;           // Інкремент: збільшуємо number на 1 (++number еквівалентно number = number + 1)
  }
  // Виведення результату
  cout << "The sum from 1 to " << upperbound << " is " << sum << endl;

  return 0;  // Успішне завершення програми
}
