/* Тестування вводу та виводу класу string (TestStringIO.cpp) */
#include <iostream>  // Бібліотека для вводу/виводу
#include <limits>    // Бібліотека для numeric_limits
#include <string>    // Заголовочний файл для використання класу string
using namespace std; // Також потрібен для <string>

int main() {
  // Конструктор string() створює об'єкт string з рядкового літералу
  string message("Hello");
  cout << message << endl;

  // Введення слова (розділеного пробілом) у string
  // Оператор >> читає тільки до першого пробілу або символу нового рядка
  cout << "Enter a message (no space): ";
  cin >> message;  // Читання одного слова
  cout << message << endl;

  // Очищення буфера вводу до символу нового рядка
  // numeric_limits<streamsize>::max() - максимальна кількість символів для ігнорування
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  // Очищення cin до нового рядка (потрібна бібліотека <limits>)

  // Введення цілого рядка (включно з пробілами) у string
  cout << "Enter a message (with spaces): ";
  // getline() читає весь рядок включно з пробілами до символу нового рядка
  getline(cin, message); // Читання вводу з cin у message
  cout << message << endl;
  return 0;
}
