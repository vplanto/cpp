/* Test vector template class (TestVectorTemplate.cpp) */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  vector<int> v1(5);  // Create a vector with 5 elements;

  // Assign values into v1, using array-like index []
  // You can retrieve the size of vector via size()
  for (int i = 0; i < v1.size(); ++i) {
    v1[i] = (i + 1) * 2;  // no index-bound check for []
  }

  // Print vector content, using at()
  for (int i = 0; i < v1.size(); ++i) {
    cout << v1.at(i) << " ";  // do index-bound check with at()
  }
  cout << endl;

  vector<int> v2;  // Create a vector with 0 elements
  // Assign v1 to v2 memberwise
  v2 = v1;
  for (int i = 0; i < v2.size(); ++i) {
    cout << v2[i] << " ";
  }
  cout << endl;

  // Compare 2 vectors memberwise
  cout << boolalpha << (v1 == v2) << endl;

  // Append more elements - dynamically allocate memory
  v1.push_back(80);
  v1.push_back(81);
  for (int i = 0; i < v1.size(); ++i) {
    cout << v1[i] << " ";
  }
  cout << endl;

  // Remove element from the end
  v1.pop_back();
  for (int i = 0; i < v1.size(); ++i) {
    cout << v1[i] << " ";
  }
  cout << endl;

  vector<string> v3;            // Create a vector of string with 0 element
  v3.push_back("A for Apple");  // append new elements
  v3.push_back("B for Boy");
  for (int i = 0; i < v3.size(); ++i) {
    cout << v3[i] << " ";
  }
  cout << endl;
}
