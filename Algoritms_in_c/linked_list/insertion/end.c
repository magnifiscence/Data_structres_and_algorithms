// Function to insert a node at the end of the linked list
void insertAtEnd(struct Node** head, int new_data) {
    //allocate memory for the new node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    //Assign data to the new node
    new_node->data = new_data;
    new_node->next = NULL; // the new node will be the last so set its next to NULL

    // If the linked list is empty make the new node the head
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    // Traverse to the last node
    struct Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }

    //make the last node point to the new node
    last->next = new_node;
}

int main() {
    struct Node* head = NULL; // Initialize the head of the list as NULL

    //insert nodes at the end
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);

    //Print the list to verify
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    return 0;

}