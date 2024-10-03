/* A mystery series (Mystery.cpp) */
#include <iostream>
using namespace std;

int main() {
  int number = 1;
  while (true) {
    ++number;
    if ((number % 3) == 0) continue;
    if (number == 133) break;
    if ((number % 2) == 0) {
      number += 3;
    } else {
      number -= 3;
    }
    cout << number << " ";
  }
  cout << endl;
  return 0;
}
