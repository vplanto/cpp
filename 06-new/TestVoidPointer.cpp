#include <iostream>
using namespace std;

int main() {
  int intVar = 42;
  double doubleVar = 3.14;
  char charVar = 'A';

  // Void pointer can hold address of any data type
  void* voidPtr;

  // Point to an integer
  voidPtr = &intVar;
  cout << "Address of intVar: " << voidPtr << endl;

  // Point to a double
  voidPtr = &doubleVar;
  cout << "Address of doubleVar: " << voidPtr << endl;

  // Point to a char
  voidPtr = &charVar;
  cout << "Address of charVar: " << voidPtr << endl;

  // We can use void pointer to compare addresses
  void* anotherPtr = &doubleVar;
  if (voidPtr == anotherPtr) {
    cout << "The void pointer and anotherPtr point to the same address."
         << endl;
  } else {
    cout << "The void pointer and anotherPtr point to different addresses."
         << endl;
  }

  // Note: We cannot dereference void pointer without casting
  // cout << *voidPtr; // This will result in a compilation error
  // int* intPtr = static_cast<int*>(voidPtr);

  return 0;
}
