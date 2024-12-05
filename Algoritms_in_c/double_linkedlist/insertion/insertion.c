#include <stdio.h>
#include <stdlib.h>

// structure for a node in a double linked list
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the doubly linked list
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// function to insert a node at the end of the linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode; //If the list is empty, the new node becomes the head
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next; // traverse to the last node
    }
    temp->next = newNode; //link the last nodes next to the new node
    newNode->prev = temp; //set new node's previous to last node
}

// function to insert a node at a specific position (0-based index)
void insertAtPosition(struct Node** head, int data, int position) {
    if (position < 0) {
        printf("Invalid position!\n");
        return;
    }
    if (position == 0) {
        insertAtBeginning(head, data);
        return;
    }

    struct Node* newNode = createNode(data);
    struct Node* temp = *head;
    int index = 0;

    //traverse to the desired position
    while (temp != NULL && index < position) {
        temp = temp->next;
        index++;
    }

    if (temp == NULL) {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }

    //Insert the new node at the desired position
    newNode->next = temp;
    newNode->prev = temp->prev;
    if (temp->prev != NULL) {
        temp->prev->next = newNode; // Update previous nodes next to new node
    }
    temp->prev = newNode;

    //if the insertion is at the begining position 0
    if ( newNode->prev == NULL) {
        *head = newNode;
    }
}

//function to insert a node after a specific position 0 based index
void insertAfterPosition(struct Node** head, int data, int position)
{
    struct Node* temp = *head;
    int index = 0;

    // Traverse to the position just before the insertion point
    while (temp != NULL && index < position) {
        temp = temp->next;
        index++;
    }

    if (temp == NULL) {
        printf("Position out of range!\n");
        return;
    }

    struct Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

// function to print doubly linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function for testing
int main() {
    struct Node* head = NULL;

    //insert at the beginning
    insertAtBeginning(&head, 10);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 30);

    // print the list
    printf("list after inserting at the beginning:\n");
    printList(head);

    //insert at the end
    insertAtEnd(&head, 40);
    insertAtEnd(&head, 50);

    //print the list
    printf("list after insertion at the end:\n");
    printList(head);

    //insert at a specific position (position 2)
    insertAtPosition(&head, 25, 2);

    //print the list
    printf("list after insertion at position 2:\n");
    printList(head);

    //insert after a specific position (position 2)
    insertAtPosition(&head, 35, 2);

    //print the list
    printf("List after insertion after position 2:\n");
    printList(head);

    return 0;
}