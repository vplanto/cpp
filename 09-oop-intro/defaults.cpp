#include <iostream>

class Example {
 public:
  Example() {}
};

int main() {
  Example ex;
  return 0;
}
// use -g on compile to add debug info
// objdump -d -C to show decompiled code
