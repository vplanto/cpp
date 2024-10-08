/* Testing string class input and output (TestStringIO.cpp) */
#include <iostream>
#include <limits>
#include <string>    // Need this header to use string class
using namespace std; // Also needed for <string>

int main() {
  string message("Hello");
  cout << message << endl;

  // Input a word (delimited by space) into a string
  cout << "Enter a message (no space): ";
  cin >> message;
  cout << message << endl;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  // flush cin up to newline (need <limits> header)

  // Input a line into a string
  cout << "Enter a message (with spaces): ";
  getline(cin, message); // Read input from cin into message
  cout << message << endl;
  return 0;
}
