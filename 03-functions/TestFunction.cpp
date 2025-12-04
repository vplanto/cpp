/* Тестування функцій (TestFunction.cpp) */
#include <iostream>  // Бібліотека для вводу/виводу
using namespace std;
const double PI = 3.14159265;  // Константа для числа π

// Прототип функції (оголошення функції)
// Прототип повідомляє компілятор про тип повернення та параметри функції
double getArea(double radius);

int main() {
  double radius1 = 1.1, area1, area2;  // Оголошення змінних
  // Виклик функції getArea() зі змінною як аргументом
  area1 = getArea(radius1);  // Результат функції зберігається в area1
  cout << "area 1 is " << area1 << endl;
  // Виклик функції getArea() з числовим літералом як аргументом
  area2 = getArea(2.2);  // 2.2 - дробовий літерал
  cout << "area 2 is " << area2 << endl;
  // Виклик функції getArea() безпосередньо в виразі виводу
  cout << "area 3 is " << getArea(3.3) << endl;  // Результат використовується одразу
}

// Визначення функції (реалізація функції)
// Повертає площу кола за заданим радіусом
// Формула площі кола: π * r²
double getArea(double radius) { return radius * radius * PI; }
