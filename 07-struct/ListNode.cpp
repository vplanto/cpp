#include <stdio.h>  // Include standard input-output library
#include <stdlib.h> // Include standard library for memory allocation functions

// Node structure
typedef struct Node {
    int data;           // Data part of the node
    struct Node *next;  // Pointer to the next node
} Node;

// Function to create a new node with given data
Node* createNode(int data) 
{
    Node *newNode = (Node *)malloc(sizeof(Node)); // Allocate memory for new node
    if (!newNode) {                               // Check if memory allocation failed
        perror("Failed to allocate memory");      // Print error message
        exit(EXIT_FAILURE);                       // Exit program with failure status
    }
    newNode->data = data;     // Set the data of the new node
    newNode->next = NULL;     // Initialize the next pointer to NULL
    return newNode;           // Return the new node
}

// Function to append a new node with given data to the end of the list
void append(Node **head, int data) 
{
    Node *newNode = createNode(data); // Create a new node
    if (*head == NULL) {              // If the list is empty
        *head = newNode;              // Set the new node as the head
        return;                       // Return from the function
    }
    Node *temp = *head;               // Temporary pointer to traverse the list
    while (temp->next != NULL)        // Traverse to the last node
        temp = temp->next;            // Move to the next node
    temp->next = newNode;             // Set the next of the last node to the new node
}

// Function to print the linked list
void printList(Node *head) 
{
    while (head != NULL) {            // Traverse the list
        printf("%d -> ", head->data); // Print the data of the current node
        head = head->next;            // Move to the next node
    }
    printf("NULL\n");                 // Print NULL at the end of the list
}

// Function to free the memory allocated for the list
void freeList(Node *head) 
{
    Node *temp;                       // Temporary pointer to hold the current node
    while (head != NULL) {            // Traverse the list
        temp = head;                  // Store the current node
        head = head->next;            // Move to the next node
        free(temp);                   // Free the memory of the current node
    }
}

int main(int argc, char *argv[]) 
{
    Node *head = NULL;                // Initialize the head of the list to NULL

    append(&head, 10);                // Append 10 to the list
    append(&head, 20);                // Append 20 to the list
    append(&head, 30);                // Append 30 to the list

    printList(head);                  // Print the list: Outputs: 10 -> 20 -> 30 -> NULL

    freeList(head);                   // Free the memory allocated for the list
    head = NULL;                      // Set head to NULL

    return 0;                         // Return 0 to indicate successful execution
}
