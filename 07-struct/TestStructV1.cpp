/*
 * Testing struct (TestStruct.cpp)
 */
#include <iostream>
using namespace std;
 
struct Point {
  int x, y;
};
 
struct Rectangle {
  Point topLeft;
  Point bottomRight;
};
 
int main() {
   Point p1, p2;
   p1.x = 0;  // p1 at (0, 3)
   p1.y = 3;
   p2.x = 4;  // p2 at (4, 0)
   p2.y = 0;
 
   cout << "p1 at (" << p1.x << "," << p1.y << ")" << endl;
   cout << "p2 at (" << p2.x << "," << p2.y << ")" << endl;
 
   Rectangle rect;
   rect.topLeft = p1;
   rect.bottomRight = p2;
 
   cout << "Rectangle top-left at (" << rect.topLeft.x
        << "," << rect.topLeft.y << ")" << endl;
   cout << "Rectangle bottom-right at (" << rect.bottomRight.x
        << "," << rect.bottomRight.y << ")" << endl;
 
   return 0;
}
