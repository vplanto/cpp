/* Testing For-each loop (TestForEach.cpp) */
#include <iostream>
using namespace std;

int main() {
  int numbers[] = {11, 22, 33, 44, 55};

  // For each member called number of array numbers - read only
  for (int number : numbers) {
    cout << number << " ";
  }
  cout << endl;
  cout << "next array is going to be modified" << endl;
  // To modify members, need to use reference (&)
  for (int &number : numbers) {
    number = 99;
  }

  for (int number : numbers) {
    cout << number << endl;
  }
  return 0;
}
