#include <iostream>
using namespace std;

// Function prototype
int factorial(int n, int depth = 0);

int main() {
  int number;

  // Ask user for a number
  cout << "Enter a positive integer: ";
  cin >> number;

  // Calculate and display the factorial using the recursive function
  cout << "Factorial of " << number << " = " << factorial(number) << endl;

  return 0;  // End of program
}

// Recursive function to calculate factorial
int factorial(int n, int depth) {
  // Print call stack information
  cout << string(depth, ' ') << "factorial(" << n << ") called" << endl;

  // Base case: factorial of 1 (or 0) is 1
  if (n <= 1) {
    cout << string(depth, ' ') << "Returning 1" << endl;
    return 1;
  } else {
    // Recursive case: n * factorial of (n-1)
    int result = n * factorial(n - 1, depth + 1);
    cout << string(depth, ' ') << "Returning " << result << endl;
    return result;
  }
}
