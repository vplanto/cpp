#include <iostream>
using namespace std;

struct Student {
  int id;
};

int main() {
  Student st1;
  st1.id = 1;
  cout << &st1 << endl;
  Student st2 = st1;
  cout << &st2 << endl;
  return 0;
}
