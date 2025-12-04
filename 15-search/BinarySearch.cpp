#include <iostream>
using namespace std;

// Бінарний пошук (Binary Search)
// Складність: O(log n) - на кожній ітерації відкидаємо половину елементів
// Вимога: масив має бути відсортований
// Принцип: "діли і володарюй" - порівнюємо з середнім елементом
int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        // Обчислення середнього індексу (запобігає переповненню)
        // l + (r - l) / 2 замість (l + r) / 2 для безпеки
        int m = l + (r - l) / 2;
        if (arr[m] == x)
            return m;  // Елемент знайдено
        if (arr[m] < x)
            l = m + 1;  // Шукаємо в правій половині
        else
            r = m - 1;  // Шукаємо в лівій половині
        // УВАГА: рекурсивний виклик не використовується (while цикл)
        binarySearch(arr,l,r,x);  // Цей рядок не має ефекту в ітеративній версії
    }
    return -1;  // Елемент не знайдено
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};  // Масив має бути відсортований
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 10;
    int result = binarySearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
                   : cout << "Element is present at index " << result;
    return 0;
}
