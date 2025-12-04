/* Заголовочний файл класу Circle (Circle.h) */
#include <string>
using namespace std;

// Оголошення класу Circle
class Circle {
 private:  // Доступний тільки членам цього класу
  // Приватні члени даних (інкапсуляція)
  double radius;
  string color;

 public:  // Доступний всім
  // Оголошення прототипів функцій-членів
  // Конструктор з параметрами за замовчуванням
  Circle(double radius = 1.0, string color = "red");

  // Публічні геттери та сеттери для приватних членів
  double getRadius() const;
  void setRadius(double radius);
  string getColor() const;
  void setColor(string color);

  // Публічна функція-член
  double getArea() const;
};
