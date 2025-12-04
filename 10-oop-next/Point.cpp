/* Файл реалізації класу Point (Point.cpp) */
#include "Point.h"

#include <iostream>
using namespace std;

// Конструктор - значення за замовчуванням вказані в оголошенні
// Список ініціалізації: x(x), y(y) - ініціалізація членів через параметри
Point::Point(int x, int y) : x(x), y(y) {}

// Геттери (методи доступу до приватних членів)
int Point::getX() const { return x; }
int Point::getY() const { return y; }

// Сеттери (методи зміни приватних членів)
void Point::setX(int x) { this->x = x; }  // this-> для розрізнення параметра та члена
void Point::setY(int y) { this->y = y; }

// Публічні функції
void Point::setXY(int x, int y) {
  this->x = x;
  this->y = y;
}

void Point::print() const { cout << "Point @ (" << x << "," << y << ")"; }
