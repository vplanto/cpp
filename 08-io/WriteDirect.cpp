#include <cstdio>
#include <cstring>
#include <unistd.h>

int write_direct() {
  FILE *file = fopen("example_direct.txt", "w");
  if (file != nullptr) {
    const char *text = "Writing this to a file\n";
    fwrite(text, sizeof(char), strlen(text), file);
    sleep(1); // Pauses the program for ? seconds
    fclose(file);
  } else {
    printf("Failed to open file.\n");
  }
  return 0;
}
