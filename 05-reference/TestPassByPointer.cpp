/* Передача параметрів через вказівник (TestPassByPointer.cpp) */
#include <iostream>
using namespace std;

void square(int *);

int main() {
  int number = 8;
  cout << "In main(): " << &number << endl;  // Адреса number у main()
  cout << number << endl;                    // 8
  square(&number);         // Явне отримання адреси для передачі
                           // &number - адреса змінної number
  cout << number << endl;  // 64 - значення змінилося через вказівник
}

void square(int *pNumber) {  // Функція приймає вказівник на int (не const)
  cout << "In square(): " << pNumber << endl;  // Адреса, на яку вказує pNumber
                                                 // pNumber містить адресу number
  *pNumber *= *pNumber;  // Явне розіменування для отримання значення
                          // *pNumber - доступ до значення за адресою
}
