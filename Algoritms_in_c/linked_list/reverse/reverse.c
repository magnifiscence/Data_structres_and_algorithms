#include <stdio.h>
#include <stdlib.h>

//define structure of node in link list
struct Node {
    int data;
    struct Node* next;
};

// function to reverse the linked list
struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;    //Previous node, initially NULL
    struct Node* current = head; //current node starts at the head
    struct Node* next = NULL;    //Next node will be used to store the next node

    //traverse the list and reverse the links
    while (current != NULL) {
        next = current->next;    //store the next node
        current->next = prev;    //reverse the next pointer
        prev = current;          //move prev o current node
        current = next;          //move to the next node
    }
    return prev; // 'prev' will be the new head of the reversed list
}



// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


//function to print the linked list
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

//main function to test the findlength function
int main() {
    //create a simple linked list: 1 -> 2-> 3 -> NULL
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);

    printf("Original linked list:\n");
    printList(head);

    //Reverse the linked list
    head = reverseList(head);

    printf("Reversed linked list:\n");
    printList(head);

    return 0;
}