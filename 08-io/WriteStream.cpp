// Базові операції з файлами
#include <unistd.h>  // Бібліотека для sleep()

#include <fstream>
using namespace std;

int write_stream() {
  ofstream myfile;  // ofstream - вихідний файловий потік для запису в файл
  // open() - відкриття файлу з режимом ios::app (додавання в кінець файлу)
  // ios::app - режим додавання: нові дані додаються в кінець файлу
  myfile.open("example_stream.txt", ios::app);
  // Оператор << для запису в файл (аналогічно cout)
  myfile << "Writing this to a file\n";
  sleep(1);  // Пауза програми на 1 секунду
  myfile.close();  // Закриття файлу
  return 0;
}

int main() { return write_stream(); };
