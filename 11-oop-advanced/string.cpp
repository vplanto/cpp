/* Тестування перевантажених операторів у класі string C++
   (TestStringOverloadOperators.cpp) */
#include <iostream>
#include <string>  // Потрібно для використання класу string
using namespace std;

int main() {
  string msg1("hello");
  string msg2("HELLO");
  string msg3("hello");

  // Оператори порівняння (порівнюють вміст рядків, а не адреси)
  cout << boolalpha;  // Виведення true/false замість 1/0
  cout << (msg1 == msg2) << endl;  // false - порівняння вмісту
  cout << (msg1 == msg3) << endl;  // true - однаковий вміст
  cout << (msg1 < msg2) << endl;   // false (великі літери перед малими в ASCII)

  // Оператор присвоєння (копіювання вмісту)
  string msg4 = msg1;  // Викликається оператор присвоєння копіювання
  cout << msg4 << endl;  // hello

  // Конкатенація (об'єднання рядків)
  cout << (msg1 + " " + msg2) << endl;  // hello HELLO (оператор +)
  msg3 += msg2;  // Оператор += (додавання в кінець)
  cout << msg3 << endl;  // helloHELLO

  // Індексація (доступ до символів)
  cout << msg1[1] << endl;   // 'e' - оператор [] (без перевірки меж)
  cout << msg1[99] << endl;  // Сміття (немає перевірки меж індексу)
  // cout << msg1.at(99) << endl; // Виняток out_of_range (at() перевіряє межі)
}
