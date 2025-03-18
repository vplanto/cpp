#include <iostream>
using namespace std;

// Function to add two integers
int add(int a, int b) { return a + b; }

// Function to add three integers
int add(int a, int b, int c) { return a + b + c; }

// Function to add two floating-point numbers
float add(float a, float b) { return a + b; }

int main() {
  // Calling the overloaded functions
  cout << "Addition of two integers: " << add(5, 10) << endl;
  cout << "Addition of three integers: " << add(5, 10, 15) << endl;
  cout << "Addition of two floats: " << add(5.5f, 10.5f) << endl;

  return 0;
}
