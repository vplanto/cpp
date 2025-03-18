#include <iostream>
using namespace std;

int main() {
  int x = 10;     // 'x' is an lvalue (has an address in memory)
  int y = x + 5;  // 'x + 5' is an rvalue (temporary result of the expression)

  cout << "x (lvalue): " << x << endl;
  cout << "x + 5 (rvalue): " << y << endl;

  // Using an rvalue directly
  int z = 20;  // '20' is an rvalue
  cout << "z (lvalue initialized by rvalue): " << z << endl;

  return 0;
}
