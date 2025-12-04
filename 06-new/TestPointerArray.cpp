/* Вказівники та масиви (TestPointerArray.cpp) */
#include <iostream>
using namespace std;

int main() {
  const int SIZE = 5;
  int numbers[SIZE] = {11, 22, 44, 21, 41};  // Масив int

  // Ім'я масиву numbers є вказівником на int, що вказує на перший елемент
  // numbers = &numbers[0] (неявне перетворення імені масиву на вказівник)
  cout << &numbers[0] << endl;     // Адреса першого елемента
  cout << numbers << endl;         // Те саме (ім'я масиву = адреса першого елемента)
  cout << *numbers << endl;        // Еквівалентно numbers[0] (розіменування вказівника)
  cout << *(numbers + 1) << endl;  // Еквівалентно numbers[1] (арифметика вказівників)
  cout << *(numbers + 4) << endl;  // Еквівалентно numbers[4] (арифметика вказівників)
}
