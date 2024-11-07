#include <iostream>
#include <string>
using namespace std;

int main() {
  string str = "Hello, World!";

  // Using the 'at' method to access and modify characters
  cout << "Original string: " << str << endl;

  // Accessing the character at index 7
  char& ch = str.at(7);
  cout << "Character at index 7: " << ch << endl;

  // Modifying the character at index 7
  ch = 'w';

  // Printing the modified string
  cout << "Modified string: " << str << endl;

  return 0;
}
