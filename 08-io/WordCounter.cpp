#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int word_counter() {
  ifstream file("example_stream.txt");
  // Перевірка на помилку відкриття файлу через перетворення в bool
  // ifstream неявно перетворюється в bool (true, якщо файл відкрито)
  if (!file) {
    cerr << "File could not be opened\n";  // cerr - потік для виводу помилок
    return 1;
  }

  int wordCount = 0;
  string word;

  // Оператор >> читає слово з файлу (до пробілу або символу нового рядка)
  // Цикл виконується, поки є слова для читання
  while (file >> word) {
    ++wordCount;
  }
  file.close();
  cout << "Number of words in the file: " << wordCount << '\n';

  return 0;
}

int main() { return word_counter(); }
