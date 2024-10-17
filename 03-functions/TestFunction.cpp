/* Test Function (TestFunction.cpp) */
#include <iostream>
using namespace std;
const double PI = 3.14159265;

// Function Prototype (Function Declaration)
double getArea(double radius);

int main() {
  double radius1 = 1.1, area1, area2;
  // call function getArea()
  area1 = getArea(radius1);
  cout << "area 1 is " << area1 << endl;
  // call function getArea()
  area2 = getArea(2.2);
  cout << "area 2 is " << area2 << endl;
  // call function getArea()
  cout << "area 3 is " << getArea(3.3) << endl;
}

// Function Definition
// Return the area of a circle given its radius
double getArea(double radius) { return radius * radius * PI; }
