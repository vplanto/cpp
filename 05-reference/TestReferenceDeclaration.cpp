/* Тестування оголошення та ініціалізації посилань (TestReferenceDeclaration.cpp) */
#include <iostream>
using namespace std;

int main() {
  int number = 88;  // Оголошення змінної типу int
  int& refNumber =
      number;  // Оголошення посилання (псевдоніма) на змінну number
               // Посилання - це альтернативне ім'я для змінної
               // refNumber та number вказують на одну й ту саму змінну в пам'яті

  cout << number << endl;     // Виведення значення змінної number
  cout << refNumber << endl;  // Виведення значення через посилання (те саме значення)

  refNumber = 99;  // Присвоєння нового значення через посилання
  cout << refNumber << endl;
  cout << number << endl;  // Значення number також змінилося (зміна через посилання)

  number = 55;  // Присвоєння нового значення безпосередньо змінній
  cout << number << endl;
  cout << refNumber << endl;  // Значення refNumber також змінилося (те саме місце в пам'яті)
}
