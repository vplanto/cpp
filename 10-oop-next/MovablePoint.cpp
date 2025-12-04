/* Файл реалізації для рухомих точок (MovablePoint.cpp) */
#include "MovablePoint.h"  // Включення заголовочного файлу з оголошенням класу

#include <iostream>
using namespace std;

// Конструктор похідного класу: викликає конструктор базового класу через список ініціалізації
MovablePoint::MovablePoint(int x, int y, int xSpeed, int ySpeed)
    : Point(x, y), xSpeed(xSpeed), ySpeed(ySpeed) {}  // Point(x, y) - виклик конструктора базового класу

// Геттери
int MovablePoint::getXSpeed() const { return xSpeed; }
int MovablePoint::getYSpeed() const { return ySpeed; }

// Сеттери
void MovablePoint::setXSpeed(int xs) { xSpeed = xs; }
void MovablePoint::setYSpeed(int ys) { ySpeed = ys; }

// Функції
void MovablePoint::print() const {
  cout << "Movable";
  // Виклик функції базового класу через оператор розв'язання області видимості ::
  Point::print();
  cout << " Speed="
       << "(" << xSpeed << "," << ySpeed << ")";
}

void MovablePoint::move() {
  // Похідний клас не може безпосередньо отримати доступ до приватних членів базового класу
  // Потрібно використовувати публічний інтерфейс (геттери та сеттери)
  Point::setX(Point::getX() + xSpeed);
  Point::setY(Point::getY() + ySpeed);
}
