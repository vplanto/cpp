#include <stdio.h>

// Визначення структури з двома полями: num та denum
typedef struct {
  int num;    // Чисельник
  int denum;  // Знаменник
} fraction;

int main() {
  // Оголошення змінної типу fraction
  fraction pi;

  // Присвоєння значень полям
  pi.num = 7;
  pi.denum = 22;

  // Виведення початкових значень
  printf("Initial values: num = %d, denum = %d\n", pi.num, pi.denum);

  // Маніпуляція вказівником для зміни поля num через адресу поля denum
  // &(pi.denum) - адреса поля denum
  // (fraction*) - приведення типу до вказівника на fraction
  // ->num - доступ до поля num через вказівник
  // Це небезпечна операція, що може призвести до невизначеної поведінки!
  ((fraction*)&(pi.denum))->num = 12;

  // Виведення змінених значень
  printf("Modified values: num = %d, denum = %d\n", pi.num, pi.denum);

  return 0;
}
