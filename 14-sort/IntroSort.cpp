/* Програма для сортування масиву за допомогою Introsort.
Найпопулярніший алгоритм C++ STL - sort()
використовує Introsort. */

#include <bits/stdc++.h>
using namespace std;

// Утиліта для обміну значень, на які вказують два вказівники
// УВАГА: ця функція обмінює вказівники, а не значення (помилка в реалізації)
void swapValue(int *a, int *b) {
  int *temp = a;
  a = b;
  b = temp;
  return;
}

/* Функція сортування підмасиву за допомогою insertion sort*/
void InsertionSort(int arr[], int *begin, int *end) {
  // Отримання лівого та правого індексів підмасиву для сортування
  int left = begin - arr;   // Арифметика вказівників: begin - arr дає індекс
  int right = end - arr;

  for (int i = left + 1; i <= right; i++) {
    int key = arr[i];
    int j = i - 1;

    /* Зсув елементів arr[0..i-1], що більші за key,
      на одну позицію вперед від їх поточної позиції */
    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }

  return;
}

// Функція розбиття масиву (partition) та повернення точки розбиття
// Використовується в Quick Sort
int *Partition(int arr[], int low, int high) {
  int pivot = arr[high]; // Опорний елемент (pivot)
  int i = (low - 1);     // Індекс меншого елемента

  for (int j = low; j <= high - 1; j++) {
    // Якщо поточний елемент менший або дорівнює опорному
    if (arr[j] <= pivot) {
      // Збільшення індексу меншого елемента
      i++;

      swap(arr[i], arr[j]);  // Обмін елементів
    }
  }
  swap(arr[i + 1], arr[high]);  // Розміщення опорного елемента в правильну позицію
  return (arr + i + 1);          // Повернення вказівника на позицію опорного елемента
}

// Функція знаходження медіани з трьох значень, на які вказують вказівники a, b, c
// Повертає вказівник на медіану (використовується для вибору хорошого опорного елемента)
int *MedianOfThree(int *a, int *b, int *c) {
  if (*a < *b && *b < *c)
    return (b);

  if (*a < *c && *c <= *b)
    return (c);

  if (*b <= *a && *a < *c)
    return (a);

  if (*b < *c && *c <= *a)
    return (c);

  if (*c <= *a && *a < *b)
    return (a);

  if (*c <= *b && *b <= *c)
    return (b);
}

// Утиліта для виконання introsort
// Introsort - гібридний алгоритм: Quick Sort + Heap Sort + Insertion Sort
// depthLimit - обмеження глибини рекурсії для запобігання O(n²) у Quick Sort
void IntrosortUtil(int arr[], int *begin, int *end, int depthLimit) {
  // Підрахунок кількості елементів
  int size = end - begin;

  // Якщо розмір підмасиву малий, використовуємо insertion sort
  // Insertion sort ефективний для малих масивів
  if (size < 16) {
    InsertionSort(arr, begin, end);
    return;
  }

  // Якщо глибина рекурсії досягла нуля, використовуємо heapsort
  // Heapsort гарантує O(n log n) складність
  if (depthLimit == 0) {
    make_heap(begin, end + 1);  // Створення купи
    sort_heap(begin, end + 1);  // Сортування купи
    return;
  }

  // Інакше використовуємо концепцію медіани з трьох для знаходження хорошого опорного елемента
  int *pivot = MedianOfThree(begin, begin + size / 2, end);

  // Обмін значень, на які вказують два вказівники
  swapValue(pivot, end);

  // Виконання Quick Sort
  int *partitionPoint = Partition(arr, begin - arr, end - arr);
  // Рекурсивне сортування лівої та правої частин
  IntrosortUtil(arr, begin, partitionPoint - 1, depthLimit - 1);
  IntrosortUtil(arr, partitionPoint + 1, end, depthLimit - 1);

  return;
}

/* Реалізація introsort*/
void Introsort(int arr[], int *begin, int *end) {
  // Обчислення обмеження глибини: 2 * log(кількість елементів)
  int depthLimit = 2 * log(end - begin);

  // Виконання рекурсивного Introsort
  IntrosortUtil(arr, begin, end, depthLimit);

  return;
}

// Утиліта для виведення масиву розміру n
void printArray(int arr[], int n) {
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

// Тестова програма для Introsort
int main() {
  int arr[] = {3, 1, 23, -9, 233, 23, -313, 32, -9};
  int n = sizeof(arr) / sizeof(arr[0]);

  // Передача масиву, вказівника на перший елемент та
  // вказівника на останній елемент
  Introsort(arr, arr, arr + n - 1);
  printArray(arr, n);

  return (0);
}

