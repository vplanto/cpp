/* Example on C++ string function (TestStringOp.cpp) */
#include <iostream>
#include <string>  // use string class
using namespace std;

int main() {
  string msg = "hello, world!";
  cout << msg << endl;
  cout << msg.length() << endl;              // length of string
  cout << msg.at(1) << endl;                 // char at index 1
  cout << msg[1] << endl;                    // same as above
  cout << msg.empty() << endl;               // test for empty string
  cout << msg.substr(3, 3) << endl;          // sub-string begins at
                                             // pos 3 of size 3
  cout << msg.replace(3, 3, "why") << endl;  // replace sub-string
  cout << msg.append("end") << endl;         // append behind
  cout << msg + "end" << endl;               // same as above
  cout << msg.insert(3, "insert") << endl;   // insert after pos 3

  string msg1;
  msg1 = msg;  // copy
  cout << msg1 << endl;

  cout << "Enter a line: ";
  getline(cin, msg);  // read a line of input
  cout << msg << endl;
}
