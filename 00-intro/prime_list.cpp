/*
 *  Виведення списку простих чисел від 1 до верхньої межі (PrimeList.cpp).
 *  Просте число - це число, яке ділиться тільки на 1 та на саме себе.
 */
#include <cmath>     // Бібліотека для математичних функцій (sqrt - квадратний корінь)
#include <iostream>  // Бібліотека для вводу/виводу
using namespace std;

int main() {
  int upperbound;  // Оголошення змінної для верхньої межі діапазону
  cout << "Enter the upperbound: ";
  cin >> upperbound;

  // Перевіряємо кожне число від 2 до upperbound на простоту
  for (int number = 2; number <= upperbound; ++number) {
    // Число не є простим, якщо знайдено дільник між 2 та sqrt(number)
    // Достатньо перевіряти до sqrt(number) для оптимізації
    int maxFactor = (int)sqrt(number);  // (int) - явне приведення типу до int
    bool isPrime = true;  // Булева змінна (true/false) для позначення, чи є число простим
    int factor = 2;       // Починаємо перевірку з дільника 2
    // Цикл while виконується, поки isPrime істинне та factor не перевищить maxFactor
    while (isPrime && factor <= maxFactor) {
      if (number % factor == 0) {  // Оператор % повертає залишок від ділення
                                    // Якщо залишок 0, то factor є дільником number
        isPrime = false;            // Знайдено дільник, число не є простим
      }
      ++factor;  // Переходимо до наступного можливого дільника
    }
    if (isPrime) cout << number << " ";  // Якщо число просте, виводимо його
  }
  cout << endl;  // Перехід на новий рядок після виведення всіх простих чисел
  return 0;       // Успішне завершення програми
}
