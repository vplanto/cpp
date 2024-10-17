#include <iostream>
using namespace std;

int main() {
  // Declare and initialize an array with 10 integers
  int arr[10] = {23, 45, 12, 67, 34, 89, 21, 90, 76, 50};

  cout << "Please enter array" << endl;
  for (int i = 0; i < 10; i++) {
    cout << "enter index=" << i << endl;
    cin >> arr[i];
  }

  // Variable to hold the maximum value, initialized to the first element of the
  // array
  int max = arr[0];

  // Variable to hold the minimum value, initialized to the first element of the
  // array
  int min = arr[0];

  // Variable to hold the sum of all elements, initialized to 0
  int sum = arr[0];

  // Loop through each element of the array
  for (int i = 1; i < 10; i++) {
    // If current element is greater than max, update max
    if (arr[i] > max) {
      max = arr[i];
    }

    // If current element is less than min, update min
    if (arr[i] < min) {
      min = arr[i];
    }

    // Add current element to sum
    sum += arr[i];
  }

  // Calculate the average of the elements
  double average = static_cast<double>(sum) / 10.0;

  // Print the maximum value
  cout << "Maximum value in the array: " << max << endl;

  // Print the minimum value
  cout << "Minimum value in the array: " << min << endl;

  // Print the average value
  cout << "Average value of the array elements: " << average << endl;

  return 0;  // End of program
}
