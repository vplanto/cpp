/* Test Formatting Output (TestFormattedOutput.cpp) */
#include <iomanip>  // Needed to do formatted I/O
#include <iostream>
using namespace std;

int main() {
  // Floating point numbers
  double pi = 3.14159265;
  cout << fixed << setprecision(4);  // fixed format with 4 decimal places
  cout << pi << endl;
  cout << "|" << setw(8) << pi << "|" << setw(10) << pi << "|" << endl;
  // setw() is not sticky, only apply to the next operation.
  cout << setfill('-');
  cout << "|" << setw(8) << pi << "|" << setw(10) << pi << "|" << endl;
  cout << scientific;  // in scientific format with exponent
  cout << pi << endl;

  // booleans
  bool done = false;
  cout << done << endl;  // print 0 (for false) or 1 (for true)
  cout << boolalpha;     // print true or false
  cout << done << endl;
  return 0;
}
