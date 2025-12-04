/*
 * Обчислення суми парних та непарних чисел від 1 до верхньої межі (SumOddEven.cpp)
 */
#include <iostream>  // Бібліотека для вводу/виводу
using namespace std; // Використання стандартного простору імен

int main() {
  int sumOdd = 0;   // Змінна для накопичення суми непарних чисел, ініціалізована як 0
  int sumEven = 0;  // Змінна для накопичення суми парних чисел, ініціалізована як 0
  int upperbound;   // Верхня межа - сумуємо числа від 1 до цього значення

  // Запитуємо у користувача верхню межу
  cout << "Enter the upperbound: ";
  cin >> upperbound;

  // Використовуємо цикл while для послідовного перевірення чисел 1, 2, 3, ..., до upperbound
  int number = 1;  // Починаємо з числа 1
  while (number <= upperbound) {  // Цикл виконується, поки number не перевищить upperbound
    if (number % 2 == 0) {  // Перевірка на парність: якщо залишок від ділення на 2 дорівнює 0
      sumEven = sumEven + number;  // Додаємо парне число до суми парних
    } else {  // Блок else виконується, якщо число непарне
      sumOdd = sumOdd + number;    // Додаємо непарне число до суми непарних
    }
    ++number;  // Інкремент: збільшуємо number на 1 для переходу до наступного числа
  }

  // Виведення результатів
  cout << "The sum of odd numbers is " << sumOdd << endl;
  cout << "The sum of even numbers is " << sumEven << endl;
  cout << "The difference is " << (sumOdd - sumEven) << endl;  // Різниця між сумами

  return 0;  // Успішне завершення програми
}
