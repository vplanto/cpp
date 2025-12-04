/* Тестування форматування вводу (TestFormattedInput.cpp) */
#include <iomanip>   // Бібліотека для маніпуляторів форматування (setw)
#include <iostream>  // Бібліотека для вводу/виводу
#include <string>    // Бібліотека для класу string
using namespace std;

int main() {
  string areaCode, phoneCode;  // Рядки для зберігання частин номера телефону
  string inStr;

  cout << "Enter your phone number in this format (xxx)xxx-xxxx : ";
  cin.ignore();  // Пропуск одного символу (у цьому випадку '(')
  // setw(3) - маніпулятор, що обмежує кількість символів для читання до 3
  cin >> setw(3) >> areaCode;  // Читання коду області (3 символи)
  cin.ignore();  // Пропуск ')'
  cin >> setw(3) >> phoneCode;  // Читання перших 3 цифр номера
  cin.ignore();  // Пропуск '-'
  cin >> setw(4) >> inStr;  // Читання останніх 4 цифр номера
  phoneCode += inStr;  // Оператор += додає inStr до phoneCode (конкатенація рядків)

  // Виведення номера телефону з форматуванням
  // substr(0, 3) - підрядок, що починається з позиції 0 довжиною 3 символи
  cout << "Phone number is (" << areaCode << ")" << phoneCode.substr(0, 3)
       << "-" << phoneCode.substr(3, 4) << endl;  // substr(3, 4) - з позиції 3, довжина 4
  return 0;
}
