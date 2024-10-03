/* Prompt user for positive integers and display the count, maximum,
   minimum and average. Terminate the input with -1 (StatNumbers.cpp) */
#include <climits>  // for INT_MAX
#include <iomanip>  // for setprecision(n)
#include <iostream>
using namespace std;

int main() {
  int numberIn;       // input number (positive integer)
  int count = 0;      // count of inputs, init to 0
  int sum = 0;        // sum of inputs, init to 0
  int max = 0;        // max of inputs, init to minimum
  int min = INT_MAX;  // min of inputs, init to maximum (need <climits>)
  int sentinel = -1;  // Input terminating value

  // Read Inputs until sentinel encountered
  cout << "Enter a positive integer or " << sentinel << " to exit: ";
  while (cin >> numberIn && numberIn != sentinel) {
    // Check input for positive integer
    if (numberIn > 0) {
      ++count;
      sum += numberIn;
      if (max < numberIn) max = numberIn;
      if (min > numberIn) min = numberIn;
    } else {
      cout << "error: input must be positive! try again..." << endl;
    }
    cout << "Enter a positive integer or " << sentinel << " to exit: ";
  }

  // Print result
  cout << endl;
  cout << "Count is " << count << endl;
  if (count > 0) {
    cout << "Maximum is " << max << endl;
    cout << "Minimum is " << min << endl;
    cout << fixed << setprecision(2);
    // print floating point to 2 decimal places (need <iomanip>)
    cout << "Average is " << (double)sum / count << endl;
  }
}
