#include <iostream>
using namespace std;

// Лінійний пошук (Linear Search)
// Складність: O(n) - перевіряємо кожен елемент послідовно
// Переваги: працює з невідсортованими масивами
// Недоліки: повільний для великих масивів
int linearSearch(int arr[], int n, int x) {
  for (int i = 0; i < n; i++) {
    if (arr[i] == x)
      return i; // Елемент знайдено, повертаємо індекс
  }
  return -1; // Елемент не знайдено
}

int main() {
  int arr[] = {3, 4, 1, 7, 5};
  int n = sizeof(arr) / sizeof(arr[0]);
  int x = 4;

  int result = linearSearch(arr, n, x);
  if (result == -1)
    cout << "Element is not present in the array";
  else
    cout << "Element is present at index " << result;

  return 0;
}
