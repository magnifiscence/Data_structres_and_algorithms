#include <stdio.h>
#include <stdlib.h>

//Inserting a node at a given position in a linked list
void insertAtPosition(struct Node** head, int new_data, int position) {
    //Allocate memory for the new code
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    //Assign data to the new node
    new_node->data = new_data;

    //if inserting at the begining, handle seperately
    if (position == 0) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    //Traverse to the node before the desired position
    struct Node* temp = *head;
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    // If the position is beyond the end of the list do nothing
    if (temp == NULL || temp->next == NULL) {
        return;
    }

    //make the new node point to the next node
    new_node->next = temp->next;

    temp->next = new_node;
}

int main() {
    struct Node* head = NULL; // Initialize the head of the list as NULL

    // Insert nodes at various positions
    insertAtPosition(&head, 10, 0); // insert at the beginning
    insertAtPosition(&head, 20, 1); // insert at position 1
    insertAtPosition(&head, 30, 1); // insert at position 1 again

    //Print the list to verify
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;

    }
    printf("NULL\n");

    return 0;
}