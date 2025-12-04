/* Передача параметрів за значенням (TestPassByValue.cpp) */
#include <iostream>
using namespace std;

int square(int);

int main() {
  int number = 8;
  cout << "In main(): " << &number << endl;  // Адреса number у main()
  cout << number << endl;                    // 8
  cout << square(number) << endl;            // 64 - результат функції
  cout << number << endl;                    // 8 - значення не змінилося
                                              // При передачі за значенням створюється копія
}

int square(int n) {                       // Параметр передається за значенням (копія)
  cout << "In square(): " << &n << endl;  // Адреса n відрізняється від адреси number
                                           // n - це копія, що має свою адресу в пам'яті
  n *= n;                                 // Зміна копії всередині функції
                                          // Оригінальна змінна number не змінюється
  return n;
}
