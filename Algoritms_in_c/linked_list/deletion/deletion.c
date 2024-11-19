#include <stdio.h>
#include <stdlib.h>

//define the structure of a node in the linked list
struct Node {
    int data;           //data stored in the node
    struct Node* next;  //pointer to the next node
};

//Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); //Allocate memory for new node
    newNode->data = data; //Assign data to new node
    newNode->next = NULL; // Initially, the next pointer is Null
    return newNode;       // Return the newly created node
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data); // print the data in each node
        temp = temp->next;             // move to the next node
    }
    printf("NULL\n"); // End of the linked list
}

// Deletion at the beginning of the linked list
void deleteAtBeginning(struct Node** head) {
    if (*head == NULL) {
        //checking if list is empty
        printf("List is already empty.\n");
        return;
    }

    struct Node* temp = *head; // Temporary pointer to the head
    *head = (*head)->next;     // Move the head pointer to the next node
    free(temp);
    printf("Node deleted at the beginning.\n");
}

// Deletion at the end of the linked list
void deleteAtEnd(struct Node** head) {
    if (*head == NULL) {// check if list is empty
    printf("list is already empty.\n");
    return;
    }

    if ((*head)->next == NULL) {
        //if there is only one node
        free(*head); // free the only node
        *head = NULL; // set head to NULL
        printf("Node deleted at the end.\n");
        return;

    }

    struct Node* temp = *head;
    while (temp->next != NULL && temp->next->next != NULL) {
        //Traverse till the second last node
        temp = temp->next;
    }

    free(temp->next); //free the last node
    temp->next = NULL; //Set the second last nodes pointer to NULL
    printf("Node deleted at the end.\n");
}

//Deleting at a specific position (1-based index)
void deleteAtPosition(struct Node** head, int position) {
    if (*head == NULL) {
        //check if the list is empty
        printf("list is already empty.\n");
        return;
    }

    // if position is 1, delete the node at the beginning
    if (position == 1) {
        deleteAtBeginning(head);
        return;
    }

    struct Node* temp = *head;
    struct Node* prev = NULL;
    int count = 1;

    // traverse the list o find the position
    while (temp != NULL && count < position) {
        prev = temp;   // keep track of the previous node
        temp = temp->next; // Move to the next node
        count++;
    }

    // If the position is greater than the number of nodes
    if (temp == NULL) {
        printf("Position out of range.\n");
        return;
    }

    prev->next = temp->next; // bypass the node at the specified position
    free(temp);              // free the memory of the deleted node
    printf("Node deleted at position %d.\n", position);
}

int main() {
    struct Node* head = NULL; // start with an empty list

    // manually creating a list for demonstration: 10 -> 20 -> 30 -> 40 -> NULL
    head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);

    printf("Original linked list: ");
    printList(head);

    // deleting at beginning
    deleteAtBeginning(&head);
    printList(head);

    //deleting at end
    deleteAtEnd(&head);
    printList(head);

    //deleting at a specific position
    deleteAtPosition(&head, 2); // deleting node at position 2
    printList(head);

    return 0;
}