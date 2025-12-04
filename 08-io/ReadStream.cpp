#include <fstream>   // Бібліотека для роботи з файлами (ifstream, ofstream)
#include <iostream>  // Бібліотека для вводу/виводу
#include <string>    // Бібліотека для класу string

void read_stream() {
  // ifstream - вхідний файловий потік для читання з файлу
  // Конструктор відкриває файл "example_stream.txt"
  std::ifstream myfile("example_stream.txt");
  if (myfile.is_open()) {  // Перевірка, чи файл успішно відкрито
    std::string line;
    // getline() читає рядок з файлу до символу нового рядка
    // Цикл виконується, поки є рядки для читання
    while (getline(myfile, line)) {
      std::cout << line << std::endl;
    }
    myfile.close();  // Закриття файлу (вивільняє ресурси)
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}

int main() { read_stream(); }
