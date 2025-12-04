/* Файл реалізації класу Circle (Circle.cpp) */
#include "Circle.h"  // Користувацький заголовочний файл в тому ж каталозі

// Конструктор
// Значення за замовчуванням вказуються тільки в оголошенні,
// не можна повторювати в визначенні
Circle::Circle(double r, string c) {
  radius = r;
  color = c;
}

// Публічний геттер для приватного члена radius
double Circle::getRadius() const { return radius; }

// Публічний сеттер для приватного члена radius
void Circle::setRadius(double r) { radius = r; }

// Публічний геттер для приватного члена color
string Circle::getColor() const { return color; }

// Публічний сеттер для приватного члена color
void Circle::setColor(string c) { color = c; }

// Публічна функція-член (обчислення площі кола)
double Circle::getArea() const { return radius * radius * 3.14159265; }

int main() { return 0; }
