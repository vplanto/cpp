/*
 * Виведення розмірів фундаментальних типів даних (SizeofTypes.cpp).
 * Оператор sizeof повертає кількість байтів, які займає тип даних у пам'яті.
 */
#include <iostream>  // Бібліотека для вводу/виводу
using namespace std; // Використання стандартного простору імен
 
int main() {
   // Оператор sizeof визначає розмір типу даних у байтах
   // Розміри можуть відрізнятися залежно від компілятора та архітектури системи
   cout << "sizeof(char) is " << sizeof(char) << " bytes " << endl;           // Зазвичай 1 байт
   cout << "sizeof(short) is " << sizeof(short) << " bytes " << endl;         // Зазвичай 2 байти
   cout << "sizeof(int) is " << sizeof(int) << " bytes " << endl;             // Зазвичай 4 байти
   cout << "sizeof(long) is " << sizeof(long) << " bytes " << endl;          // Зазвичай 4 або 8 байтів
   cout << "sizeof(long long) is " << sizeof(long long) << " bytes " << endl; // Зазвичай 8 байтів
   cout << "sizeof(float) is " << sizeof(float) << " bytes " << endl;        // Зазвичай 4 байти
   cout << "sizeof(double) is " << sizeof(double) << " bytes " << endl;      // Зазвичай 8 байтів
   cout << "sizeof(long double) is " << sizeof(long double) << " bytes " << endl; // Зазвичай 8, 12 або 16 байтів
   cout << "sizeof(bool) is " << sizeof(bool) << " bytes " << endl;          // Зазвичай 1 байт
   return 0;  // Успішне завершення програми
}
