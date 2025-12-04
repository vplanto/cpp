/* Заголовочний файл для рухомих точок (MovablePoint.h) */
#ifndef MOVING_POINT_H
#define MOVING_POINT_H

#include "Point.h"  // Включення заголовочного файлу базового класу

// MovablePoint - похідний клас від Point (public наслідування)
class MovablePoint : public Point {
 private:
  int xSpeed, ySpeed;  // Швидкості руху по осях

 public:
  MovablePoint(int x, int y, int xSpeed = 0, int ySpeed = 0);
  int getXSpeed() const;
  int getYSpeed() const;
  void setXSpeed(int xSpeed);
  void setYSpeed(int ySpeed);
  void move();  // Зміна позиції відповідно до швидкостей
  virtual void print() const;  // Віртуальна функція для поліморфізму
};

#endif
