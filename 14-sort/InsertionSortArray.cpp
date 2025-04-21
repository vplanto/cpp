#include <iostream>
using namespace std;
//{2,1}
void insertionSort(int arr[], int n) {
  int i, key, j;
  for (i = 1; i < n; i++) {
    key = arr[i];//1
    j = i - 1;//0

    while (j >= 0 && arr[j] > key) {//2>1
      arr[j + 1] = arr[j];//arr[1]=arr[0]=2
      j = j - 1;//j=-1
    }
    arr[j + 1] = key;//arr[0]=1
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
