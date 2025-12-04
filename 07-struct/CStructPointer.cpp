#include <stdio.h>

// typedef struct - створення псевдоніма типу для структури
// Дозволяє використовувати Person замість struct Person
typedef struct {
    int id;
    char name[20];  // Масив символів фіксованого розміру
} Person;

int main(int argc, char *argv[]) 
{
    Person person = {1, "Alice"};  // Ініціалізація структури
    Person *ptr = &person;        // Вказівник на структуру

    // Доступ до полів структури через вказівник: оператор -> (стрілка)
    // ptr->id еквівалентно (*ptr).id
    printf("ID: %d, Name: %s\n", ptr->id, ptr->name);

    // Зміна через розіменування: (*ptr).id - спочатку розіменуємо, потім доступ до поля
    (*ptr).id = 2;
    printf("Updated ID: %d\n", person.id);  // Значення змінилося через вказівник

    return 0;
}

