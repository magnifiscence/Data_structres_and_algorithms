#include <stdio.h>
#include <stdlib.h>

//define structure of node in link list
struct Node {
    int data;
    struct Node* next;
};

// function to find the length of a linked list
int findLength(struct Node* head) {
    int length = 0; //variable to store the length
    struct Node* current = head; // start with the head of the list

    // traverse the list
    while (current != NULL) {
        length++;   //increment length for each node
        current = current->next; // move to the next node
    }

    return length; // return the total length
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

//main function to test the findlength function
int main() {
    //create a simple linked list: 1 -> 2-> 3 -> NULL
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);

    //find and print the length of the list
    printf("length of the linked list: %d\n", findLength(head));

    return 0;
}