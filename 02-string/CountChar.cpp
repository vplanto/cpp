/* Function to count the occurrence of a char in a string (CountChar.cpp) */
#include <cstring>
#include <iostream>
using namespace std;

int count(const char *str, const char c);  // No need to pass the array size

int main() {
  char msg1[] = "Hello, world";
  char *msg2 = "Hello, world";

  cout << count(msg1, 'l') << endl;
  cout << count(msg2, 'l') << endl;
  cout << count("Hello, world", 'l') << endl;
}

// Count the occurrence of c in str
// No need to pass the size of char[] as C-string is terminated with '\0'
int count(const char *str, const char c) {
  int count = 0;
  while (*str) {  // same as (*str != '\0')
    if (*str == c) ++count;
    ++str;
  }
  return count;
}
