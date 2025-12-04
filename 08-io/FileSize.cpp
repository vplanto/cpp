// Отримання розміру файлу
#include <fstream>
#include <iostream>
using namespace std;

int file_size() {
  streampos begin, end;  // streampos - тип для позиції у файловому потоці
  // ios::binary - відкриття файлу в бінарному режимі
  ifstream myfile("example_stream.txt", ios::binary);
  // tellg() - повертає поточну позицію в файлі (get position)
  begin = myfile.tellg();
  // seekg(0, ios::end) - переміщення вказівника читання в кінець файлу
  // 0 - зміщення, ios::end - точка відліку (кінець файлу)
  myfile.seekg(0, ios::end);
  end = myfile.tellg();  // Позиція в кінці файлу
  myfile.close();
  // Різниця позицій дає розмір файлу в байтах
  cout << "size is: " << (end - begin) << " bytes.\n";
  return 0;
}

int main() { return file_size(); };
