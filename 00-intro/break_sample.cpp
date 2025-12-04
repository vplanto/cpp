/*
 *  Виведення списку непростих чисел від 1 до верхньої межі (NonPrimeList.cpp).
 */
#include <cmath>     // Бібліотека для математичних функцій (sqrt - квадратний корінь)
#include <iostream>  // Бібліотека для вводу/виводу
using namespace std;

int main() {
  int upperbound;  // Оголошення змінної для верхньої межі
  cout << "Enter the upperbound: ";
  cin >> upperbound;
  // Цикл for: складається з ініціалізації (int number = 2), умови (number <= upperbound), 
  // та інкременту (++number). Виконується для кожного number від 2 до upperbound
  for (int number = 2; number <= upperbound; ++number) {
    // Число не є простим, якщо знайдено дільник між 2 та sqrt(number)
    // Достатньо перевіряти до sqrt(number), бо якщо є дільник більший за sqrt, 
    // то є і менший дільник
    int maxFactor = (int)sqrt(number);  // (int) - явне приведення типу до int
    // Вкладений цикл for для перевірки всіх можливих дільників
    for (int factor = 2; factor <= maxFactor; ++factor) {
      if (number % factor == 0) {  // Оператор % (модуло) повертає залишок від ділення
                                    // Якщо залишок 0, то factor є дільником number
        cout << number << " ";
        break;  // Оператор break негайно виходить з поточного циклу (внутрішнього for)
                // Знайдено дільник, немає потреби шукати інші
      }
    }
  }
  cout << endl;  // Перехід на новий рядок після виведення всіх чисел
  return 0;       // Успішне завершення програми
}
