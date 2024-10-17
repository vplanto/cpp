#include <iostream>
using namespace std;

// Function prototype
int factorial(int n);

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
int factorial(int n) {
  // Base case: factorial of 1 (or 0) is 1
  if (n <= 1) {
    return 1;
  } else {
    // Recursive case: n * factorial of (n-1)
    return n * factorial(n - 1);
  }
}
