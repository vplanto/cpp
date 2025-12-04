/* Тестування обмежень цілих типів у заголовочному файлі <climits> */
#include <iostream>  // Бібліотека для вводу/виводу
#include <climits>   // Бібліотека з константами обмежень цілих типів
using namespace std; // Використання стандартного простору імен
 
int main() {
   // Виведення максимальних та мінімальних значень різних цілих типів
   // Ці константи визначені в <climits> та показують межі, які може зберігати кожен тип
   cout << "int max = " << INT_MAX << endl;              // Максимальне значення типу int
   cout << "int min = " << INT_MIN << endl;              // Мінімальне значення типу int
   cout << "unsigned int max = " << UINT_MAX << endl;   // Максимальне значення беззнакового int
   cout << "long long max = " << LLONG_MAX << endl;     // Максимальне значення типу long long
   cout << "long long min = " << LLONG_MIN << endl;     // Мінімальне значення типу long long
   cout << "unsigned long long max = " << ULLONG_MAX << endl; // Максимальне значення беззнакового long long
   cout << "Bits in char = " << CHAR_BIT << endl;       // Кількість бітів у байті (зазвичай 8)
   cout << "char max = " << CHAR_MAX << endl;           // Максимальне значення типу char
   cout << "char min = " << CHAR_MIN << endl;           // Мінімальне значення типу char
   cout << "signed char max = " << SCHAR_MAX << endl;   // Максимальне значення знакового char
   cout << "signed char min = " << SCHAR_MIN << endl;   // Мінімальне значення знакового char
   cout << "unsigned char max = " << UCHAR_MAX << endl; // Максимальне значення беззнакового char
   return 0;  // Успішне завершення програми
}
