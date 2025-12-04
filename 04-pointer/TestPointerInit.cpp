/* Тестування оголошення та ініціалізації вказівників (TestPointerInit.cpp) */
#include <iostream>
using namespace std;

int main() {
  int number = 88;  // Оголошення змінної типу int з початковим значенням
  int* pNumber;     // Оголошення вказівника на int (int* - тип "вказівник на int")
                    // Вказівник зберігає адресу змінної в пам'яті
  pNumber =
      &number;  // Оператор & (адреса) повертає адресу змінної number
                // Присвоюємо адресу number вказівнику pNumber

  cout << pNumber << endl;   // Виведення вмісту pNumber (адреса, на яку він вказує)
  cout << &number << endl;   // Виведення адреси змінної number (той самий адрес)
  cout << *pNumber << endl;  // Оператор * (розіменування) - отримання значення за адресою
                              // Виведення значення, на яке вказує pNumber
  cout << number << endl;    // Виведення значення number (те саме значення)

  *pNumber = 99;             // Зміна значення через вказівник
                              // *pNumber - доступ до значення за адресою, яку зберігає pNumber
  cout << pNumber << endl;   // Адреса pNumber не змінилася
  cout << &number << endl;   // Адреса number не змінилася
  cout << *pNumber << endl;  // Значення змінилося на 99
  cout << number << endl;    // Значення number також змінилося на 99
                             // Значення number змінилося через вказівник

  cout << &pNumber
       << endl;  // Виведення адреси самої змінної-вказівника pNumber
                  // pNumber - це змінна, що має свою адресу в пам'яті
}
