/*
 * Запитуємо у користувача радіус кола та обчислюємо його площу та довжину кола
 * (CircleComputation.cpp)
 */
#include <iostream>  // Бібліотека для вводу/виводу
using namespace std; // Використання стандартного простору імен

int main() {
  double radius, circumference, area; // Оголошення трьох змінних типу double (дробові числа з подвійною точністю)
  const double PI = 3.14159265;       // Оголошення константи типу double (const - значення не можна змінити)

  cout << "Enter the radius: "; // Виведення запиту на введення радіусу
  cin >> radius;                // Читання введеного значення та збереження в змінну radius

  // Обчислення площі та довжини кола
  area = radius * radius * PI;        // Формула площі кола: π * r²
  circumference = 2.0 * radius * PI; // Формула довжини кола: 2 * π * r
                                       // 2.0 - дробове число, що забезпечує дробові обчислення

  // Виведення результатів
  cout << "The radius is: " << radius << endl;
  cout << "The area is: " << area << endl;
  cout << "The circumference is: " << circumference << endl;

  return 0;  // Успішне завершення програми
}
