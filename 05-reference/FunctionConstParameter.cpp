/* Тестування const та non-const параметрів функцій (FunctionConstParameter.cpp) */
#include <iostream>
using namespace std;

int squareConst(const int);
int squareNonConst(int);
int squareConstRef(const int &);
int squareNonConstRef(int &);

int main() {
  int number = 8;
  const int constNumber = 9;  // Константна змінна
  // const int можна передати в функцію, що приймає const int або int (копія)
  cout << squareConst(number) << endl;        // Працює: int -> const int
  cout << squareConst(constNumber) << endl;  // Працює: const int -> const int
  cout << squareNonConst(number) << endl;    // Працює: int -> int
  cout << squareNonConst(constNumber) << endl; // Працює: const int -> int (копія)

  // const int можна передати за const посиланням, але не за non-const посиланням
  cout << squareConstRef(number) << endl;        // Працює: int -> const int&
  cout << squareConstRef(constNumber) << endl;    // Працює: const int -> const int&
  cout << squareNonConstRef(number) << endl;     // Працює: int -> int&
  // cout << squareNonConstRef(constNumber) << endl; // ПОМИЛКА!
  // error: invalid initialization of reference of type 'int&' from expression of type 'const int'
  // Не можна створити non-const посилання на const змінну
}

int squareConst(const int number) {
  // number *= number;  // ПОМИЛКА: спроба змінити read-only параметр
  // const параметр не можна змінювати всередині функції
  return number * number;
}

int squareNonConst(int number) {  // non-const параметр (копія)
  number *= number;  // Можна змінювати (це копія, не впливає на оригінал)
  return number;
}

int squareConstRef(const int &number) {  // const посилання
  // number не можна змінювати, але передача за посиланням ефективніша за копіювання
  return number * number;
}

int squareNonConstRef(int &number) {  // non-const посилання
  // Можна змінювати number, але не можна передати const змінну
  return number * number;
}
