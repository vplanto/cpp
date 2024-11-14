#include <stdio.h>

// Define the struct with two fields: num and denum
typedef struct {
    int num;
    int denum;
} fraction;

int main() {
    // Declare a variable of type fraction
    fraction pi;

    // Assign values to the fields
    pi.num = 7;
    pi.denum = 22;

    // Print the initial values
    printf("Initial values: num = %d, denum = %d\n", pi.num, pi.denum);

    // Manipulate the pointer to change the num field via the denum field's address
    ((fraction*)&(pi.denum))->num = 12;

    // Print the modified values
    printf("Modified values: num = %d, denum = %d\n", pi.num, pi.denum);

    return 0;
}
