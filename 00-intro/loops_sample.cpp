/* Запитуємо у користувача додатні цілі числа та виводимо кількість, максимум,
   мінімум та середнє значення. Введення завершується значенням -1 (StatNumbers.cpp) */
#include <climits>  // Бібліотека для констант обмежень цілих типів (INT_MAX, INT_MIN тощо)
#include <iomanip>  // Бібліотека для маніпуляторів форматування виводу (setprecision)
#include <iostream> // Бібліотека для вводу/виводу
using namespace std;

int main() {
  int numberIn;       // Змінна для зберігання введеного числа (додатнє ціле)
  int count = 0;      // Лічильник введених чисел, ініціалізований як 0
  int sum = 0;        // Сума введених чисел, ініціалізована як 0
  int max = 0;        // Максимальне значення, ініціалізоване як мінімальне
  int min = INT_MAX;  // Мінімальне значення, ініціалізоване як максимальне (потрібна <climits>)
  int sentinel = -1;  // Страж-значення для завершення вводу

  // Читаємо введені числа до зустрічі страж-значення
  cout << "Enter a positive integer or " << sentinel << " to exit: ";
  // Умова циклу: cin >> numberIn повертає true, якщо введення успішне, і перевіряємо, чи не дорівнює numberIn sentinel
  while (cin >> numberIn && numberIn != sentinel) {
    // Перевірка, чи введене число додатнє
    if (numberIn > 0) {  // Оператор if виконує код, якщо умова істинна
      ++count;           // Збільшуємо лічильник на 1
      sum += numberIn;   // Оператор += додає numberIn до sum (еквівалентно sum = sum + numberIn)
      // Тернарний оператор: якщо max < numberIn, то max = numberIn, інакше max залишається незмінним
      max = (max < numberIn) ? numberIn : max;
      if (min > numberIn) min = numberIn;  // Оновлюємо мінімум, якщо знайдено менше значення
    } else {  // Блок else виконується, якщо умова if хибна
      cout << "error: input must be positive! try again..." << endl;
    }
    cout << "Enter a positive integer or " << sentinel << " to exit: ";
  }

  // Виведення результатів
  cout << endl;  // Порожній рядок для відступу
  cout << "Count is " << count << endl;
  if (count > 0) {  // Перевірка, чи були введені числа (щоб уникнути ділення на нуль)
    cout << "Maximum is " << max << endl;
    cout << "Minimum is " << min << endl;
    cout << fixed << setprecision(2);  // fixed - фіксований формат, setprecision(2) - 2 знаки після коми
    // Виведення середнього значення з 2 знаками після коми (потрібна <iomanip>)
    // (double)sum - явне приведення типу до double для отримання дробового результату ділення
    cout << "Average is " << (double)sum / count << endl;
  }

  return 0;  // Успішне завершення програми
}
