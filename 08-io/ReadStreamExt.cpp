#include <fstream>
#include <iostream>
#include <string>

void read_stream_ext() {
  std::ifstream myfile("example_stream.txt");
  if (myfile.is_open()) {
    std::string line;

    // eof() - перевірка, чи досягнуто кінця файлу (end of file)
    // УВАГА: eof() повертає true тільки після спроби читання за межами файлу
    while (!myfile.eof()) {
      getline(myfile, line);
      // Додаткова перевірка eof() необхідна, бо getline може прочитати порожній рядок
      // на кінці файлу, якщо файл закінчується символом нового рядка
      if (!myfile.eof()) {
        std::cout << line << std::endl;
      }
    }

    myfile.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
}
