/*
 * Запитуємо у користувача два цілі числа та виводимо їх суму, різницю, добуток та частку
 * (IntegerArithmetic.cpp)
 */
#include <iostream>  // Підключення бібліотеки для вводу/виводу
using namespace std; // Використання стандартного простору імен

int main() {
  int firstInt;   // Оголошення змінної типу int (ціле число) з ім'ям firstInt
  int secondInt;  // Оголошення змінної типу int з ім'ям secondInt
  int sum, difference, product, quotient;
  // Оголошення чотирьох змінних типу int для зберігання результатів обчислень

  cout << "Enter first integer: ";  // Виведення запиту на введення першого числа
  cin >> firstInt;  // Читання введеного значення з клавіатури (cin) та збереження в firstInt
  cout << "Enter second integer: ";  // Виведення запиту на введення другого числа
  cin >> secondInt;                  // Читання другого числа та збереження в secondInt

  // Виконання арифметичних операцій
  sum = firstInt + secondInt;        // Оператор + додає два числа
  difference = firstInt - secondInt;  // Оператор - віднімає друге число від першого
  product = firstInt * secondInt;     // Оператор * множить два числа
  quotient = firstInt / secondInt;    // Оператор / ділить перше число на друге (цілочисельне ділення для int)

  // Виведення результатів
  cout << "The sum is: " << sum << endl;
  cout << "The difference is: " << difference << endl;
  cout << "The product is: " << product << endl;
  cout << "The quotient is: " << quotient << endl;

  return 0;  // Успішне завершення програми
}
