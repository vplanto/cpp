/* Тестування циклу for-each (TestForEach.cpp) */
#include <iostream>  // Бібліотека для вводу/виводу
using namespace std;

int main() {
  int numbers[] = {11, 22, 33, 44, 55};  // Оголошення масиву з 5 елементів

  // Цикл for-each (діапазонний for): для кожного елемента number з масиву numbers
  // У цьому випадку number - це копія елемента, тому зміни не впливають на масив
  for (int number : numbers) {  // number приймає значення кожного елемента масиву
    cout << number << " ";
  }
  cout << endl;
  cout << "next array is going to be modified" << endl;
  // Для зміни елементів масиву потрібно використовувати посилання (&)
  // &number - посилання на елемент масиву, зміни впливають на оригінальний масив
  for (int &number : numbers) {  // number - посилання на елемент масиву
    number = 99;  // Змінюємо значення елемента масиву через посилання
  }

  // Виведення зміненого масиву
  for (int number : numbers) {
    cout << number << endl;
  }
  return 0;  // Успішне завершення програми
}
