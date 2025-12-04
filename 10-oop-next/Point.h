/* Заголовочний файл класу Point (Point.h) */
#ifndef POINT_H  // Захист від множинного включення (include guard)
#define POINT_H

class Point {
 private:
  int x, y;  // Приватні члени даних (інкапсуляція)

 public:
  Point(int x = 0, int y = 0);  // Конструктор з параметрами за замовчуванням
  int getX() const;             // Геттер (const метод - не змінює стан)
  void setX(int x);             // Сеттер
  int getY() const;
  void setY(int y);
  void setXY(int x, int y);
  void print() const;  // Виведення стану об'єкта
};

#endif
