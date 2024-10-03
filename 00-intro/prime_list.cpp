/*
 *  List primes from 1 to an upperbound (PrimeList.cpp).
 */
#include <cmath>
#include <iostream>
using namespace std;

int main() {
  int upperbound;
  cout << "Enter the upperbound: ";
  cin >> upperbound;

  for (int number = 2; number <= upperbound; ++number) {
    // Not prime, if there is a factor between 2 and sqrt of number
    int maxFactor = (int)sqrt(number);
    bool isPrime = true;
    int factor = 2;
    while (isPrime && factor <= maxFactor) {
      if (number % factor == 0) {  // Factor of number?
        isPrime = false;
      }
      ++factor;
    }
    if (isPrime) cout << number << " ";
  }
  cout << endl;
  return 0;
}
