#include <iostream>
using namespace std;
unsigned long pwr(unsigned long n, unsigned long m) {
  if (m == 0) n = 1;
  if (m == 1) n = n;
  n = pwr(n, m / 2) * pwr(n, m / 2);
  return n;
}

int main() {
  unsigned long n(2), m(16);
  cout << pwr(n, m);
  return 0;
}
