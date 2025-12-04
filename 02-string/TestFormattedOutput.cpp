/* Тестування форматування виводу (TestFormattedOutput.cpp) */
#include <iomanip>  // Бібліотека для маніпуляторів форматування вводу/виводу
#include <iostream> // Бібліотека для вводу/виводу
using namespace std;

int main() {
  // Форматування дробових чисел
  double pi = 3.14159265;
  // fixed - фіксований формат (не наукова нотація)
  // setprecision(4) - 4 знаки після коми (працює разом з fixed)
  cout << fixed << setprecision(4);  // Фіксований формат з 4 знаками після коми
  cout << pi << endl;
  // setw(8) - встановлює ширину поля виводу (8 символів)
  // setw() не є "липким" - діє тільки на наступну операцію виводу
  cout << "|" << setw(8) << pi << "|" << setw(10) << pi << "|" << endl;
  // setfill('-') - встановлює символ заповнення (за замовчуванням пробіл)
  cout << setfill('-');
  cout << "|" << setw(8) << pi << "|" << setw(10) << pi << "|" << endl;
  // scientific - науковий формат з експонентою
  cout << scientific;  // Науковий формат з експонентою
  cout << pi << endl;

  // Форматування булевих значень
  bool done = false;
  cout << done << endl;  // Виведення 0 (для false) або 1 (для true)
  // boolalpha - виведення true/false замість 1/0
  cout << boolalpha;     // Виведення true або false як текст
  cout << done << endl;
  return 0;
}
