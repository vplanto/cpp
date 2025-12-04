#include <bits/stdc++.h>  // Включає всі стандартні бібліотеки
using namespace std;

int main() {
  vector<int> v;  // Створення порожнього vector
  // Вставка елементів
  for (int i = 0; i < 10; i++) {
    v.push_back(i * 10);  // Додавання елементів в кінець
  }
  // size() - поточна кількість елементів у vector
  cout << "The size of vector is " << v.size();
  // capacity() - максимальна кількість елементів, яку може зберігати vector
  // без перевиділення пам'яті (зазвичай більше за size())
  cout << "\nThe maximum capacity is " << v.capacity();
  return 0;
}
