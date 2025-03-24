/* Testing struct (TestStruct.cpp) */
#include <iostream>
using namespace std;

struct Point {
  int x;
  int y;
};

int main() {
  Point p1 = {3, 4};  // declare and init members
  cout << "(" << p1.x << "," << p1.y << ")" << endl;  // (3,4)

  Point p2 = {};  // declare and init numbers to defaults
  cout << "(" << p2.x << "," << p2.y << ")" << endl;  // (0,0)
  p2.x = 7;
  p2.y = 8;
  cout << "(" << p2.x << "," << p2.y << ")" << endl;  // (7,8)
  return 0;
}

// Notes:
// You can declare and initialize an instance of struct as shown in Line 11 and
// Line 14. To access members of a struct, use the dot (.) operator.
