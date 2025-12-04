/*
 * Тестування вкладених структур (TestStruct.cpp)
 */
#include <iostream>
using namespace std;
 
// Структура Point з двома полями
struct Point {
  int x, y;  // Можна оголошувати кілька полів одного типу в одному рядку
};
 
// Структура може містити інші структури як поля (вкладені структури)
struct Rectangle {
  Point topLeft;      // Поле типу Point
  Point bottomRight;  // Поле типу Point
};
 
int main() {
   Point p1, p2;  // Оголошення двох змінних типу Point
   p1.x = 0;  // Присвоєння значення полю x структури p1
   p1.y = 3;
   p2.x = 4;  // Присвоєння значення полю x структури p2
   p2.y = 0;
 
   cout << "p1 at (" << p1.x << "," << p1.y << ")" << endl;
   cout << "p2 at (" << p2.x << "," << p2.y << ")" << endl;
 
   Rectangle rect;
   // Присвоєння структури Point полю структури Rectangle (копіювання)
   rect.topLeft = p1;
   rect.bottomRight = p2;
 
   // Доступ до вкладених полів: rect.topLeft.x - поле x структури topLeft
   cout << "Rectangle top-left at (" << rect.topLeft.x
        << "," << rect.topLeft.y << ")" << endl;
   cout << "Rectangle bottom-right at (" << rect.bottomRight.x
        << "," << rect.bottomRight.y << ")" << endl;
 
   return 0;
}
