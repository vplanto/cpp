#include <iostream>  // Бібліотека для вводу/виводу
using namespace std;

// Прототип функції з параметром за замовчуванням
// depth = 0 - параметр за замовчуванням (якщо не вказано, використовується 0)
int factorial(int n, int depth = 0);

int main() {
  int number;

  // Запитуємо у користувача число
  cout << "Enter a positive integer: ";
  cin >> number;

  // Обчислення та виведення факторіалу за допомогою рекурсивної функції
  // Викликаємо функцію без параметра depth (використається значення за замовчуванням 0)
  cout << "Factorial of " << number << " = " << factorial(number) << endl;

  return 0;  // Успішне завершення програми
}

// Рекурсивна функція для обчислення факторіалу з відстеженням глибини рекурсії
// depth - глибина рекурсії (для візуалізації викликів)
int factorial(int n, int depth) {
  // Виведення інформації про стек викликів
  // string(depth, ' ') - створює рядок з depth пробілів для відступу
  cout << string(depth, ' ') << "factorial(" << n << ") called" << endl;

  // Базовий випадок: факторіал 1 (або 0) дорівнює 1
  if (n <= 1) {
    cout << string(depth, ' ') << "Returning 1" << endl;
    return 1;
  } else {
    // Рекурсивний випадок: n * факторіал (n-1)
    // depth + 1 - збільшуємо глибину для наступного виклику
    int result = n * factorial(n - 1, depth + 1);
    cout << string(depth, ' ') << "Returning " << result << endl;
    return result;
  }
}
