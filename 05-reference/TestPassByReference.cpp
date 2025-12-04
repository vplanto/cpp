/* Передача параметрів за посиланням (TestPassByReference.cpp) */
#include <iostream>
using namespace std;

void square(int &);

int main() {
  int number = 8;
  cout << "In main(): " << &number << endl;  // Адреса number у main()
  cout << number << endl;                    // 8
  square(number);          // Неявне посилання (без '&')
                           // number передається за посиланням, не створюється копія
  cout << number << endl;  // 64 - значення змінилося через посилання
}

void square(int &rNumber) {  // Функція приймає посилання на int (не const)
  cout << "In square(): " << &rNumber << endl;  // Адреса така сама, як у main()
                                                  // rNumber - це посилання на number
  rNumber *= rNumber;  // Неявне розіменування (без '*')
                       // Зміна значення через посилання впливає на оригінальну змінну
}
