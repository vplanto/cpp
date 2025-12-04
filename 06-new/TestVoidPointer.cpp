#include <iostream>
using namespace std;

int main() {
  int intVar = 42;
  double doubleVar = 3.14;
  char charVar = 'A';

  // void* - універсальний вказівник, може зберігати адресу будь-якого типу даних
  void* voidPtr;

  // Вказівник на int
  voidPtr = &intVar;
  cout << "Address of intVar: " << voidPtr << endl;

  // Вказівник на double
  voidPtr = &doubleVar;
  cout << "Address of doubleVar: " << voidPtr << endl;

  // Вказівник на char
  voidPtr = &charVar;
  cout << "Address of charVar: " << voidPtr << endl;

  // void* можна використовувати для порівняння адрес
  void* anotherPtr = &doubleVar;
  if (voidPtr == anotherPtr) {
    cout << "The void pointer and anotherPtr point to the same address."
         << endl;
  } else {
    cout << "The void pointer and anotherPtr point to different addresses."
         << endl;
  }

  // УВАГА: void* не можна розіменувати без приведення типу
  // cout << *voidPtr; // Це призведе до помилки компіляції
  // Для доступу до значення потрібно явне приведення типу:
  // int* intPtr = static_cast<int*>(voidPtr);
  // cout << *intPtr;

  return 0;
}
