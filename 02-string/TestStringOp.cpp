/* Приклади використання функцій C++ string (TestStringOp.cpp) */
#include <iostream>  // Бібліотека для вводу/виводу
#include <string>    // Бібліотека для класу string
using namespace std;

int main() {
  string msg = "hello, world!";
  cout << msg << endl;
  cout << msg.length() << endl;              // length() - довжина рядка (кількість символів)
  cout << msg.at(1) << endl;                 // at(1) - символ за індексом 1 (з перевіркою меж)
  cout << msg[1] << endl;                    // [1] - те саме, що at(1), але без перевірки меж
  cout << msg.empty() << endl;               // empty() - перевірка, чи рядок порожній (true/false)
  // substr(3, 3) - підрядок, що починається з позиції 3 довжиною 3 символи
  cout << msg.substr(3, 3) << endl;          // Підрядок з позиції 3 розміром 3
  // replace(3, 3, "why") - заміна підрядка з позиції 3 довжиною 3 на "why"
  cout << msg.replace(3, 3, "why") << endl;  // Заміна підрядка
  // append("end") - додавання рядка в кінець
  cout << msg.append("end") << endl;         // Додавання "end" в кінець
  // Оператор + виконує конкатенацію (об'єднання) рядків
  cout << msg + "end" << endl;               // Те саме, що append("end")
  // insert(3, "insert") - вставка рядка "insert" після позиції 3
  cout << msg.insert(3, "insert") << endl;   // Вставка після позиції 3

  string msg1;
  msg1 = msg;  // Оператор = виконує копіювання рядка
  cout << msg1 << endl;

  cout << "Enter a line: ";
  getline(cin, msg);  // Читання цілого рядка (включно з пробілами)
  cout << msg << endl;
}
