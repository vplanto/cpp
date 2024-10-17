/* Testing max function (TestMaxFunction.cpp) */
#include <iostream>
using namespace std;

int maximum(int, int);  // Function prototype (declaration)

int main() {
  cout << maximum(5, 8) << endl;  // Call maximum() with literals

  int a = 6, b = 9, c;
  c = maximum(a, b);  // Call maximum() with variables
  cout << c << endl;

  cout << maximum(c, 99) << endl;  // Call maximum()
}

// Function definition
// A function that returns the maximum of two given int
int maximum(int num1, int num2) { return (num1 > num2) ? num1 : num2; }
