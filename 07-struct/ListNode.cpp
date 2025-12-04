#include <stdio.h>  // Бібліотека для вводу/виводу
#include <stdlib.h> // Бібліотека для функцій виділення пам'яті (malloc, free)

// Структура вузла зв'язаного списку
// Рекурсивна структура: структура містить вказівник на саму себе
typedef struct Node {
    int data;           // Дані вузла
    struct Node *next;  // Вказівник на наступний вузол (рекурсивна структура)
} Node;

// Функція для створення нового вузла з заданими даними
Node* createNode(int data) 
{
    // malloc(sizeof(Node)) - виділення пам'яті для структури Node
    // (Node *) - приведення типу void* до Node*
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {                               // Перевірка на помилку виділення пам'яті
        perror("Failed to allocate memory");      // Виведення повідомлення про помилку
        exit(EXIT_FAILURE);                       // Завершення програми з кодом помилки
    }
    newNode->data = data;     // Присвоєння даних новому вузлу
    newNode->next = NULL;     // Ініціалізація вказівника на NULL (кінець списку)
    return newNode;           // Повернення нового вузла
}

// Функція для додавання нового вузла в кінець списку
// Node **head - вказівник на вказівник (для зміни head у main)
void append(Node **head, int data) 
{
    Node *newNode = createNode(data); // Створення нового вузла
    if (*head == NULL) {              // Якщо список порожній
        *head = newNode;              // Новий вузол стає головою списку
        return;
    }
    Node *temp = *head;               // Тимчасовий вказівник для проходження списку
    while (temp->next != NULL)        // Прохід до останнього вузла
        temp = temp->next;            // Перехід до наступного вузла
    temp->next = newNode;             // Додавання нового вузла в кінець
}

// Функція для виведення зв'язаного списку
void printList(Node *head) 
{
    while (head != NULL) {            // Прохід по списку
        printf("%d -> ", head->data); // Виведення даних поточного вузла
        head = head->next;            // Перехід до наступного вузла
    }
    printf("NULL\n");                 // Виведення NULL в кінці списку
}

// Функція для звільнення пам'яті, виділеної для списку
void freeList(Node *head) 
{
    Node *temp;                       // Тимчасовий вказівник для зберігання поточного вузла
    while (head != NULL) {            // Прохід по списку
        temp = head;                  // Зберігання поточного вузла
        head = head->next;            // Перехід до наступного вузла
        free(temp);                   // Звільнення пам'яті поточного вузла
    }
}

int main(int argc, char *argv[]) 
{
    Node *head = NULL;                // Ініціалізація голови списку як NULL

    append(&head, 10);                // Додавання 10 до списку
    append(&head, 20);                // Додавання 20 до списку
    append(&head, 30);                // Додавання 30 до списку

    printList(head);                  // Виведення списку: 10 -> 20 -> 30 -> NULL

    freeList(head);                   // Звільнення пам'яті списку
    head = NULL;                      // Встановлення head в NULL

    return 0;
}
