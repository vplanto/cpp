/*
 *  List non-prime from 1 to an upperbound (NonPrimeList.cpp).
 */
#include <cmath>
#include <iostream>
using namespace std;

int main() {
  int upperbound;
  cout << "Enter the upperbound: ";
  cin >> upperbound;
  for (int number = 2; number <= upperbound; ++number) {
    // Not a prime, if there is a factor between 2 and sqrt(number)
    int maxFactor = (int)sqrt(number);
    for (int factor = 2; factor <= maxFactor; ++factor) {
      if (number % factor == 0) {  // Factor?
        cout << number << " ";
        break;  // A factor found, no need to search for more factors
      }
    }
  }
  cout << endl;
  return 0;
}
