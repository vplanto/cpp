/* Функція для обчислення суми діапазону масиву (SumArrayRange.cpp) */
#include <iostream>
using namespace std;

// Прототип функції
int sum(const int *begin, const int *end);

int main() {
  int a[] = {8, 4, 5, 3, 2, 1, 4, 8};
  // a - вказівник на початок, a + 8 - вказівник на елемент після останнього
  cout << sum(a, a + 8) << endl;      // a[0] до a[7] (діапазон [begin, end))
  // a + 2 - вказівник на a[2], a + 5 - вказівник на a[5]
  cout << sum(a + 2, a + 5) << endl;  // a[2] до a[4] (end не включається)
  // &a[2] - адреса a[2], &a[5] - адреса a[5]
  cout << sum(&a[2], &a[5]) << endl;  // a[2] до a[4] (еквівалентно попередньому)
}

// Визначення функції
// Повертає суму елементів масиву в діапазоні від begin до end (end не включається)
// Використовує ідіому "вказівників-ітераторів" [begin, end)
int sum(const int *begin, const int *end) {
  int sum = 0;
  // Цикл від begin до end (end не включається)
  for (const int *p = begin; p != end; ++p) {
    sum += *p;  // Додаємо значення, на яке вказує p
  }
  return sum;
}
