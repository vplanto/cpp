/* Повернення значення через посилання та вказівник (TestPassByReferenceReturn.cpp) */
#include <iostream>
using namespace std;

int &squareRef(int &);
int *squarePtr(int *);

int main() {
  int number1 = 8;
  cout << "In main() &number1: " << &number1 << endl;  // Адреса number1
  // Функція повертає посилання на number1
  int &result = squareRef(number1);  // result - посилання на number1
  cout << "In main() &result: " << &result << endl;  // Та сама адреса, що й number1
  cout << result << endl;                            // 64
  cout << number1 << endl;                           // 64 - значення змінилося

  int number2 = 9;
  cout << "In main() &number2: " << &number2 << endl;  // Адреса number2
  // Функція повертає вказівник на number2
  int *pResult = squarePtr(&number2);  // pResult - вказівник на number2
  cout << "In main() pResult: " << pResult << endl;  // Адреса number2
  cout << *pResult << endl;                          // 81
  cout << number2 << endl;                           // 81 - значення змінилося
}

int &squareRef(int &rNumber) {
  cout << "In squareRef(): " << &rNumber << endl;  // Адреса параметра
  rNumber *= rNumber;  // Зміна значення через посилання
  return rNumber;      // Повернення посилання на ту саму змінну
}

int *squarePtr(int *pNumber) {
  cout << "In squarePtr(): " << pNumber << endl;  // Адреса, на яку вказує вказівник
  *pNumber *= *pNumber;  // Зміна значення через вказівник
  return pNumber;        // Повернення вказівника на ту саму змінну
}
