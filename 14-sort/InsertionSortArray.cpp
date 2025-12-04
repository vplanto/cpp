#include <iostream>
using namespace std;

// Алгоритм сортування вставками (Insertion Sort)
// Складність: O(n²) у найгіршому випадку, O(n) у найкращому (вже відсортований масив)
// Приклад: {2,1}
void insertionSort(int arr[], int n) {
  int i, key, j;
  // Починаємо з другого елемента (індекс 1)
  for (i = 1; i < n; i++) {
    key = arr[i];  // Поточний елемент для вставки
    j = i - 1;     // Індекс попереднього елемента

    // Зсув елементів, більших за key, вправо
    // Пошук правильного місця для вставки key
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];  // Зсув елемента вправо
      j = j - 1;            // Перехід до попереднього елемента
    }
    arr[j + 1] = key;  // Вставка key в правильну позицію
  }
}

int main() {
  int arr[] = {12, 11, 13, 5, 6};
  int n = sizeof(arr) / sizeof(arr[0]);

  insertionSort(arr, n);

  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";
  return 0;
}
