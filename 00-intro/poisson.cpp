/*
 * Розрахунок ймовірностей розподілу Пуассона P(k) для заданого λ.
 * Формула: P(k) = (λ^k * e^(-λ)) / k!
 * (poisson.cpp)
 */
#include <cmath>     // exp(), pow()
#include <iostream>  // cin, cout
using namespace std;

// Обчислення k! через цикл (0! = 1)
long long factorial(int n) {
  long long result = 1;
  for (int i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

double poissonProbability(double lambda, int k) {
  return (pow(lambda, k) * exp(-lambda)) / factorial(k);
}

int main() {
  double lambda;

  cout << "Enter lambda (mean): ";
  cin >> lambda;

  const int maxK = 5;
  for (int k = 0; k <= maxK; ++k) {
    cout << k << " - " << poissonProbability(lambda, k) << endl;
  }

  return 0;
}
