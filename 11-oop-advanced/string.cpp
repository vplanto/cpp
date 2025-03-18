/* Test overloaded operators in the C++ string class
   (TestStringOverloadOperators.cpp) */
#include <iostream>
#include <string>  // needed to use the string class
using namespace std;

int main() {
  string msg1("hello");
  string msg2("HELLO");
  string msg3("hello");

  // Relational Operators (comparing the contents)
  cout << boolalpha;
  cout << (msg1 == msg2) << endl;  // false
  cout << (msg1 == msg3) << endl;  // true
  cout << (msg1 < msg2) << endl;   // false (uppercases before lowercases)

  // Assignment
  string msg4 = msg1;
  cout << msg4 << endl;  // hello

  // Concatenation
  cout << (msg1 + " " + msg2) << endl;  // hello HELLO
  msg3 += msg2;
  cout << msg3 << endl;  // helloHELLO

  // Indexing
  cout << msg1[1] << endl;   // 'e'
  cout << msg1[99] << endl;  // garbage (no index-bound check)
  // cout << msg1.at(99) << endl; // out_of_range exception
}
