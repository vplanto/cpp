#include <iostream>  // Бібліотека для вводу/виводу
#include <string>    // Бібліотека для класу string
using namespace std;

int main() {
  string str = "Hello, World!";  // Оголошення та ініціалізація об'єкта string

  // Використання методу 'at' для доступу та зміни символів
  cout << "Original string: " << str << endl;

  // Доступ до символу за індексом 7 через метод at()
  // at() повертає посилання (char&), що дозволяє змінювати символ
  // at() перевіряє межі масиву (викидає виняток, якщо індекс некоректний)
  char& ch = str.at(7);  // ch - посилання на символ у позиції 7
  cout << "Character at index 7: " << ch << endl;

  // Зміна символу через посилання
  ch = 'w';  // Змінюємо символ у рядку str через посилання ch

  // Виведення зміненого рядка
  cout << "Modified string: " << str << endl;

  return 0;
}
