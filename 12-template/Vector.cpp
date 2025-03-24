#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> v;
  // inserts elements
  for (int i = 0; i < 10; i++) {
    v.push_back(i * 10);
  }
  cout << "The size of vector is " << v.size();
  cout << "\nThe maximum capacity is " << v.capacity();
  return 0;
}
