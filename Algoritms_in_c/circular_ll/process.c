#include <stdio.h>
#include <stdlib.h>

// Structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the circular linked list
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head; // Circular link to itself
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
        *head = newNode;
    }
    printf("Inserted %d at the beginning.\n", data);
}

// Function to insert a node at the end of the circular linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head; // Circular link to itself
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
    printf("Inserted %d at the end.\n", data);
}

// Function to insert a node at a specific position
void insertAtPosition(struct Node** head, int data, int position) {
    if (position < 0) {
        printf("Invalid position.\n");
        return;
    }
    if (position == 0) {
        insertAtBeginning(head, data);
        return;
    }
    struct Node* newNode = createNode(data);
    struct Node* temp = *head;
    for (int i = 1; i < position; i++) {
        temp = temp->next;
        if (temp == *head) {
            printf("Position out of range.\n");
            return;
        }
    }
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at position %d.\n", data, position);
}

// Function to delete a node by value
void deleteByValue(struct Node** head, int value) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *current = *head, *prev = NULL;

    // If the head node is to be deleted
    if (current->data == value) {
        while (current->next != *head) {
            current = current->next;
        }
        if (*head == (*head)->next) { // Only one node in the list
            free(*head);
            *head = NULL;
        } else {
            current->next = (*head)->next;
            free(*head);
            *head = current->next;
        }
        printf("Deleted %d from the list.\n", value);
        return;
    }

    // For other nodes
    while (current->next != *head) {
        prev = current;
        current = current->next;
        if (current->data == value) {
            prev->next = current->next;
            free(current);
            printf("Deleted %d from the list.\n", value);
            return;
        }
    }
    printf("Value %d not found in the list.\n", value);
}

// Function to print the circular linked list
void printList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = head;
    printf("Circular Linked List: ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

// Main function
int main() {
    struct Node* head = NULL;

    // Insertions
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    insertAtBeginning(&head, 5);
    insertAtPosition(&head, 15, 2);

    // Print the list
    printList(head);

    // Deletion
    deleteByValue(&head, 20);
    printList(head);

    deleteByValue(&head, 5);
    printList(head);

    deleteByValue(&head, 100); // Value not in the list
    printList(head);

    return 0;
}