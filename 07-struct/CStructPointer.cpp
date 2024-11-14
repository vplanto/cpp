#include <stdio.h>

typedef struct {
    int id;
    char name[20];
} Person;

int main(int argc, char *argv[]) 
{
    Person person = {1, "Alice"};
    Person *ptr = &person;

    // Access using arrow operator
    printf("ID: %d, Name: %s\n", ptr->id, ptr->name);

    // Modify using dereferencing
    (*ptr).id = 2;
    printf("Updated ID: %d\n", person.id);

    return 0;
}

