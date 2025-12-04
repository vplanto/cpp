/* Посилання vs. Вказівники (TestReferenceVsPointer.cpp) */
#include <iostream>
using namespace std;

int main() {
  int number1 = 88, number2 = 22;

  // Створення вказівника на number1
  int* pNumber1 = &number1;   // Явне отримання адреси (оператор &)
  *pNumber1 = 99;             // Явне розіменування (оператор *)
  cout << *pNumber1 << endl;  // 99
  cout << &number1 << endl;   // Адреса number1
  cout << pNumber1
       << endl;  // Вміст вказівника (адреса, на яку він вказує)
  cout << &pNumber1 << endl;  // Адреса самої змінної-вказівника pNumber1
  pNumber1 = &number2;  // Вказівник можна переназначити на іншу адресу
                        // Вказівник - це змінна, що може зберігати різні адреси

  // Створення посилання (псевдоніма) на number1
  int& refNumber1 = number1;    // Неявне посилання (НЕ &number1)
                                // Посилання має бути ініціалізоване при оголошенні
  refNumber1 = 11;              // Неявне розіменування (НЕ *refNumber1)
                                // Посилання використовується як звичайна змінна
  cout << refNumber1 << endl;   // 11
  cout << &number1 << endl;     // Адреса number1
  cout << &refNumber1 << endl;  // Та сама адреса (посилання не має своєї адреси)
  // refNumber1 = &number2;     // ПОМИЛКА! Посилання не можна переназначити
  //  error: invalid conversion from 'int*' to 'int'
  refNumber1 =
      number2;  // refNumber1 залишається псевдонімом number1
                // Присвоюємо значення number2 (22) refNumber1 (і number1)
  number2++;
  cout << refNumber1 << endl;  // 22 (refNumber1 все ще вказує на number1)
  cout << number1 << endl;     // 22
  cout << number2 << endl;     // 23
}
