#include <cstdio>    // C-стиль бібліотека для роботи з файлами (FILE, fopen, fwrite)
#include <cstring>   // Бібліотека для strlen()
#include <unistd.h>  // Бібліотека для sleep()

int write_direct() {
  // fopen() - C-стиль відкриття файлу
  // "w" - режим запису (write), файл створюється або перезаписується
  FILE *file = fopen("example_direct.txt", "w");
  if (file != nullptr) {
    const char *text = "Writing this to a file\n";
    // fwrite() - C-стиль запису в файл
    // Параметри: дані, розмір елемента, кількість елементів, файловий потік
    fwrite(text, sizeof(char), strlen(text), file);
    sleep(1); // Пауза програми на 1 секунду
    fclose(file);  // Закриття файлу
  } else {
    printf("Failed to open file.\n");
  }
  return 0;
}
