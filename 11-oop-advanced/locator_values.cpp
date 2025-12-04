#include <iostream>
using namespace std;

int main() {
  // lvalue (left value) - об'єкт, що має адресу в пам'яті, може бути зліва від =
  int x = 10;     // 'x' - це lvalue (має адресу в пам'яті)
  // rvalue (right value) - тимчасове значення виразу, не має адреси
  int y = x + 5;  // 'x + 5' - це rvalue (тимчасовий результат виразу)

  cout << "x (lvalue): " << x << endl;
  cout << "x + 5 (rvalue): " << y << endl;

  // Використання rvalue безпосередньо
  int z = 20;  // '20' - це rvalue (літерал), який використовується для ініціалізації lvalue z
  cout << "z (lvalue initialized by rvalue): " << z << endl;

  return 0;
}
