#include <iostream>
using namespace std;

int main() {
  // Declare and initialize a 2D array (matrix) with 3 rows and 3 columns
  int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  // Variables to hold sums of rows and columns
  int rowSum[3] = {0, 0, 0};
  int colSum[3] = {0, 0, 0};

  // Calculate the sum of each row
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      rowSum[i] += matrix[i][j];  // Add element to the corresponding row sum
    }
  }

  // Calculate the sum of each column
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 3; i++) {
      colSum[j] += matrix[i][j];  // Add element to the corresponding column sum
    }
  }

  // Print the sum of each row
  for (int i = 0; i < 3; i++) {
    cout << "Sum of row " << i + 1 << ": " << rowSum[i] << endl;
  }

  // Print the sum of each column
  for (int j = 0; j < 3; j++) {
    cout << "Sum of column " << j + 1 << ": " << colSum[j] << endl;
  }

  return 0;  // End of program
}
