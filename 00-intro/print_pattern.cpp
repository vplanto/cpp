/*
 *  Print square pattern (PrintSquarePattern.cpp).
 */
#include <iostream>
using namespace std;

int main() {
  int size = 8;
  for (int row = 1; row <= size; ++row) {  // Outer loop to print all the rows
    if ((row % 2) == 0) {  // print a leading space for even-numbered rows
      cout << " ";
    }
    for (int col = 1; col <= size;
         ++col) {  // Inner loop to print all the columns of each row
      cout << "# ";
    }
    cout << endl;  // A row ended, bring the cursor to the next line
  }

  return 0;
}
