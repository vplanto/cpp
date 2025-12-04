#include <fstream>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

int main() {
  // Відкриття файлу для читання
  ifstream file("example_stream.txt");

  if (!file) {
    cerr << "Error opening file for reading." << endl;
    return 1;
  }

  string line;

  // Читання та обробка даних
  while (getline(file, line)) {
    // Перевірка стану файлового потоку через прапорці стану:
    if (file.bad()) {
      // bad() - критична помилка (наприклад, помилка диска)
      cerr << "Bad file operation." << endl;
      break;
    } else if (file.fail()) {
      // fail() - помилка формату або логічна помилка (наприклад, некоректні дані)
      cerr << "Fail bit set - possible format error or read error." << endl;
      file.clear();  // Скидання прапорця помилки
      // ignore() - пропуск символів до '\n' або до максимальної кількості
      file.ignore(numeric_limits<streamsize>::max(), '\n');
    } else if (file.eof()) {
      // eof() - досягнуто кінця файлу
      cout << "Reached end of file." << endl;
      break;
    } else if (file.good()) {
      // good() - потік у нормальному стані, операція успішна
      cout << "Read line: " << line << endl;
    }
  }

  // Очищення прапорців та закриття файлу
  file.clear();
  file.close();

  // Спроба відкриття файлу для запису для демонстрації обробки помилок
  // ios::app - режим додавання (append)
  ofstream outfile("example_stream.txt", ios::app);
  if (!outfile) {
    cerr << "Error opening file for writing." << endl;
    return 1;
  }

  // Симуляція операції запису та перевірка стану
  outfile << "Adding new line to file." << endl;
  if (outfile.bad()) {
    cerr << "Bad write operation." << endl;
  } else if (outfile.fail()) {
    cerr << "Fail bit set during write operation." << endl;
  } else if (outfile.good()) {
    cout << "Write operation successful." << endl;
  }

  // Очищення прапорців та закриття файлу
  outfile.clear();
  outfile.close();

  return 0;
}
