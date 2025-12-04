// Базові операції з файлами
#include <unistd.h>

#include <fstream>
#include <iostream>
using namespace std;

int write_stream_ext() {
  ofstream myfile;
  // Відкриття файлу без режиму - за замовчуванням режим перезапису (ios::out)
  myfile.open("example_stream.txt");
  for (int i = 0; i < 60; i++) {
    myfile << i << "Writing this to a file\n";  // Дія, що виконується
  }
  // Навмисний segmentation fault для аварійного завершення програми (закоментовано)
  // int *ptr = nullptr;
  // *ptr = 10;
  // flush() - примусове записання буфера на диск
  // Дані можуть бути в буфері, flush() гарантує їх запис
  myfile.flush();
  myfile << "Writing this to a file\n";
  sleep(60);  // Пауза програми на 60 секунд
  myfile.close();
  return 0;
}

int main() { return write_stream_ext(); };
