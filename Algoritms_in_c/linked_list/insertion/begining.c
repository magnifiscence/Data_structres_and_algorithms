#include <stdio.h>
#include <stdlib.h>

// define the structure of a node
struct Node {
    int data;
    struct Node* next;
};

// function to insert a node at the begining of the linked list
void insertAtBegining(struct Node** head, int new_data) {
    // allocate memory for the new node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    // Assign data to the new node
    new_node->data = new_data;

    // Make the new node point to the current head
    new_node->next = (*head);

    //update the head to point to the newnode
    (*head) = new_node;
}

int main() {
    struct Node* head = NULL; //intialize  the head of the list as NULL

    // Insert nodes at the begining
    insertAtBegining(&head, 10);
    insertAtBegining(&head, 20);
    insertAtBegining(&head, 30);

    // Print the list to verify
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    return 0;
}