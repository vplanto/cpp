/*
 * Конвертація температури між градусами Цельсія та Фаренгейта
 * (ConvertTemperature.cpp)
 */
#include <iostream>  // Бібліотека для вводу/виводу
using namespace std; // Використання стандартного простору імен

int main() {
   double celsius, fahrenheit;  // Оголошення змінних типу double для зберігання температури

   // Конвертація з Цельсія в Фаренгейта
   cout << "Enter the temperature in celsius: ";
   cin >> celsius;
   // Формула перетворення: F = C * 9/5 + 32
   // Використання 9.0 та 5.0 забезпечує дробові обчислення
   fahrenheit = celsius * 9.0 / 5.0 + 32.0;
   cout << celsius << " degree C is " << fahrenheit << " degree F." << endl << endl;

   // Конвертація з Фаренгейта в Цельсія
   cout << "Enter the temperature in fahrenheit: ";
   cin >> fahrenheit;
   // Формула перетворення: C = (F - 32) * 5/9
   celsius =  (fahrenheit - 32.0) * 5.0 / 9.0;
   cout << fahrenheit << " degree F is " << celsius << " degree C." << endl;

   return 0;  // Успішне завершення програми
}
